#include <iostream>
#include <mpi.h>
#include <unistd.h>
#include <cstdlib>
#include <time.h>
#include <iomanip>

using namespace std;

int main (int argc, char *argv[])
{
    MPI_Init(&argc, &argv);
    int rank, size;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);   

    int n;
    srand(time(NULL));

    // Zmiana typu tablic na double
    double* tab_part = new double[size];

    double *tabA = nullptr, *tabB = nullptr, *tabC = nullptr;

    if(rank == 0)
    {
        cout << "Podaj rozmiar tablicy: ";
        cin >> n;

        tabA = new double[n];

        for (int i = 0; i < n; ++i) {
            tabA[i] = rand() % 10 + 10 + (rand() % 100) / 100.0; // Zmiana na double z losową częścią dziesiętną
        }

        // cout << "Wylosowana tablica A: ";
        // for (int i = 0; i < n; ++i) {
        //     cout << tabA[i] << " ";
        // }
        // cout << endl;


        tabB = new double[n];
        tabC = new double[n];

        for (int i = 0; i < n; ++i) {
            tabB[i] = rand() % 100 + 100 + (rand() % 100) / 100.0; // Zmiana na double z losową częścią dziesiętną
        }

        // cout << "Wylosowana tablica B: ";
        // for (int i = 0; i < n; ++i) {
        //     cout << tabB[i] << " ";
        // }
        // cout << endl;
    }

    double tBegin, tEnd;


    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

    int local_size = n / size;
    double *local_A = new double[local_size];
    double *local_B = new double[local_size];
    double *local_C = new double[local_size];

    MPI_Scatter(tabA, local_size, MPI_DOUBLE, local_A, local_size, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Scatter(tabB, local_size, MPI_DOUBLE, local_B, local_size, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    MPI_Barrier(MPI_COMM_WORLD);

    tBegin = MPI_Wtime();


    for (int i = 0; i < local_size; ++i) {
        local_C[i] = local_A[i] + local_B[i];
    }

    MPI_Gather(local_C, local_size, MPI_DOUBLE, tabC, local_size, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    if(rank == 0){
        //cout << "Tablica A + B = "; 
        /*for (int i = 0; i < n; ++i) {
            cout << tabC[i] << " ";
        }*/
        tEnd = MPI_Wtime();
        cout << fixed << setprecision(10) << " --- Czas działania: " << tEnd - tBegin << endl;
    }

    MPI_Finalize();
    return 0;
}
