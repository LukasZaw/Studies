#include <iostream>
#include <iomanip>
#include <omp.h>

int main() {
    const int n =1024; // rozmiar tablicy
    double * tab = new double[n]; // tworzenie obietu w pamięci dla tablicy dynamicznej
    for(int i=0; i<n; ++i) tab[i] = 0.1; //wypełnianie tablicy
    double time; // zmienne dla pomiaru czasu
    double s1 = 0.0;
    double s2 = 0.0;
    double s3 = 0.0;
    double s4 = 0.0;
    double sum = 0.0;
    time = omp_get_wtime(); //pomiar czasu - start
    //poniższy fragment należy zmienić zgodnie z koncepcją z nagrania
    
    for(int t=0; t<n*n; ++t) {
        for(int i=0; i<n; i+=4) {
            s1+=tab[i];
            s2+=tab[i+1];
            s3+=tab[i+2];
            s4+=tab[i+3];
        }
    }
    sum = s1 + s2 + s3 + s4;
    time = omp_get_wtime() - time; //pomiar czasu - stop
    std::cout<<std::fixed;
    std::cout<<"1. suma = "<<std::setprecision(30)<<sum<<" ";
    std::cout<<"czas wykonania = "<<std::setprecision(3)<<time<<std::endl;
    delete [] tab; //kasowanie tablicy
    return 0;
}