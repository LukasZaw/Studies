#include <iostream>
#include <cstdlib>
#include <math.h>  
#include <mpi.h>
#include <iomanip>

using namespace std;

// funkcja do scalkowania
double f(double x) {
    return sqrt(1 - x * x);
}

double trapez(double a, double b, int n) {
    double h = (b - a) / n;
    double sum = 0.5 * (f(a) + f(b));

    for (int i = 1; i < n; ++i) {
        sum += f(a + i * h);
    }

    return sum * h;
}
int main(int argc, char *argv[]) {

    double tBegin, tEnd;

    MPI_Init(&argc, &argv);
    int rank, size;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);  

    int n;
    


    double a = -1.0;
    double b = 1.0;

    



    if (rank == 0){
        cout << "Podaj liczbę przedziałów całkowania: ";
        cin >> n;

        tBegin = MPI_Wtime();

        double area = trapez(a, b, n);
        double pi = 2 * area;

        cout << fixed << setprecision(10) << "Przybliżona wartość liczby Pi: " << pi << endl;
        tEnd = MPI_Wtime();
        cout << fixed << setprecision(10) << "Czas działania: " << tEnd - tBegin << endl;
        
    }


    MPI_Finalize();
    return 0;
}