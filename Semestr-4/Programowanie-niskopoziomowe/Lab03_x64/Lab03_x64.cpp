#include <iostream>

using namespace std;

extern "C" __int64 if_1(int, int);
extern "C" __int64 if_4(int, int);
extern "C" __int64 case_2(int, int);
extern "C" __int64 for_1(int);
extern "C" __int64 silnia(int);
extern "C" __int64 while_1(int, int, int);
extern "C" __int64 zad3(int, int);
extern "C" __int64 zad4(int, int, int);
extern "C" __int64 zad6(int);


int for_11(int N)
{
    int wynik = 0;
    for (int i = 0; i < N; i++)
    {
        wynik += 2 * i;
    }
    return wynik;
}

int while_11(int a, int r, int max)
{
    int wynik;
    int w;
    wynik = a;
    w = a + r;
    while (w < max)
    {
        wynik += w;
        w += r;
    }
    return wynik;
}


int main()
{
    cout << "IF 1\n";
    cout << if_1(4, 9) << endl;

    cout << "IF 4\n";
    cout << if_4(2,5) << endl;

    cout << "CASE 2\n";
    cout << case_2(3, 6) << endl;

    cout << "FOR 1\n";
    cout << for_1(4) << endl;
    cout << for_11(4) << endl;

    cout << "Silnia\n";
    cout << silnia(5) << endl;

    cout << "While\n";
    cout << while_1(1,1,6) << endl;
    cout << while_11(1, 1, 6) << endl;

    cout << "Zadanie 3\n";
    cout << zad3(0, 0) << endl;

    cout << "Zadanie 4\n";
    cout << zad4(6, 2, 3) << endl;

    cout << "Zadanie 6\n";
    cout << zad6(5) << endl;
}