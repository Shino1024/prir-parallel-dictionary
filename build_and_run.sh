#!/bin/bash
mkdir build
cd build
cmake ..
make
./prir_parallel_dictionary_test
./prir_parallel_dictionary
