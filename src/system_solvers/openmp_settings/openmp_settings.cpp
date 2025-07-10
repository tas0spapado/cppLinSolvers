#include "openmp_settings.h"

int openmp_settings::num_threads = 1;

void openmp_settings::set_num_threads(int N)
{
    num_threads = (N>omp_get_max_threads())?omp_get_max_threads():N;
}


