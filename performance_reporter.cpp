#include <iostream>
#include "performance_reporter.h"

void PerformanceReporter::logTime(checkpoint _checkpoint)
{

    switch (_checkpoint)
    {
    case cp_1:
        t1 = chrono::system_clock::now();
        break;
    case cp_2:
        t2 = chrono::system_clock::now();
        break;
    case cp_3:
        t3 = chrono::system_clock::now();
        break;
    case cp_4:
        t4 = chrono::system_clock::now();
        break;
    }

}

void PerformanceReporter::show_time_report()
{

    cout << "T2 - T1 Elapsed time in nanoseconds : "
        << chrono::duration_cast<chrono::nanoseconds>(t2 - t1).count()
        << " ns" << endl;

    cout << "T3 - T2 Elapsed time in nanoseconds : "
        << chrono::duration_cast<chrono::nanoseconds>(t3 - t2).count()
        << " ns" << endl;

    cout << "T4 - T3 Elapsed time in nanoseconds : "
        << chrono::duration_cast<chrono::nanoseconds>(t4 - t3).count()
        << " ns" << endl;

    cout <<endl;

}
