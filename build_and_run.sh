#!/bin/bash
mkdir build
cd build
cmake ..
make
mpiexec -n 10 --oversubscribe ./prir_parallel_dictionary
