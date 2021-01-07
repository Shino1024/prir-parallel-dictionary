#ifndef PRIR_PERFORMANCE_REPORTER
#define PRIR_PERFORMANCE_REPORTER

#include <chrono>
#include <iostream>
#include <unistd.h>

using namespace std;
using namespace std::chrono;

class PerformanceReporter {
    public:
        enum checkpoint{cp_1,cp_2,cp_3,cp_4};
        
        void logTime(checkpoint);
        void show_time_report();
        
    private:
        bool mid_measurements;
        chrono::time_point<system_clock> t1; //beginning of the processing
        chrono::time_point<system_clock> t2; //just before pararrell processing
        chrono::time_point<system_clock> t3; //just after pararrell processing
        chrono::time_point<system_clock> t4; //end of processing

};

#endif // PRIR_PERFORMANCE_REPORTER
