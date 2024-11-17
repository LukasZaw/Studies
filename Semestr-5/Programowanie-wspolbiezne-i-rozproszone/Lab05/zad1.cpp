#include <iostream>
#include <cmath>
#include <mpi.h>
#include <iomanip>

double calculatePi(int intervals) {
    double a = -1.0;
    double b = 1.0;
    double h = (b - a) / intervals;
    double sum = 0.0;

    for (int i = 1; i < intervals; ++i) {
        double x = a + i * h;
        sum += std::sqrt(1 - x * x);
    }

    double result = (h / 2) * (std::sqrt(1 - a * a) + 2 * sum + std::sqrt(1 - b * b));
    return 2 * result;
}

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);
    
    int intervals;
    double tBegin, tEnd;

    std::cout << "Podaj liczbę przedziałów całkowania: ";
    std::cin >> intervals;

    tBegin = MPI_Wtime();

    double pi = calculatePi(intervals);
    std::cout << std::fixed << std::setprecision(10) << "Przybliżona wartość liczby Pi: " << pi << std::endl;

    tEnd = MPI_Wtime();
    std::cout <<  std::fixed <<  std::setprecision(10) << "Czas działania: " << tEnd - tBegin <<  std::endl;

    MPI_Finalize();
    return 0;
}