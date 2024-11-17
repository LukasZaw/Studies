#include <mpi.h>
#include <iostream>
#include <unistd.h> // dla funkcji sleep()
#include <cstdlib>  // dla funkcji rand(), srand()
#include <ctime>    // dla funkcji time()

int main(int argc, char** argv) {
    // Inicjalizacja MPI
    MPI_Init(&argc, &argv);

    // Pobranie liczby procesów oraz ID procesu
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    // Uśpienie procesu na czas równy jego identyfikatorowi
    sleep(world_rank);

    // Inicjalizacja generatora liczb losowych
    srand(time(nullptr) + world_rank);

    // Losowanie liczby rzeczywistej z przedziału <0, 10>
    double random_number = (double)(rand() % 11); // Liczby całkowite 0-10

    // Wypisanie wylosowanej liczby przez każdy proces
    std::cout << "Proces " << world_rank << " wylosował liczbę: " << random_number << std::endl;

    // Redukcja do maksymalnej wylosowanej liczby
    double max_number;
    MPI_Reduce(&random_number, &max_number, 1, MPI_DOUBLE, MPI_MAX, 1, MPI_COMM_WORLD);

    // Proces 1 wypisuje maksymalną liczbę
    if (world_rank == 1) {
        std::cout << "Maksymalna liczba wylosowana przez procesy to: " << max_number << std::endl;
    }

    // Finalizacja MPI
    MPI_Finalize();

    return 0;
}