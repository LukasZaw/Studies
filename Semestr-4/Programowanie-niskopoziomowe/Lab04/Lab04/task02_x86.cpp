// Task1_x64.cpp 

//Zadanie1
//Dana jest tablica warto?ci ca?kowitych (32 bity) o rozmiarze N. Podnie? do kwadratu ka?dy element tej tablicy.

#include <iostream>

using namespace std;

int main()
{
    int n = 4;
    int* v = new int [n] { 1, 2, 3, 4 };

    __asm {
        push esi
        mov ecx, n;
        mov esi, v

            petla :
        mov eax, [esi + 4 * ecx - 4]
            imul eax
            mov[esi + 4 * ecx - 4], eax
            dec ecx
            jnz petla
            pop esi

    }

    for (int i = 0; i < n; i++)
    {
        cout << v[i] << "\t";
    }
    cout << endl;
}