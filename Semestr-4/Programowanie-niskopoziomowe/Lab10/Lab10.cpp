#include <iostream>
using namespace std;

float fun_1(float x, float y)
{
    float wynik;
    __asm {
        fld y       //y
        fld x       //x; y
        fyl2x       //y*log2x niżej normalizacja do przedzialu <0, 1>

        fld st      //y*log2x; y*log2x
        frndint     //round(y*log2x), y*log2x   zaokraglenie do inta
        fsub st(1), st //round(y * log2x); y* log2x - round(y*log2x)
        fxch        //y* log2x - round(y * log2x); round(y*log2x);
        f2xm1       //2^(f) - 1; round(y*log2x)
        fld1        //1; 2^(f) - 1; round(y*log2x)
        fadd        //2^(f); round(y*log2x)
        fscale      //chuj wie co robi, tak trzeba
                    //x^y; round(y*log2x)
        fstp st(1)  //x^y
        fstp wynik
    }
    return wynik;
}

float fun_w1(float a, float b, float c, float d, float x)
{
    float wynik;
    __asm {
        fld b       //b
        fld x       //x; b
        fyl2x

        fld st
        frndint
        fsub st(1), st
        fxch
        f2xm1
        fld1
        fadd
        fscale      //x^b; rnd(log)
        fstp st(1)  //x^b

        fld a
        fmul        //a*x^b

        fld c       //c; a*x^b
        fld x       //x; c; a*x^b
        fyl2x
        fld st
        frndint
        fsub st(1), st
        fxch
        f2xm1
        fld1
        fadd
        fscale      //x^c; rnd(..); a*x^b
        fstp st(1)  //x^c; a*x^b

        fld b
        fmul        //b*x^c; a*x^b
        fsub        //a*x^b - b*x^c

        fld c       //c; a*x^b - b*x^c
        fld x       //x; c; a*x^b - b*x^c
        fmul        //c*x; a*x^b - b*x^c
        fadd        //a*x^b - b*x^c + c*x

        fld d
        fadd        //a*x^b - b*x^c + c*x + d
        fstp wynik
    }
    return wynik;
}

float fun_w2(float* x, float* y, int k, float a, float b, float p1, float p2, float min_x, float max_x)
{
    float buf = 180;
    float wynik;
    __asm {
        mov esi, x
        mov edi, y
        mov ecx, k  //rozmiar tab

        fld min_x           //minx
        fld max_x           //maxx; minx
        fsubrp st(1), st    //maxx - minx
        fild k              //k; maxx - minx
        fdivp st(1), st     //krok

        fld b
        fld p1
        fld p2
        fld buf             //180; p2; p1; b; krok
        fld max_x           //x; 180; p2; p1; b; krok

        petla:
            fldpi           //pi; x; 180; p2; p1; b; krok
            fmul st, st(3)  //pi*p2; x; 180; p2; p1; b; krok
            fmul st, st(1)  //x*pi*p2; x; 180; p2; p1; b; krok
            fdiv st, st(2)  //x*pi*p2 / 180; x; 180; p2; p1; b; krok
            fcos            //cos(x*pi*p2 / 180); x; 180; p2; p1; b; krok
            fmul st, st(5)  //b*cos(x*pi*p2 / 180); x; 180; p2; p1; b; krok

            fldpi;          //pi, b*cos(x*pi*p2 / 180); x; 180; p2; p1; b; krok
            fmul st, st(5); //pi*p1; b*cos(x*pi*p2 / 180); x; 180; p2; p1; b; krok
            fmul st, st(2); //pi * p1 * x; b*cos(x*pi*p2 / 180); x; 180; p2; p1; b; krok
            fdiv st, st(3); //(pi * p1 * x)/buf; b*cos(x*pi*p2 / 180); x; 180; p2; p1; b; krok
            fsin;           //sin((pi * p1 * x)/buf); b*cos(x*pi*p2 / 180); x; 180; p2; p1; b; krok
            fmul a;         //a * sin((pi * p1 * x)/buf); b*cos(x*pi*p2 / 180); x; 180; p2; p1; b; krok
            
            fadd            //a * sin((pi * p1 * x)/buf) + b*cos(x*pi*p2 / 180); x; 180; p2; p1; b; krok
            fstp [edi + 4 * ecx - 4]    // x; 180; p2; p1; b; krok => wynik do tablicy y
            fst [esi + 4 * ecx - 4]     // x; 180; p2; p1; b; krok => x do tablicy x
            fsub st, st(5)              //zmniejszenie x o krok
        dec ecx
        jnz petla
        fstp st(1)
    }
    return wynik;
}

