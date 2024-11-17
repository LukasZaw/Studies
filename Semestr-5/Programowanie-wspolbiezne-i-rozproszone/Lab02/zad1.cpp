#include <iostream>
#include <mpi.h>
using namespace std;

int main (int argc, char *argv[])
{
    MPI_Init(&argc, &argv);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    double number;

    if (rank == 0) {
        // Proces 0 pobiera liczbę od użytkownika
        std::cout << "Podaj liczbe typu double: ";
        std::cin >> number;

        // Wysłanie liczby do procesu 1
        MPI_Send(&number, 1, MPI_DOUBLE, 1, 0, MPI_COMM_WORLD);
    } 
    else if (rank == 1) {
        // Proces 1 odbiera liczbę od procesu 0
        MPI_Recv(&number, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        // Wyświetlenie otrzymanej liczby
        std::cout << "Proces 1 otrzymal liczbe: " << number << std::endl;
    }
    MPI_Finalize();
    return 0;
}
