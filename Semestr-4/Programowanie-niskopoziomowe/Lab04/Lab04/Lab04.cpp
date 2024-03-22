#include <iostream>

using namespace std;

extern "C" __int64 fun1(int* ,int );
extern "C" __int64 fun2(int* ,int* ,int );
extern "C" __int64 fun3(int*, int*, int);

int main()
{
    int N = 4; //r8
    int* v = new int [N] {1, 2, 3, 4}; //rcx
    int* u = new int [N] {5, 6, 7, 8}; //rdx

    cout << "Zadanie 1\n";
    cout << fun1(v, N) << endl;

    cout << "Zadanie 2\n";
    fun2(v, u, N);

    for (int i = 0; i < N; i++)
    {
        cout << v[i] << " ";
    }
    cout << endl;

    cout << "Zadanie 3\n";
    fun2(v, u, N);

    for (int i = 0; i < N; i++)
    {
        cout << v[i] << " ";
    }
    cout << endl;
}