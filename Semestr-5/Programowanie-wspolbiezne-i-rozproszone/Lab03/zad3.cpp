#include <mpi.h>
#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int n;

    if (rank == 0) {
        cout << "Podaj rozmiar tablicy n: ";
        cin >> n;
    }

    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

    sleep(rank);
    srand(time(nullptr) + rank);

    double* values = new double[n];
    for (int i = 0; i < n; ++i) {
        values[i] = (double)(rand() % 10);
    }

    cout << "Proces " << rank << " wylosował liczby: ";
    for (int i = 0; i < n; ++i) {
        cout << values[i] << " ";
    }
    cout << endl;

    double local_max = values[0];
    for (int i = 1; i < n; ++i) {
        if (values[i] > local_max) {
            local_max = values[i];
        }
    }

    double global_max;
    MPI_Reduce(&local_max, &global_max, 1, MPI_DOUBLE, MPI_MAX, 1, MPI_COMM_WORLD);

    if (rank == 1) {
        std::cout << "Maksymalna liczba wylosowana przez procesy to: " << global_max << std::endl;
    }

    delete[] values;

    MPI_Finalize();

    return 0;
}