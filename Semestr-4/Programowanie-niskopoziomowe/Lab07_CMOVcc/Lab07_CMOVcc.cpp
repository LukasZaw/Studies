#include <iostream>
#include <Windows.h>

using namespace std;

extern "C" void zad0(INT64* v1, INT64* v2, INT64* v3, INT64* v4, int n);
extern "C" __int64 zad1(int, int);

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
    
    cout << "Zadanie 1\n";
    cout << zad1(22, 8);

}