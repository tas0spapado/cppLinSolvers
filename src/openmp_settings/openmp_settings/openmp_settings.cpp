#include "openmp_settings.h"
#include <iostream>

int openmp_settings::num_threads = 1;

void openmp_settings::set_num_threads(int N)
{
    num_threads = (N>omp_get_num_procs())?omp_get_max_threads():N;
    if (num_threads<1) num_threads = 1;
    omp_set_num_threads(num_threads);
    std::cout << "Setting number of threads: " << num_threads << " (max:" << omp_get_num_procs() << ")" << std::endl; 
}


