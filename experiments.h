#ifdef __cplusplus
#include <cstdlib>
#else
#include <stdlib.h>
#endif
#pragma once

typedef struct experiment_result_ {
    double result;
    double time_ms;
    double speedup;
} experiment_result;

experiment_result *run_experiments(unsigned *V, size_t count, unsigned min , unsigned max, double (*accumulate)(unsigned *, size_t, unsigned, unsigned));
void print_experiment_results(const experiment_result *results);
void run_experiments_for(unsigned *V, size_t count, unsigned min, unsigned max, double (*accumulate)(unsigned *, size_t, unsigned, unsigned));