#include <iostream>

using namespace std;

int main()
{

    static int N = 4;
    int* v = new int[N] {6, 2, 3, 4};
    int* u = new int[N] {1, 2, 2, 3};
    int w;

    cout << "Zadanie 5\n";
    __asm {
        push esi
        push edi

        mov esi, v
        mov edi, N

        mov eax, [esi + 4*edi - 4]
        dec edi

        petla1:
            cmp eax, [esi + 4 * edi - 4]
            jle skok1
            mov eax, [esi + 4 * edi - 4]

            skok1:
            dec edi
        jnz petla1

        mov w, eax
        pop esi
        pop edi
    }
    cout << w << endl;

    cout << "Zadanie 5\n";
    __asm {
        push esi
        push edi
        push ebx

        mov esi, v
        mov edi, u
        mov edx, N

        


        petla2:
            mov eax, [edi + 4 * edx - 4]
            add [esi + 4 * edx - 4], eax

            dec edx
        jnz petla2

        pop ebx
        pop esi
        pop edi
    }
    for (int i = 0; i < N; i++)
        cout << v[i] << ", ";



    return 0;
}
