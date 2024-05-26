#include <iostream>

using namespace std;

float suma(float** M, int m, int n) {
    float wynik;
    __asm {
        mov eax, n
        mov ebx, m
        mov esi, M

        fldz
        petlaM:
            mov edi, [esi + 4*eax - 4]
            mov ecx, ebx
            petlaN:
                fld dword ptr[edi + 4*ecx - 4]
                fadd
                dec ecx
            jnz petlaN
            dec eax
        jnz petlaM
        fstp wynik
    }
    return wynik;
}

void mno(float** M, float* v, float* wynik, int n) {
    __asm {
        mov eax, n
        mov esi, M
        mov ecx, v
        mov edx, wynik
        petlaM :
            fldz
            mov edi, [esi + 4 * eax - 4]
            mov ebx, n
            petlaN :
                fld dword ptr[edi + 4*ebx - 4]
                fmul dword ptr[ecx + 4*ebx - 4]
                fadd
                dec ebx
            jnz petlaN
            fstp [edx + 4 * eax - 4]
            dec eax
        jnz petlaM
        fstp wynik
    }
}

int pierwiastki(float a, float b, float c, float* x1, float* x2) {
    int roz = 0;
    __asm {
        fld a       //a
        fld c       //c; a
        fmul        //ac
        fadd st, st //2ac
        fadd st, st //4ac
        fld b       //b; 4ac
        fld st      //b; b; 4ac
        fmul        //b^2; 4ac
        fsubr       //b^2 - 4ac

        fldz        //0; b^2 - 4ac
        fcomip st, st(1) //b^2 - 4ac porownanie

        jz zero
        jc wieksze

        mniejsze:   //brak rozwiazan
            mov roz, 0
            jmp koniec

        wieksze:    //2 rozwiazania
            fld a       //a; b^2 - 4a
            fld st      //a; a; b^2 - 4a
            fadd        //2a; b^2 - 4a
            fld st(1)   //b^2 - 4a; 2a; b^2 - 4a
            fsqrt       //sqrt(d); 2a; b^2 - 4a
            fld b       //b; sqrt(d); 2a; b^2 - 4a
            fchs        //-b; sqrt(d); 2a; b^2 - 4a
            fadd       //-b - sqrt(d); 2a; b^2 - 4a
            fdivr       //-b - sqrt(d) / 2a; b^2 - 4a

            mov ecx, x1
            fstp dword ptr[ecx]//b^2 - 4a i x1 przenosi

            fld a       //a; b^2 - 4a
            fld st      //a; a; b^2 - 4a
            fadd        //2a; b^2 - 4a
            fld st(1)   //b^2 - 4a; 2a; b^2 - 4a
            fsqrt       //sqrt(d); 2a; b^2 - 4a
            fld b       //b; sqrt(d); 2a; b^2 - 4a
            fchs        //-b; sqrt(d); 2a; b^2 - 4a
            fsubr       //-b - sqrt(d); 2a; b^2 - 4a
            fdivr       //-b - sqrt(d) / 2a; b^2 - 4a

            mov ecx, x2
            fstp dword ptr[ecx]//b^2 - 4a i x2 przenosi
            mov roz, 2
            jmp koniec

        zero:   //1 rozwiazanie
            fld a       //a; b^2 - 4a
            fld st      //a; a; b^2 - 4a
            fadd        //2a; b^2 - 4a
            fld b       //b; 2a; b^2 - 4a
            fchs        //-b; 2a; b^2 - 4a
            fdivr       //-b/2a; b^2 - 4a

            mov eax, x1
            fst dword ptr[eax]
            mov eax, x2
            fstp dword ptr[eax]
        
            mov roz, 1
        koniec:
    }
    return roz;
}

void fun_wektor(float* x, float* y, int n) {
    __asm {
        mov eax, x
        mov ebx, y
        mov ecx, n

        petla :
        fld dword ptr[eax + 4 * ecx - 4]//x
            fld st      //x; x
            fld st      //x; x; x
            fmul        //x*x; x
            fsubr       //x*x - x
            fld1
            fadd        //x*x - x + 1
            fsqrt
            mov edx, 16
            push edx
            fild dword ptr[esp]
            pop edx
            fmul

            fstp dword ptr [ebx + 4 * ecx - 4]

            dec ecx
        jnz petla
    }
}

int main()
{
    cout << "== Suma elementow macierzy float ==" << endl;
    float n = 4;
    float m = 4;
    float** M = new float* [n];
    for (int i = 0; i < n; i++)
        M[i] = new float[m];



    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++) {
            M[i][j] = i + j * 2;
            cout << M[i][j] << "\t";
        }
        cout << endl;
    }

    cout << suma(M, m, n) << endl;

    cout << "== Mnozenia macierz przez wektor ==" << endl;

    float* v = new float[n];
    for (int i = 0; i < n; i++)
        v[i] = i + 1;

    float* wynik = new float[n];

    mno(M, v, wynik, n);

    for (int i = 0; i < n; i++)
        cout << wynik[i] << "\t";
    cout << endl;

    cout << "== Pierwiastki rownania kwadratowego ==" << endl;
    float x1 = 0;
    float x2 = 0;
    cout << "Liczba rozwiazan: " << pierwiastki(-3, -3, 6, &x1, &x2) << endl;

    cout << "x1, x2: " << x1 << " " << x2 << endl;


    cout << "== Funkcja na wektorze ==" << endl;

    float nn = 6;
    float* y = new float[nn];
    float* x = new float[nn];
    for (int i = 0; i < nn; i++)
    {
        x[i] = i * 2;
        cout << x[i] << "\t";
    }
    cout << endl;
    
    fun_wektor(x, y, nn);
    for (int i = 0; i < nn; i++)
    {
        cout << y[i] << "\t";
    }
    cout << endl;
}