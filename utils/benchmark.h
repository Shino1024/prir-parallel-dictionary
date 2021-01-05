#ifndef PRIR_BENCHMARK_H
#define PRIR_BENCHMARK_H

#include <chrono>

#include <utils/report_creation.h>

namespace benchmark {
    class Benchmark {
    public:
        Benchmark(unsigned int threads);

    private:
        unsigned int threads{};
    };
}

#endif // PRIR_BENCHMARK_H
