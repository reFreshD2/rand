#ifdef __cplusplus
#define EXTERN_C extern "C"
#include <cstdio>
using std::fprintf;
#else
#define EXTERN_C
#include <stdio.h>
#endif
#define CACHE_LINE 64
#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <ctime>
#include "num_threads.h"

#define A 1103515245u
#define b 12345u
#define c 4294967296u

std::vector<unsigned> get_A(unsigned T) {
    std::vector<unsigned> result;
    result.reserve(T);
    result.emplace_back(A);
    for (unsigned i = 1; i < T; i++) {
        result.emplace_back((result.back() * A) % c);
    }
    return result;
}

struct aligned_unsigned {
    alignas(CACHE_LINE) unsigned value;
};

double randomize(unsigned *V, size_t N, unsigned mina, unsigned maxa) {
    unsigned T = get_num_threads();
    std::vector<unsigned> multipliers = get_A(T);
    double median = 0.0;
    std::mutex mtx;
    std::vector<aligned_unsigned> partial_rand(T);
    std::vector<std::thread> threads;
    unsigned seed = std::time(nullptr);
    for (std::size_t t = 0; t < T; ++t) {
        threads.emplace_back([t, T, &V, N, seed, &multipliers, &mtx, &median, &mina, &maxa]() {
            unsigned _A = multipliers.back();
            unsigned off = (b * (_A - 1) / (A - 1)) % c;
            unsigned x = ((seed * multipliers[t]) % c + (b * (multipliers[t] - 1) / (A - 1)) % c) % c;
            double my_median = 0.0;
            for (size_t i = t; i < N; i += T) {
                V[i] = (x % (maxa - mina)) + mina;
                my_median += (double) V[i];
                x = ((x * _A) % c + off) % c;
            }
            mtx.lock();
            median += my_median;
            mtx.unlock();
        });
    }
    for (auto &thread : threads) { thread.join(); }
    return median / N;
}