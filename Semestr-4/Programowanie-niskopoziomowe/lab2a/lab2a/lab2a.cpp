#include <iostream>

using namespace std;

int main()
{
    cout << "Hello World!\n";

    unsigned short a = 12;
    unsigned short b = 5;
    unsigned short result = 0;

    //__asm {
    //    xor eax, eax;   //zerowanie rejestru eax(32 bity)
    //    mov ax, g;      //kopia g do ax (16 bity)
    //    inc ax;         //zwiekszenie ax 69+1
    //    mov ebx, eax;   //kopia eax do ebx
    //    mov gg, bx;     //kopia bx do gg

    //    mov ax, g;      //kopia g do ax
    //    add ax, ggg;    //dodanie do ax ggg
    //    mov ggg, ax;    //zapisanie ggg do ax
    //}
    
    //suma
    __asm {
        mov ax, a;
        add ax, b;
        mov result, ax;
    }
    cout << a << " + " << b << " = " << result << endl;

    //roznica
    __asm {
        mov ax, a;
        sub ax, b;
        mov result, ax;
    }
    cout << a << " - " << b << " = " << result << endl;

    //mnozenie
    __asm {
        xor eax, eax;
        mov ax, a;
        mov bx, b;
        mul bx;         //mnozenie bx przez ax czyli akumulator
        mov result, ax;
    }
    cout << a << " * " << b << " = " << result << endl;


    //dzielenie 
    __asm {
        mov ax, a;
        mov bx, b;
        xor dx, dx;      // Wyczyść rejestr DX, aby zapewnić 0 w części wyższej wyniku dzielenia
        div bx;          // Podziel zawartość rejestru AX przez zawartość rejestru BX; wynik zostanie zapisany w AX
        mov result, ax;  // Zapisz wynik do zmiennej result
    }
    cout << a << " / " << b << " = " << result << endl;

    return 0;
}

