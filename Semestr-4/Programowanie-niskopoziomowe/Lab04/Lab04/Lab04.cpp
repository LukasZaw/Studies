#include <iostream>

using namespace std;

extern "C" __int64 fun1(int* ,int );
extern "C" __int64 fun2(int* ,int* ,int );
extern "C" __int64 fun3(int*, int*, int);

extern "C" __int64 fun01(int*, int);
extern "C" __int64 fun02(int*, int);

int main()
{
    int N = 4; //rdx
    int v1[4] = { 1,2,3,4 };
    int* v = new int [N] {1, 2, 3, 2}; //rcx
    int* u = new int [N] {3, 4, 5, 6}; 

    //cout << "Zadanie 1\n";
    //fun01(v1, N);

    cout << "Zadanie 2\n";
    fun02(v1, N);

    for (int i = 0; i < N; i++)
    {
        cout << v1[i] << " ";
    }
    cout << endl;
}