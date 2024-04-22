#include <iostream>

using namespace std;

int main()
{
   
    int a = 5;
    int b = 3;
    int w = 0;

    cout << "Zadanie 1\n";
    __asm {
        mov ecx, a
        mov edx, b
        cmp ecx, edx
        jge prawda1

        jmp end1
        prawda1:
        mov w, 10
        end1:

    }
    cout << w << endl;

    cout << "Zadanie 2\n";
    __asm {
        mov ecx, a
        mov edx, b
        
        cmp ecx, edx
        jne skok2
            mov w, 0
        jmp end2

        skok2:
            imul ecx, edx
            mov w, ecx
        end2:

    }
    cout << w << endl;

    int x = 2;
    a = 5;
    b = 3;
    w = 63;
    int y1 = 0;

    cout << "SWITCH \n";
    __asm {
        push ebx
        push esi
        push edi

        mov eax, x
        mov ebx, a
        mov ecx, b
        mov esi, w

        cmp esi, 1
        je case1
        cmp esi, 2
        je case2
        cmp esi, 3
        je case3
        jmp default1

        case1:
            inc ecx
            mov y1, ecx
            jmp koniec1

        case2:
            imul eax, eax
            imul eax, ebx

            add eax, ecx
            mov y1, eax
            jmp koniec1
        case3:
            mov edi, eax
            dec eax
            imul eax, edi
            xor edx, edx
            mov esi, 2
            div esi
            mov y1, eax
            jmp koniec1
        default1:
            mov eax, 0
            mov y1, eax

        koniec1:
        pop ebx
        pop esi
        pop edi
    }
    cout << y1 << endl;
}
