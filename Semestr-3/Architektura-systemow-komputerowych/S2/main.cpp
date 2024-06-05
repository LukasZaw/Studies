#include <iostream>
#include <stdlib.h>
#include <omp.h>
#include "f1.h"
#include "f2.h"
#include "f3.h"
int main() {
    const int n =1024*1024*1024;
    double *t0 = (double*)aligned_alloc(64, n*sizeof(double));
    double *t1 = (double*)aligned_alloc(64, n*sizeof(double));
    double *t2 = (double*)aligned_alloc(64, n*sizeof(double));
    
    for(int i=0; i<n; ++i) {
        t0[i] = i * 1.0;
        t1[i] = i*3.0;
        t2[i] = 0.0;
    }
    
    double time;
    
    time = omp_get_wtime();
    for(int i=0; i<n; ++i)
        scalar_add(t0[i],t1[i],t2[i]);
    time = omp_get_wtime() - time;
    std::cout<<time<<" czas wykonania obl. skalarnych"<<std::endl;
    
    time = omp_get_wtime();
    for(int i=0; i<n; i+=2)
        sse_add(*(__m128d*)&t0[i],*(__m128d*)&t1[i],*(__m128d*)&t2[i]);
    time = omp_get_wtime() - time;
    std::cout<<time<<" czas wykonania obl. wektorowych see"<<std::endl;
    
    time = omp_get_wtime();
    for(int i=0; i<n; i+=4)
        avx_add(*(__m256d*)&t0[i],*(__m256d*)&t1[i],*(__m256d*)&t2[i]);
    time = omp_get_wtime() - time;
    std::cout<<time<<" czas wykonania obl. wektorowych avx"<<std::endl;
    
    free(t0);
    free(t1);
    free(t2);
    return 0;
}