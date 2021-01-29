cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_STANDARD 17)

set(MPI_CXX_COMPILER /usr/bin/mpicxx)
set(MPI_C_COMPILER /usr/bin/mpicc)
set(MPIEXEC_EXECUTABLE /usr/bin/mpiexec.hydra)
SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${MPI_COMPILE_FLAGS}")
SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${MPI_LINK_FLAGS}")
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

# find_package(OpenMP)
# if(OpenMP_CXX_FOUND)
#     target_link_libraries(prir_parallel_dictionary PUBLIC OpenMP::OpenMP_CXX)
# endif()

target_include_directories(prir_parallel_dictionary PUBLIC .)

# TESTING
# project(prir_parallel_dictionary_test VERSION 1.0 LANGUAGES CXX)

# add_executable(prir_parallel_dictionary_test dictionary/dictionary.cpp
#                                              parallel/finder.cpp
#                                              utils/benchmark.cpp
#                                              utils/file.cpp
#                                              utils/serialization.cpp
#                                              utils/command_line.cpp
#                                              utils/performance_reporter.cpp
#                                              testing/main_test.cpp
#                                              testing/benchmark_test.cpp
#                                              testing/dictionary_test.cpp
#                                              testing/file_test.cpp
#                                              testing/report_creation_test.cpp
#                                              testing/serialization_test.cpp)

# find_package(OpenMP)
# if(OpenMP_CXX_FOUND)
#     target_link_libraries(prir_parallel_dictionary_test PUBLIC OpenMP::OpenMP_CXX)
# endif()

find_package(MPI REQUIRED)
include_directories(SYSTEM ${MPI_INCLUDE_PATH})
target_link_libraries(prir_parallel_dictionary ${MPI_LIBRARIES})
# target_link_libraries(prir_parallel_dictionary_test MPI_C)

# target_include_directories(prir_parallel_dictionary_test PUBLIC .)
