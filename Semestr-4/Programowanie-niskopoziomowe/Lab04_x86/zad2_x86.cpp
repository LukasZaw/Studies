#include <iostream>

using namespace std;

int main()
{
    int n = 4;
    int* v = new int [n] { 1, 2, 3, 4 };

    __asm {
        mov ecx, n;
        mov esi, v

            petla :
                mov eax, [esi + 4 * ecx - 4]


            imul eax
            mov[esi + 4 * ecx - 4], eax
            dec ecx
            jnz petla


    }

    for (int i = 0; i < n; i++)
    {
        cout << v[i] << " ";
    }
    cout << endl;
}