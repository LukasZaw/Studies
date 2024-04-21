#include <iostream>

using namespace std;

extern "C" __int64 poleKwad(int*, int);
extern "C" __int64 sumaTab(int*, int*, int);
extern "C" __int64 skalar(int*, int*, int);
extern "C" __int64 zad1(int*, int);
extern "C" __int64 zad2(int*, int);
extern "C" __int64 zad3(int*, int);
extern "C" __int64 zad4(int*, int);
extern "C" __int64 zad9(int*, int*, int*, int);
extern "C" __int64 zad8(int*, int*, int);



int main()
{
    static int N = 4;
    int* v = new int[N] {1, 2, 3, 4};
    int* u = new int[N] {1, 2, 2, 3};

    cout << "Pole Kwadratu" << endl;
    cout << poleKwad(v, N) << endl;

    cout << "Suma Tablic" << endl;
    sumaTab(v, u, N);
    for (int i = 0; i < N; i++)
        cout << v[i] << ", ";
    cout << endl;

    v = new int[N] {1, 2, 3, 4};
    cout << "Iloczyn skalarny" << endl;
    cout << skalar(v, u, N) << endl;

    cout << "Zadanie 1" << endl;
    zad1(v, N);
    for (int i = 0; i < N; i++)
        cout << v[i] << ", ";
    cout << endl;


    v = new int[N] {1, 2, 3, 4};
    cout << "Zadanie 2" << endl;
    zad2(v, N);
    for (int i = 0; i < N; i++)
        cout << v[i] << ", ";
    cout << endl;

    v = new int[N] {1, 2, 3, 4};
    cout << "Zadanie 3" << endl;
    zad3(v, N);
    for (int i = 0; i < N; i++)
        cout << v[i] << ", ";
    cout << endl;

    int* a = new int[N] {8, 7, 25, 90};
    int* b = new int[N] {2, 3, 5, 9};
    int* c = new int[N] {0, 0, 0, 0};
    cout << "Zadanie 9" << endl;
    zad9(a, b, c, N);
    for (int i = 0; i < N; i++)
        cout << c[i] << ", ";
    cout << endl;

    int* tab1 = new int[N] {8, 7, 2, 5};
    int* tab2 = new int[N] {2, 3, 5, 9};
    cout << "Zadanie 8" << endl;
    zad8(tab1, tab2,  N);
    for (int i = 0; i < N; i++)
        cout << tab1[i] << ", ";
}