#include <iostream>
#include "num_threads.h"
#include "experiments.h"
#include "rand.h"


int main(int argc, char **argv) {
    size_t element_count = 100000000u;
    unsigned min = 10;
    unsigned max = 100;
    auto* V = new unsigned[element_count];
    run_experiments_for(V, element_count, min, max,
                        reinterpret_cast<double (*)(unsigned int *, size_t, unsigned int, unsigned int)>(randomize));
    return 0;
}