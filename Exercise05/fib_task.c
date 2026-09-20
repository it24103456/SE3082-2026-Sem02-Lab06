#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int fib(int n) {
    if (n < 2) return n;

    int i, j;

    #pragma omp task shared(i) firstprivate(n) if(n > 20)
    i = fib(n - 1);

    #pragma omp task shared(j) firstprivate(n) if(n > 20)
    j = fib(n - 2);

    #pragma omp taskwait
    return i + j;
}

int main(int argc, char *argv[]) {
    int n = 20;
    if (argc > 1) n = atoi(argv[1]);

    int result;

    #pragma omp parallel
    {
        #pragma omp single
        result = fib(n);
    }

    printf("%d\n", result);
    return 0;
}
