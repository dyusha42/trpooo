#include <iostream>
#include <vector>
#include <chrono>
#include <cmath>
#include <iomanip>
#include <omp.h>
#include <cblas.h>

#include "my_blas.hpp"

using namespace std;

void run_openblas(int n, float* A, float* B, float* C) {
    cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, n, n, n, 1.0f, A, n, B, n, 0.0f, C, n);
}
void run_openblas(int n, double* A, double* B, double* C) {
    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, n, n, n, 1.0, A, n, B, n, 0.0, C, n);
}

template <typename T>
void run_benchmark(int n, const string& type_name) {
    cout << "\n=== Тестирование для типа: " << type_name << " (Размер: " << n << "x" << n << ") ===\n";
    
    vector<T> A(n * n, 1.0), B(n * n, 1.0), C(n * n, 0.0);
    vector<int> threads = {1, 2, 4, 8, 16};
    const int runs = 10;

    for (int t : threads) {
        omp_set_num_threads(t);
        openblas_set_num_threads(t);

        double my_total_time = 0.0;
        double ob_total_time = 0.0;
        double log_sum = 0.0;

        cout << "Потоков: " << setw(2) << t << " | ";

        for (int r = 0; r < runs; ++r) {
            auto start = chrono::high_resolution_clock::now();
            run_openblas(n, A.data(), B.data(), C.data());
            auto end = chrono::high_resolution_clock::now();
            double ob_time = chrono::duration<double>(end - start).count();

            start = chrono::high_resolution_clock::now();
            my_gemm<T>(n, 1.0, A.data(), B.data(), 0.0, C.data());
            end = chrono::high_resolution_clock::now();
            double my_time = chrono::duration<double>(end - start).count();

            ob_total_time += ob_time;
            my_total_time += my_time;

            double rel_perf = (ob_time / my_time) * 100.0; 
            log_sum += log(rel_perf);
        }

        double geom_mean = exp(log_sum / runs);
        cout << "Ср. время OpenBLAS: " << fixed << setprecision(4) << (ob_total_time / runs) << "c | "
             << "Ср. время MyBLAS: " << (my_total_time / runs) << "c | "
             << "Ср. геом. производительность: " << setprecision(2) << geom_mean << "%\n";
    }
}

int main() {
    int N = 2000; 

    run_benchmark<float>(N, "float (Одинарная точность)");
    run_benchmark<double>(N, "double (Двойная точность)");

    return 0;
}