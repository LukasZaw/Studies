#include <iostream>
using namespace std;

extern "C" __int64 zad1(int);
extern "C" __int64 zad2(int, int, int, int);

int main()
{
    cout << "Zadanie 1\n";
    cout << zad1(5) << endl;

    cout << "Zadanie 2\n";
    cout << zad2(1,2,3,2) << endl;
}

