#include <iostream>

using namespace std;

int main()
{
    int n = 4;
    int* v = new int [n] { 1, 2, 3, 4 };

    __asm {
        mov ecx, n
        mov ebx, v

            petla :
                mov eax, [ebx + 4 * ecx - 4]
                imul eax
                mov [ebx + 4 * ecx - 4], eax
                dec ecx
            jnz petla

    }

    for (int i = 0; i < n; i++)
    {
        cout << v[i] << " ";
    }
    cout << endl;
}
