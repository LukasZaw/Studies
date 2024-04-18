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

    cout << "Zadanie 1\n";
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
}
