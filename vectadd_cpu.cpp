#include <iostream>
#include <chrono>
#include <cmath>

void add(int n, float *x, float *y) {
    for (int i = 0; i < n; i++) {
        y[i] = x[i] + y[i];
    }
}

int main() {
    int N = 1 << 29;  // 512M elements as specified

    float *x = new float[N];
    float *y = new float[N];

    for (int i = 0; i < N; i++) {
        x[i] = 1.0f;
        y[i] = 2.0f;
    }

    auto start = std::chrono::high_resolution_clock::now();
    
    add(N, x, y);
    
    auto end = std::chrono::high_resolution_clock::now();
    
    std::chrono::duration<double> elapsed_seconds = end - start;
    double elapsed_ms = elapsed_seconds.count() * 1000.0;

    // Verify results
    float maxError = 0.0f;
    for (int i = 0; i < N; i++) {
        maxError = fmax(maxError, fabs(y[i] - 3.0f));
    }
    std::cout << "Max error: " << maxError << std::endl;
    std::cout << "Elapsed time: " << elapsed_ms << " ms" << std::endl;

    // frees
    delete[] x;
    delete[] y;

    return 0;
}