#include <testing/benchmark_test.h>
#include <testing/dictionary_test.h>
#include <testing/file_test.h>
#include <testing/report_creation_test.h>
#include <testing/serialization_test.h>

int main(int argc, char *argv[]) {
    test::run_all_dictionary_tests();
    test::run_all_file_tests();
    test::run_all_serialization_tests();
    test::run_all_report_creation_tests();
    test::run_all_benchmark_tests();
    
    return 0;
}
