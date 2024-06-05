#include <iostream>
#include <stdlib.h>
#include <omp.h>
int main() {

     // Utworzenie tablic
     const int n =1024*1024*128;
     double * A = new double[n];
     double * B = new double[n];
     double * C = new double[n];
     double * D = new double[n];
     double time;
     // Inicjalizacja danych
     for(int i=0; i<n; ++i) {
         A[i]=1.0*i;
         B[i]=2.0*i;
         C[i]=3.0*i;
         D[i]=4.0*i;
     }
    
     time = omp_get_wtime(); // pomiar czasu - start
     // Fragment do modyfikacji
     for(int i=0; i<n; ++i) {
         A[i] = A[i]+B[i];
         C[i] = A[i]+1.0;
         A[i] = D[i]+1.0;
     }
     time = omp_get_wtime() - time; // pomiar czasu - stop
     std::cout<<" czas wykonania = "<<time;
     std::cout<<" przykładowa wartość "<<A[0]<<std::endl;
    for(int i=0; i<10; ++i) {
         std::cout<<C[i]<<std::endl;
     }
     // Kasowanie danych
     delete [] A;
     delete [] B;
     delete [] C;
     delete [] D;

 return 0;
}