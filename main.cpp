#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#include <dictionary/dictionary.h>
#include <parallel/finder.h>

#include <utils/benchmark.h>
#include <utils/file.h>
#include <utils/report_creation.h>
#include <utils/serialization.h>

#include "command_line.h"


int main(int argc, char *argv[]) {
    // dictionary::Dictionary d{};
    // d.insert("g", "8");
    // d.insert("e", "4");
    // d.insert("k", "5");
    // d.insert("v", "2");
    // d.insert("a", "7");
    // d.insert("y", "0");
    // d.insert("i", "9");
    // d.insert("p", "1");
    // d.insert("j", "3");
    // d.insert("t", "6");
    // parallel::Finder f{d};
    // const auto r = f.parallel_find("j", 5);
    // std::cout << r.first << std::endl;
    // return 0;

#define CHUNKSIZE   10
#define N       100

//int nthreads, tid, i, chunk;
//float a[N], b[N], c[N];

CommandLine commandLine;

//performance_reporter.show_time_report();

commandLine.ProcessUserCommands();

}
