# prir-parallel-dictionary
A project for WUT Polish technical university's Computer Science course about parallelism.

Compile with:
`chmod u+x ./build.sh`
`./build.sh`

Compile and run with:
`chmod u+x ./build_and_run.sh`
`./build_and_run.sh`

Please install:
`sudo apt install mpich`

Run the MPI version with:
`mpiexec -n 10 --oversubscribe ./prir_parallel_dictionary`

Sample CSVs in the `assets/` directory.

Available commands in the OpenMP version:
```
reset
save
saveexit
find <key>
pfind <key> <threads_num>
init <file_name>
put <key> <value>
delete <key>
update <key> <value>
exit
```

Available commands in the MPI version:
```
find <key>
put <key> <value>
delete <key>
update <key> <value>
exit
```
