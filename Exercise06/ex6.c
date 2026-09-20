#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 1000000
#define STRIP_SIZE 256

int main() {
    float *A, *B, *C;

    if (posix_memalign((void**)&A, 64, N * sizeof(float)) != 0) return 1;
    if (posix_memalign((void**)&B, 64, N * sizeof(float)) != 0) return 1;
    if (posix_memalign((void**)&C, 64, N * sizeof(float)) != 0) return 1;

    for (int i = 0; i < N; i++) {
        A[i] = (float)(i % 100) * 0.5f;
        B[i] = (float)(i %  50) * 0.25f;
    }

    #pragma omp parallel for schedule(static)
    for (int s = 0; s < N; s += STRIP_SIZE) {
        int end = s + STRIP_SIZE;
        if (end > N) end = N;

        #pragma omp simd
        for (int i = s; i < end; i++) {
            C[i] = A[i] * B[i];
        }
    }

    printf("%f\n", C[0] + C[N-1]);

    free(A);
    free(B);
    free(C);
    return 0;
}
