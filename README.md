A C++ library collection for solving linear systems of equations numerically, using OpenMP.

## Make sure you have the following installed:
sudo apt update
sudo apt install build-essential

## Build instructions 
chmod +x buildAll.sh
./buildAll.sh or bear -- ./build.sh

## Repository structure 
src/         -> Library source code
tests/       -> Test applications (executables)
linked_headers/    -> Symlinked headers for compilation
libs/        -> Compiled shared libraries (.so)
objs/        -> Intermediate object files (.o)
bins/        -> Final compiled binaries
solvers/     -> Solver source code (optional/experimental)

