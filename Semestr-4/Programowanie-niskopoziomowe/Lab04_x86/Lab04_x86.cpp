
#include<iostream>

using namespace std;

int main()
{
    int n = 4;
    int* v = new int [n] { 1, 2, 3, 4 };

    //Zadanie 1
    /*__asm {
        mov ecx, n
        mov ebx, v

        petla :
        mov eax, [ebx + 4 * ecx - 4]
            imul eax
            mov[ebx + 4 * ecx - 4], eax
            dec ecx
            jnz petla

    }*/

    //Zadanie 2
    /*__asm {
        push esi
        push ebx

        mov ecx, n
        mov esi, v


        mov ebx, 2
        

        petla:
            mov eax, [esi + 4 * ecx - 4]
            xor edx, edx
            idiv ebx
            cmp edx, 0
                jne skokNieZero

                mov eax, [esi + 4 * ecx - 4]
                mul eax
                mov [esi + 4 * ecx - 4], eax

                skokNieZero:
            dec ecx
            jnz petla


        pop esi
        pop ebx
    }*/

    //Zadanie 3
    __asm {
        push esi
        push ebx

        mov ecx, n
        mov esi, v



        pop esi
        pop ebx
    }


    for (int i = 0; i < n; i++)
    {
        cout << v[i] << " ";
    }
    cout << endl;
}
