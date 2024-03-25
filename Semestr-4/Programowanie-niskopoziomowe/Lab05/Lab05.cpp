#include <iostream>
#include <windows.h>
using namespace std;

//suma elementów macierzy typu int 
extern "C" INT64 suma32(int**, int, int);
//suma elementow macierzy typu int64
extern "C" INT64 suma64(INT64**, INT64, INT64);
//Iloczyn macierzy i wektora dla wartości typu INT64
extern "C" INT64 uemxv(INT64**, INT64*, INT64*, INT64, INT64);


int main()
{
    //Suma elementow INT
    int n = 3;
    int m = 4;
    int** tab1 = new int* [n];

    for (int i = 0; i < n; i++)
    {
        tab1[i] = new int[m];
        for (int j = 0; j < m; j++)
        {
            tab1[i][j] = 1+ j;
        }
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cout << tab1[i][j] << " ";
        }
        cout << endl;
    }

    cout << suma32(tab1, n, m) << endl;


    //Suma elementow INT64
    cout << "INT64 - zad 1" << endl;
    INT64 n1 = 3;
    INT64 m1 = 4;
    INT64** tab = new INT64 * [n];

    for (INT64 i = 0; i < n; ++i)
    {
        tab[i] = new INT64[m];
        for (int j = 0; j < m; ++j)
        {
            tab[i][j] = i + j + 1;
        }
    }

    for (INT64 i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            cout << tab[i][j] << " ";
        }
        cout << endl;
    }

    cout << suma64(tab, n1, m1) << endl;

    //Iloczyn macierzy i wektora dla wartości typu INT64 i zapisanie do innego wektora
    cout << "INT64 - zad 2" << endl;
    INT64 n2 = 3;
    INT64 m2 = 4;
    INT64** tab2 = new INT64 * [n2];
    INT64* v2 = new INT64[n2];
    INT64* u2 = new INT64[m2];
    
    for (INT64 i = 0; i < n2; i++)
    {
        tab2[i] = new INT64[m2];
        for (int j = 0; j < m2; j++)
        {
            tab2[i][j] = 1;
        }
    }


    for (INT64 i = 0; i < m2; i++)
    {
        v2[i] = 2;
    }
    for (INT64 i = 0; i < n2; i++)
    {
        u2[i] = 0;
    }
    uemxv(tab2, v2, u2, n2, m2);

    for (INT64 i = 0; i < n2; i++)
    {
        cout << u2[i] << " ";
    }
}