float fun_sin(float kat)
{
    float wynik;
    __asm {
        fld kat     //kat
        fldpi       //pi; kat
        fmul        //pi*kat

        mov ecx, 180
        push ecx
        fild dword ptr[esp]
        pop ecx     //180; pi*kat
        fdiv        //180/ pi*kat

        fsin        //sin(180/ pi*kat)
        fstp wynik
    }

    return wynik;
}

float fun_tryg(float a, float b, float x)
{
    float wynik;
    __asm {
        fld a
        fldpi
        fmul

        mov ecx, 180
        push ecx
        fild dword ptr[esp]
        pop ecx     //180; pi*a
        fdiv        //pi*a/180 = alfa
        fld x       //x; alfa
        fmul        //x*alfa
        fld st      
        fmul        //(x*alfa)^2
        fsin        //sin((x*alfa)^2)

        fld b       //b
        fldpi       //pi; b
        fmul        //pi*b

        mov ecx, 180
        push ecx
        fild dword ptr[esp]
        pop ecx
        fdiv        //pi*b/180

        fld x
        fmul        //x*beta
        fcos        //cos(x*beta)
        fld st
        fmul        //cos2(x * beta); sin((x*alfa)^2)

        fsub


        fstp wynik
    }

    return wynik;
}

float fun_ctg(float a)
{
    float wynik;
    __asm {
        fld a       //a
        fldpi       //pi; a
        fmul        //pi*a

        mov ecx, 180
        push ecx
        fild dword ptr[esp]//180; pi*a
        pop ecx

        fdiv        //pi*a/180 = alfa
        fptan       //1; tan(alfa)
        fdivr       //1/tan = cot

        fstp wynik
    }

    return wynik;
}

float fun_6(double a, double b, double c, int i, int j, int k)
{
    float y;
    __asm {
        fldl2t      //log
        mov eax, 128
        push eax
        fild dword ptr[esp]//128; log
        pop eax
        fmul        //128*log
        
        fld c       //c; 128*log
        fld st      //c; c; 128*log
        fmul        //c^2; 128*log
        fild k      //k; c^2; 128*log
        fmul        //k*c^2; 128*log
        mov eax, 64
        push eax
        fild dword ptr[esp]//64; k*c^2; 128*log
        pop eax
        fmul        //64*k*c^2; 128*log
        fsubr       //64*k*c^2 - 128*log

        fld b       //b
        fld st      //b; b
        fld st      //b; b; b
        fmul        //b*b; b
        fmul        //b^3
        fild j      //j; b^3
        fmul        //j*b^3
        mov eax, 32
        push eax
        fild dword ptr[esp]//32; j*b^3
        pop eax
        fmul        //32*j*b^3

        fld a
        fld st
        fmul
        fld st
        fmul
        fild i
        fmul
        mov eax, 16
        push eax
        fild dword ptr[esp]//32; j*b^3
        pop eax
        fmul
        fadd

        fdivr
        fstp y
    }

    return y;
}


int main()
{
   cout << "zadanie x^y\n";
    cout << fun_1(3, 0.5) << endl;
    /*
    cout << "zadanie 1\n";
    cout << fun_w1(2, 3, 4, 2, 2) << endl;

    int k = 8;
    float* x = new float[k];
    float* y = new float[k];
    for (int i = 0; i < k; i++)
    {
        x[i] = 0;
        y[i] = 0;
    }
    float a = 2;
    float b = 3;
    float p1 = 4;
    float p2 = 2;
    float xmin = 2;
    float xmax = 10;


    cout << "zadanie 2\n";
    fun_w2(x, y, k, a, b, p1, p2, xmin, xmax);
    for (int i = 0; i < k; i++)
    {
        cout << x[i] << " = " << y[i] << endl;
    }*/

    cout << "zadanie 3 - Sin kata\n";
    cout << fun_sin(90) << endl;

    cout << "zadanie 4 - fun trygonometryczne\n";
    cout << fun_tryg(30, 60, 2) << endl;

    cout << "zadanie 5 - cotangens\n";
    cout << fun_ctg(60) << endl;

    cout << "zadanie 6 - obliczanie funkcji\n";
    cout << fun_6(2.5, 3.5, 4.5, 1, 2, 3) << endl;
}