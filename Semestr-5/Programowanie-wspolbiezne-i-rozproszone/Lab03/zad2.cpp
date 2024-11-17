#include <mpi.h>
#include <iostream>
#include <unistd.h>
#include <cstdlib>

using namespace std;

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    MPI_Comm_size(MPI_COMM_WORLD, &size);   
    int source = rank;

    //sleep(rank);

    cout  << "Rank: " << rank << endl;

    int n;

    if(rank == 0)
    {
        cout << "Podaj rozmiar tablicy: ";
        cin >> n;
        for(int i = 0; i < size; i++ )
        {
            MPI_Send(&n, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
        }
    }

    MPI_Recv(&n, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    sleep(rank);
    srand((unsigned) time(NULL));

    int* tablica = new int[n];

    for (int i = 0; i < n; ++i) {
        tablica[i] = rand() % 10;
    }

    cout << "Wylosowana tablica: ";
    for (int i = 0; i < n; ++i) {
        cout << tablica[i] << " ";
    }
    cout << endl;

    int maks_lokalne = 0;
    for (int i = 0; i < n; ++i) {
        if(tablica[i] > maks_lokalne)
        {
            maks_lokalne = tablica[i];
        }
    }
    cout << "Maks lokalne:" << maks_lokalne << endl;

    int max;

    //MPI_Recv(&suma, 1, MPI_DOUBLE, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    
    MPI_Reduce(&maks_lokalne, &max, 1, MPI_INT, MPI_MAX, 1, MPI_COMM_WORLD);
    if(rank == 1){
        cout << "---- Maksimum: " << max << endl;
    }


    MPI_Finalize();
    return 0;
}