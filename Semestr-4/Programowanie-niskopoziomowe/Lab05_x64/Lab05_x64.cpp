#include <iostream>
#include <windows.h>

using namespace std;

extern "C" __int64 suma32(int**, int, int);
extern "C" __int64 suma64(INT64**, INT64, INT64);
extern "C" INT64 uemxv(INT64**, INT64*, INT64*, INT64, INT64);
extern "C" void sumaMeUpV(INT64**, INT64**, INT64**, INT64, INT64);

int main()
{
    
    cout << "== Suma elementow macierzy - x64 ==" << endl;
    int n = 3;
    int m = 4;
    int** v = new int* [n];
    for (int i = 0; i < n; i++)
        v[i] = new int[m];
        
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
            v[i][j] = i + j + 1;
    }

    cout << suma32(v, n, m) << endl;
    

    cout << "== Suma dla macierzy wartości typu INT64 ==" << endl;
    INT64 n1 = 4;
    INT64 m1 = 3;
    INT64** v1 = new INT64 * [n1];
    for (int i = 0; i < n1; i++)
        v1[i] = new INT64[m1];

    for (int i = 0; i < n1; i++)
    {
        for (int j = 0; j < m1; j++)
            v1[i][j] = i + j + 1;
    }
    cout << suma64(v1, n1, m1) << endl;

    cout << "== Iloczyn macierzy i wektora dla wartosci typu INT64 ==" << endl;
    INT64 k = 4;
    INT64 l = 3;
    INT64** vv = new INT64 * [k];
    for (int i = 0; i < k; i++)
        vv[i] = new INT64[m1];

    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < l; j++)
            vv[i][j] = i + j + 1;
    }
    INT64* u = new INT64[k]{1, 1, 1};
    INT64* y = new INT64[l]{0,0,0,0};

    uemxv(v1, u, y, k, l);
    

    cout << "Wynik:" << endl;
    for (int i = 0; i < l; i++)
    {
         cout << y[i] << "  ";
    }


    cout << "\n\n== Suma macierzy dwuwymiarowych dla wartości typu INT64 ==" << endl;
    INT64 a = 5;
    INT64 b = 4;
    INT64** qwe = new INT64 * [a];
    INT64** asd = new INT64 * [a];
    INT64** zxc = new INT64 * [a];

    for (int i = 0; i < a; i++)
    {
        qwe[i] = new INT64[b];
        asd[i] = new INT64[b];
        zxc[i] = new INT64[b];
    }

    for (int i = 0; i < a; i++)
    {
        for (int j = 0; j < b; j++) 
        {
            qwe[i][j] = i + j + 1;
            asd[i][j] = (i + j) * 2;
        }
    }
    sumaMeUpV(qwe, asd, zxc, a, b);

    for (int i = 0; i < a; i++)
    {
        for (int j = 0; j < b; j++)
            cout << zxc[i][j] << "\t";
        cout << endl;
    }
}
