#include "f2.h"
void sse_add(__m128d &t0, __m128d &t1, __m128d &t2) {
    t2 = _mm_add_pd ( t0, t1);
}