#include<stdio.h>
#include<stdlib.h>

#define Y(i,j) Y[(i)*N+(j)]
#define X(i,j) X[(i)*2*N+(j)]

#define max(a,b) (a)>(b)?(a):(b)
#define min(a,b) (a)>(b)?(b):(a)

long count;

int op(int a, int b) {
    count++;
    return max(a,b);
}

int* r0(int *X, int N) {
    int *Y = malloc(N*N*sizeof(int));
    int i,j,k,l;

    for (i=0; i<N; i++) 
        for (j=i; j<N; j++) 
            for (k=i; k<=2*i; k++) 
                for (l=i+j; l<=2*j; l++) 
                    Y(i,j) = op(Y(i,j), X(k,l));

    return Y;
}

#define Y_NR_add(i,j,l) Y_NR_add[(i)*(N)*(2)+(j)*(2)+(l)%2]
#define Y_outer(i,l) Y_NR_add(i,(l+1)/2,l)

void fractal0(int *X, int *Y, int *Y_NR_add, int N, int U, int l) {
    #define A(i) Y_outer(i,l)
    #define B(k) X(k,l)

    if (U<10) {
      for (int i=0; i<U; i++) 
        for (int k=i; k<=2*i; k++) 
          A(i) = op(A(i), B(k));
      return;
    }

    /* backward scan
     * D := [U]->{[i,k]: U>10 and 0<=i<U and i<=k<=2i and k<U and 2i>=U }
     * f := [U]->{[i,k]->[i-1,k]}
     * D - f(D)
     */
    int c0 = 1;
    int i = U-c0;
    int k = U-c0;
    A(i) = B(k);
    for (int c0=2; c0<=U/2; c0+=1) {
      int i = U-c0;
      int k = U-c0;
      A(i) = op(A(i+1), B(k));
    }

    /* forward scan
     * D := [U]->{[i,k]: U>10 and 0<=i<U and i<=k<=2i and k>=U }
     * f := [U]->{[i,k]->[i+1,k]}
     * D - f(D)
     */
    i = (U+1)/2;
    int tmp = 0;
    for (int k=max(U,2*i-1); k<=2*i; k++) {
      tmp = op(tmp, B(k));
    }
    A(i) = op(A(i), tmp); 
    for (int i=(U+1)/2+1; i<U; i++) {
      for (int k=max(U,2*i-1); k<=2*i; k++) {
        tmp = op(tmp, B(k));
      }
      A(i) = op(A(i), tmp); 
    }

    /* recurse 
     * D := [U]->{[i,k]: U>10 and 0<=i<U and i<=k<=2i and 2i<U }
     */
    fractal0(X, Y, Y_NR_add, N, (U+1)/2, l);

    #undef A
    #undef B
}

void fractal1(int *X, int *Y, int *Y_NR_add, int N, int L, int U, int i) {
    #define A(j) Y(i,j)
    #define B(l) Y_outer(i,l)

    if (U-L<10) {
      for (int j=L; j<U; j++) 
        for (int l=L+j; l<=2*j; l++) 
          A(j) = op(A(j), B(l));
      return;
    }

    /* backward scan
     * D := [L,U]->{[j,l]: 0<=L and U-L>10 and L<=j<U and L+j<=l<=2j and l<L+U and 2j>=L+U }
     * f := [L,U]->{[j,l]->[j-1,l]}
     * D - f(D)
     */
    int c0 = 1;
    int j = U-c0;
    int l = L+U-c0;
    A(j) = B(l);
    for (int c0=2; c0<=-L+(L+U)/2; c0+=1) {
      int j = U-c0;
      int l = L+U-c0;
      A(j) = op(A(j+1), B(l));
    }

    /* forward scan
     * D := [L,U]->{[j,l]: 0<=L and U-L>10 and L<=j<U and L+j<=l<=2j and l>=L+U }
     * f := [L,U]->{[j,l]->[j+1,l]}
     * D - f(D)
     */
    j = (L+U+1)/2;
    int tmp = 0;
    for (int l=max(L+U,2*j-1); l<=2*j; l++) {
      tmp = op(tmp, B(l));
    }
    A(j) = op(A(j), tmp); 
    for (int j=(L+U+1)/2+1; j<U; j++) {
      for (int l=max(L+U,2*j-1); l<=2*j; l++) {
        tmp = op(tmp, B(l));
      }
      A(j) = op(A(j), tmp); 
    }

    /* recurse 
     * D := [L,U]->{[j,l]: 0<=L and U-L>10 and L<=j<U and L+j<=l<=2j and 2j<L+U }
     */
    fractal1(X, Y, Y_NR_add, N, L, (L+U+1)/2, i);

    #undef A
    #undef B
}


int* r1(int *X, int N) {
    int *Y = malloc(N*N*sizeof(int));
    int *Y_NR_add = malloc((N)*(N)*(2)*sizeof(int));

    // This is O(N^2)
    // 
    for(int l=0; l<=2*N; l++)
      fractal0(X, Y, Y_NR_add, N, l/2+1, l);

    // This is O(N^2)
    // 
    for (int i=0; i<N; i++) {
      for (int k=i; k<=2*i; k++)
        Y(i,i) = op(Y(i,i), X(k,2*i));
    }

    // This is O(N^2)
    // 
    for (int i=0; i<N; i++) {
      fractal1(X, Y, Y_NR_add, N, i+1, N, i);
      for (int j=i+1; j<N; j++) 
        Y(i,j) = op(Y(i,j), Y_outer(i,i+j));
    }

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
        for (int j=0; j<2*N; j++) 
            X(i,j) = (int)(100000 * (rand() + 0.0) / RAND_MAX);
 
    // input reduction O(N^4)
    count = 0;
    int *Y0 = r0(X, N);
    long count0 = count;

    // simplified reduction O(N^2)
    count = 0;
    int *Y1 = r1(X, N);
    long count1 = count;
    
    #define Y0(i,j) Y0[(i)*N+(j)]
    #define Y1(i,j) Y1[(i)*N+(j)]
    int errs = 0;
    for (int i=0; i<N; i++)
        for (int j=i; j<N; j++)
            if (Y0(i,j) != Y1(i,j)) {
                fprintf(stderr, "Y0(%d,%d)=%d, Y1(%d,%d)=%d\n", i, j, Y0(i,j), i, j, Y1(i,j));
                errs++;
            }

    printf("(seed=%d)\n", seed);
    printf("N = %d\n", N);
    printf("count0 = %ld\n", count0);
    printf("count1 = %ld\n", count1);
    printf("errors = %d\n", errs);

    return 0;    
}
