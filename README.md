A C++ library collection for solving linear systems of equations numerically. 

## Build Instructions 
## Make sure you have g++ and make 
sudo apt update
sudo apt install build-essential
chmod +x buildAll.sh
./buildAll.sh


## Repository Structure 
src/        : library source code 
tests/      : executables to test libraries 
iheaders/   : symlinked headers for compilation 
libs/       : compiled shared libraries 
objs/       : object files 
bins/       : final compiled binaries 
solvers/    : solver source code
