#include "f3.h"
void avx_add(__m256d &t0, __m256d &t1, __m256d &t2) {
    t2 = _mm256_add_pd ( t0, t1);
}