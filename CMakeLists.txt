cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_STANDARD 17)

# RELEASE
project(prir_parallel_dictionary VERSION 1.0 LANGUAGES CXX)

add_executable(prir_parallel_dictionary main.cpp
                                        dictionary/dictionary.cpp
                                        parallel/finder.cpp
                                        utils/benchmark.cpp
                                        utils/file.cpp
                                        utils/serialization.cpp
                                        utils/performance_reporter.cpp
                                        utils/command_line.cpp)

find_package(OpenMP)
if(OpenMP_CXX_FOUND)
    target_link_libraries(prir_parallel_dictionary PUBLIC OpenMP::OpenMP_CXX)
endif()

target_include_directories(prir_parallel_dictionary PUBLIC .)

# TESTING
project(prir_parallel_dictionary_test VERSION 1.0 LANGUAGES CXX)

add_executable(prir_parallel_dictionary_test dictionary/dictionary.cpp
                                             parallel/finder.cpp
                                             utils/benchmark.cpp
                                             utils/file.cpp
                                             utils/serialization.cpp
                                             utils/command_line.cpp
                                             utils/performance_reporter.cpp
                                             testing/main_test.cpp
                                             testing/benchmark_test.cpp
                                             testing/dictionary_test.cpp
                                             testing/file_test.cpp
                                             testing/report_creation_test.cpp
                                             testing/serialization_test.cpp)

find_package(OpenMP)
if(OpenMP_CXX_FOUND)
    target_link_libraries(prir_parallel_dictionary_test PUBLIC OpenMP::OpenMP_CXX)
endif()

target_include_directories(prir_parallel_dictionary_test PUBLIC .)
