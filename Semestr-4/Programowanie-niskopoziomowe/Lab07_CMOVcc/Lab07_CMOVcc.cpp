#include <iostream>
#include <Windows.h>

using namespace std;

extern "C" void zad0(INT64* v1, INT64* v2, INT64* v3, INT64* v4, int n);
extern "C" __int64 zad1(int, int);
extern "C" __int64 zad2(int, int, int);
extern "C" __int64 zad3(int, int);
extern "C" __int64 zad4(int**, int);
extern "C" __int64 zad5(int, int);



int main()
{
    cout << "Zadanie 0 \n";
    static int N = 4;
    INT64* v1 = new INT64[N] {1, 2, 3, 4};
    INT64* v2 = new INT64[N] {7, 3, 2, 8};
    INT64* v3 = new INT64[N] {5, 6, 7, 3};
    INT64* v4 = new INT64[N] {10, 5, 8, 2};
    zad0(v1, v2, v3, v4, N);
    for (int i = 0; i < N; i++)
        cout << v4[i] << ", ";
    cout << endl;
    
    cout << "Zadanie 1 - MAX\n";
    cout << zad1(22, 8) << endl;

    cout << "Zadanie 2 - MIN\n";
    cout << zad2(9, 8, 2) << endl;

    cout << "Zadanie 3 - IF\n";
    cout << zad3(9, 12) << endl;

    cout << "Zadanie 4 - MACIERZ\n";
    int n = 4;
    int** tab1 = new int* [n];
    for (int i = 0; i < n; i++)
        tab1[i] = new int[n];

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            tab1[i][j] = (i + j + 6);
            cout << tab1[i][j] << "\t";
        }
        cout << endl;
    }

    zad4(tab1, n);
    cout << "Wynik: \n";
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            cout << tab1[i][j] << "\t";
        cout << endl;
    }

    cout << "Zadanie 3 - IF 2\n";
    cout << zad5(2, 2) << endl;
}