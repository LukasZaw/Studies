#include <iostream>
#include <mpi.h>
#include <unistd.h>
#include <cstdlib>
#include <time.h>


using namespace std;

int main (int argc, char *argv[])
{
    MPI_Init(&argc, &argv);
    int rank, size;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);   

    int n;
    srand(time(NULL));

    int* tab_part = new int[size];

    int *tabA = nullptr, *tabB = nullptr, *tabC = nullptr;

    if(rank == 0)
    {
        cout << "Podaj rozmiar tablicy: ";
        cin >> n;

        tabA = new int[n];

        for (int i = 0; i < n; ++i) {
            tabA[i] = rand() % 10 + 10;
        }

        cout << "Wylosowana tablica A: ";
        for (int i = 0; i < n; ++i) {
            cout << tabA[i] << " ";
        }
        cout << endl;


        tabB = new int[n];
        tabC = new int[n];


        for (int i = 0; i < n; ++i) {
            tabB[i] = rand() % 100 + 100;
        }

        cout << "Wylosowana tablica B: ";
        for (int i = 0; i < n; ++i) {
            cout << tabB[i] << " ";
        }
        cout << endl;
    }

    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

    int local_size = n / size;
    int *local_A = new int[local_size];
    int *local_B = new int[local_size];
    int *local_C = new int[local_size];

    MPI_Scatter(tabA, local_size, MPI_INT, local_A, local_size, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(tabB, local_size, MPI_INT, local_B, local_size, MPI_INT, 0, MPI_COMM_WORLD);

    for (int i = 0; i < local_size; ++i) {
        local_C[i] = local_A[i] + local_B[i];
    }

    // for (int i = 0; i < local_size; ++i) {
    //     cout << local_C[i] << " ";
    // }
    // cout << endl;

    MPI_Gather(local_C, local_size, MPI_INT, tabC, local_size, MPI_INT, 0, MPI_COMM_WORLD);


    if(rank == 0){
        cout << "Tablica A + B = "; 
        for (int i = 0; i < n; ++i) {
            cout << tabC[i] << " ";
        }
    }


    MPI_Finalize();
    return 0;
}