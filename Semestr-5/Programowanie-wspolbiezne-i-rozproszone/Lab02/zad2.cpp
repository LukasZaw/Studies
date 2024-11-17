#include <iostream>
#include <mpi.h>
using namespace std;
int main (int argc, char *argv[]){ 
    MPI_Init(&argc, &argv);
    

    int rank;
    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int number;

    if (rank == 0) {
        // Proces 0 pobiera liczbę od użytkownika
        std::cout << "Podaj liczbe typu int: ";
        std::cin >> number;

        // Wysłanie liczby do procesu 1
        MPI_Send(&number, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        // Odbiór liczby z ostatniego procesu
        MPI_Recv(&number, 1, MPI_INT, size - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        // Wyświetlenie wyniku
        std::cout << "Proces 0 otrzymal liczbe: " << number << std::endl;
    } 
    else {
        // Odbieranie liczby od poprzedniego procesu
        MPI_Recv(&number, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        // Dodanie 1 do liczby
        number += 1;

        // Jeśli nie jesteśmy ostatnim procesem, wysyłamy do następnego procesu
        if (rank < size - 1) {
            MPI_Send(&number, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
        }
        // Jeśli jesteśmy ostatnim procesem, wysyłamy do procesu 0
        else {
            MPI_Send(&number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        }
    }
    MPI_Finalize();
    return 0;
}