
#include <iostream>

#include <mpi.h>

#include <cstdlib>

#include <cmath>

#include <iomanip>



using namespace std;



int main (int argc, char *argv[])

{ 

 MPI_Init(&argc, &argv);

 int rank,size,n;

 MPI_Comm_rank(MPI_COMM_WORLD, &rank);

 MPI_Comm_size(MPI_COMM_WORLD, &size);

 double tBegin, tEnd;

 



 double*tabA = new double[n];

 double*tabB = new double[n];

 double*tabC = new double[n];

 

 



 

 srand((unsigned) time(NULL));

 cout << "Podaj razmiar tab" << endl;

 cin >> n;

 for(int i=0; i<n; i++)

 {

 tabA[i] = static_cast<double>(rand())/RAND_MAX * 10 + 10;

 tabB[i] = static_cast<double>(rand())/RAND_MAX * 100 + 100;

 tabC[i] = 0.f;

 } 

 

 

 tBegin = MPI_Wtime();

 for (size_t i = 0; i < n; i++)

 {

 tabC[i] = tabA[i] + tabB[i];

 }



 

 tEnd = MPI_Wtime();

 cout << "Czas działania: " <<setprecision(10) << fixed <<tEnd - tBegin <<" s"<< endl;

 

 MPI_Finalize(); 

 return 0;

}