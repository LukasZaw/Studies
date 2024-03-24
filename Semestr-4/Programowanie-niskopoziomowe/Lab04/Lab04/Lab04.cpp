#include <iostream>

using namespace std;

extern "C" __int64 fun1(int* ,int );
extern "C" __int64 fun2(int* ,int* ,int );
extern "C" __int64 fun3(int*, int*, int);

extern "C" __int64 fun01(int*, int);
extern "C" __int64 fun02(int*, int);
extern "C" __int64 fun03(int*, int*, int*, int);

int main()
{
    int N = 4; //rdx
    int v1[4] = { 1,5,3,4 };
    int* v = new int [N] {1, 2, 3, 2}; //rcx
    int* u = new int [N] {3, 4, 5, 6}; 

    int n1 = 4; //r9
    int* a = new int [n1] {3, 4, 5, 6}; //rcx
    int* b = new int [n1] {1, 4, 1, 2}; //rdx
    int* c = new int [n1] {0, 0, 0, 0}; //r8
    

    //cout << "Zadanie 1\n";
    //fun01(v1, N);

    //cout << "Zadanie 6\n";
    //cout << "Max: " << fun02(v, N) << endl;
    //Maksimum

    cout << "Zadanie 9\n";
    fun03(a, b, c, n1);

    for (int i = 0; i < N; i++)
    {
        cout << c[i] << " ";
    }
    cout << endl;
}