#include<stdio.h>
#include<stdlib.h>

#define Y(i) Y[i]
#define X(i) X[i]

#define max(a,b) (a)>(b)?(a):(b)
#define min(a,b) (a)>(b)?(b):(a)

int count;

int op(int a, int b) {
    count++;
    return max(a, b);
}

int* r0(int *X, int N) {
    int *Y = malloc(N*sizeof(int));

    for (int i=0; i<N; i++) 
        for (int j=i; j<=2*i; j++) 
            //Y(i) = max(Y(i), X(j));
            Y(i) = op(Y(i), X(j));

    return Y;
}

void fractal(int *Y, int *X, int N, int U) {
    if (U<10) {
      for (int i=0; i<U; i++) 
        for (int j=i; j<=2*i; j++) 
          Y(i) = op(Y(i), X(j));
      return;
    }

    /* backward scan
     * D := [U]->{[i,j]: U>10 and 0<=i<U and i<=j<=2i and j<U and 2i>=U }
     * f := [U]->{[i,j]->[i-1,j]}
     * D - f(D)
     */
    int c0 = 1;
    int i = U-c0;
    int j = U-c0;
    Y(i) = X(j);
    for (int c0=2; c0<=U/2; c0+=1) {
      int i = U-c0;
      int j = U-c0;
      Y(i) = op(Y(i+1), X(j));
    }

    /* forward scan
     * D := [U]->{[i,j]: U>10 and 0<=i<U and i<=j<=2i and j>=U }
     * f := [U]->{[i,j]->[i+1,j]}
     * D - f(D)
     */
    i = (U+1)/2;
    int tmp = 0;
    for (int j=max(U,2*i-1); j<=2*i; j++) {
      tmp = op(tmp, X(j));
    }
    Y(i) = op(Y(i), tmp); 
    for (int i=(U+1)/2+1; i<U; i++) {
      for (int j=max(U,2*i-1); j<=2*i; j++) {
        tmp = op(tmp, X(j));
      }
      Y(i) = op(Y(i), tmp); 
    }

    /* recurse 
     * D := [U]->{[i,j]: U>10 and 0<=i<U and i<=j<=2i and 2i<U }
     */
    fractal(Y, X, N, (U+1)/2);
}


int* r1(int *X, int N) {
    int *Y = malloc(N*sizeof(int));

    // O(N)
    fractal(Y, X, N, N);   

    return Y;
}

int main(int argc, char **argv) {

    int seed;
    if (argc < 2) {
        printf("usage: %s N [seed]\n", argv[0]);
        return 1;
    } else if (argc < 3) {
        seed = 0;
    } else {
        seed = atoi(argv[2]);
    }
    int N = atoi(argv[1]);

    int *X = malloc(4*N*N*sizeof(int));

    srand(seed);
    for (int i=0; i<2*N; i++) 
        X(i) = (int)(100000 * (rand() + 0.0) / RAND_MAX);
 
    // input reduction O(N^2)
    count = 0;
    int *Y0 = r0(X, N);
    long count0 = count;

    // simplified reduction O(N)
    count = 0;
    int *Y1 = r1(X, N);
    long count1 = count;
    
    #define Y0(i) Y0[i]
    #define Y1(i) Y1[i]
    int errs = 0;
    for (int i=0; i<N; i++)
        if (Y0(i) != Y1(i)) {
            fprintf(stderr, "Y0(%d)=%d, Y1(%d)=%d\n", i, Y0(i), i, Y1(i));
            errs++;
        }

    printf("(seed=%d)\n", seed);
    printf("N = %d\n", N);
    printf("count0 = %ld\n", count0);
    printf("count1 = %ld\n", count1);
    printf("errors = %d\n", errs);

    return 0;    
}
