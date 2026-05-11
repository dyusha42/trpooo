#pragma once
#include <omp.h>

template <typename T>
void my_gemm(int n, T alpha, const T* __restrict A, const T* __restrict B, T beta, T* __restrict C) {
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (beta == 0.0) C[i * n + j] = 0.0;
            else C[i * n + j] *= beta;
        }
    }

    #pragma omp parallel for
    for (int i = 0; i < n; ++i) {
        for (int k = 0; k < n; ++k) {
            T r = alpha * A[i * n + k];
            #pragma omp simd
            for (int j = 0; j < n; ++j) {
                C[i * n + j] += r * B[k * n + j];
            }
        }
    }
}