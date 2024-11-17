#include <mpi.h>
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int size;
    double* values;

    if (rank == 0) {
        ifstream inputFile("zad3.txt");

        inputFile >> size;

        values = new double[size];

        for (int i = 0; i < size; ++i) {
            inputFile >> values[i];
        }
        inputFile.close();

        MPI_Send(&size, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);

        MPI_Send(values, size, MPI_DOUBLE, 1, 0, MPI_COMM_WORLD);

        double suma;
        MPI_Recv(&suma, 1, MPI_DOUBLE, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        cout << "Suma wartosci tablicy: " << suma << endl;
    } 
    else if (rank == 1) {
        MPI_Recv(&size, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        values = new double[size];

        MPI_Recv(values, size, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        double suma = 0.0;
        for (int i = 0; i < size; ++i) {
            suma += values[i];
        }

        MPI_Send(&suma, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}