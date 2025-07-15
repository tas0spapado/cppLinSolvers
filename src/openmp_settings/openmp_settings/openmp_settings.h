#include <omp.h>

namespace openmp_settings
{
    extern int num_threads;

    void set_num_threads(int N);
}
