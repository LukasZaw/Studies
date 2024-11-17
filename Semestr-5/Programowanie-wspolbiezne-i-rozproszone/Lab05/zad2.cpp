#include <iostream>
#include <cstdlib>
#include <math.h>  
#include <mpi.h>
#include <iomanip>

using namespace std;

double calculatePartialPi(int start, int end, double h) {
    double partialSum = 0.0;
    for (int i = start; i < end; ++i) {
        double x = -1.0 + i * h;
        partialSum += sqrt(1 - x * x);
    }
    //cout << partialSum << endl;
    return partialSum;
}


int main(int argc, char *argv[]) {
    int n;
    int rank, size;
    double tBegin, tEnd;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);  


    if (rank == 0){
        cout << "Podaj liczbę przedziałów całkowania: ";
        cin >> n;
    }

    tBegin = MPI_Wtime();

    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

    double h = 2.0 / n;
    double local_n = n / size;

    double start = rank * local_n;
    double end = start + local_n;
    cout << start << " " << end << endl;


    double localSum = calculatePartialPi(start, end, h);
    //cout << localSum << endl;

    double globalSum = 0.0;
    MPI_Reduce(&localSum, &globalSum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    if (rank == 0) {
        globalSum = (h / 2) * (sqrt(1 - (-1.0) * (-1.0)) + 2 * globalSum + sqrt(1 - 1.0 * 1.0));
        double pi = 2 * globalSum;
        tEnd = MPI_Wtime();

        cout << fixed << setprecision(10) << "Wyliczona wartość Pi: " << pi << endl;
        cout << fixed << setprecision(10) << "Czas działania: " << tEnd - tBegin << endl;
    }

    MPI_Finalize();
    return 0;
}