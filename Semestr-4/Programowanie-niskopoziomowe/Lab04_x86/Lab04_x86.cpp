
#include<iostream>

using namespace std;

int main()
{
    int n = 5;
    int* v = new int [n] { 43, 24, 54, 123, 545 };
    int x;

    //Zadanie 1
    //Podniesione do kwadratu
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
    //Parzyste do kwadratu
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
    //Co drugi wyzerowny
    /*__asm {
        push esi
        push ebx

        mov ecx, n
        mov esi, v
        xor ebx, ebx

        petla:
            mov [esi + 4 * ecx - 4], 0

            dec ecx
            dec ecx
            cmp ecx, 0
        jg petla


        pop esi
        pop ebx
    }*/

    //Zadanie 5
    //Minimum
    /*__asm {
        push esi
        push ebx

        mov ecx, n
        mov esi, v

        mov ebx, [esi + 4 * ecx - 4]

        petla:
            mov eax, [esi + 4 * ecx - 4]
            cmp ebx, eax
            jl skokMniejsze
                mov ebx, [esi + 4 * ecx - 4]


                skokMniejsze:
            dec ecx
        jnz petla

        mov x, ebx

        pop esi
        pop ebx
    }*/

    cout << "X: " << x << endl;
    for (int i = 0; i < n; i++)
    {
        cout << v[i] << " ";
    }
    cout << endl;
}
