cmake_minimum_required(VERSION 3.27)
project(Integral)

set(CMAKE_C_COMPILER "/opt/homebrew/opt/open-mpi/bin/mpicc")
set(CMAKE_CXX_COMPILER "/opt/homebrew/opt/open-mpi/bin/mpicxx")
set(MPI_INCLUDE_PATH "/opt/homebrew/opt/open-mpi/include")
set(MPI_LIBRARY "/opt/homebrew/opt/open-mpi/lib/libmpi.dylib")

set(CMAKE_CXX_STANDARD 17)

add_executable(Integral integration.c
        parallel_integration.c)
