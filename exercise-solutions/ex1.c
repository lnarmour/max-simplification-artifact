#include<stdio.h>
#include<stdlib.h>

#define Y(i) Y[i]
#define X(i) X[i]

int count;

int op(int a, int b) {
    count++;
    return a + b;
}

int op_inv(int a, int b) {
    count++;
    return a - b;
}

int* r0(int *X, int N) {
    int *Y = malloc(N*sizeof(int));

    for (int i=0; i<N; i++) 
        for (int j=i; j<=2*i; j++) 
            //Y(i) = Y(i) + X(j);
            Y(i) = op(Y(i), X(j));

    return Y;
}

int* r1(int *X, int N) {
    int *Y = malloc(N*sizeof(int));

    Y(0) = X(0);
    for (int i=1; i<N; i++)
      // Y(i) = Y(i-1) + X(2*i) + X(2*i-1) - X(i-1);
      Y(i) = op(Y(i-1), op_inv(op(X(2*i), X(2*i-1)), X(i-1)));

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
