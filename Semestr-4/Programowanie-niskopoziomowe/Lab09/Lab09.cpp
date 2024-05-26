#include <iostream>

using namespace std;

float fun_w1(float a, float b, float c, float d, float x)
{
    float y;
    __asm {
        fld d;                  //d
        fld x;                  //x; d
        fld st;                 //x; x; d
        fmul st, st(1);         //xx; x; d
        fld st(1);              //x; xx; x; d
        fmul st, st(1);         //xxx; xx; x; d
        fmul a;                 //axxx; xx; x; d
        faddp st(3), st;        //xx; x; axxx+d
        fmul b;                 //b*xx; x; axxx+d
        faddp st(2), st;        //x; axxx+b*xx+d
        fmul c;                 //c*x; axxx+b*xx+d
        fadd;                   //axxx+b*xx+c*x+d
        fstp y
    }
    return y;
}

float fun_w2(float r)
{
    float y;
    __asm {
        fld r               //r
        fld st              //r; r
        fmul st, st(1)      //r*r; r
        fmul                //r*r*r;
        fldpi               //pi; r^3
        fmul                //pi*r^3

        mov eax, 4
        push eax
        fild dword ptr[esp] //4; pi*r^3
        pop eax

        mov eax, 3
        push eax
        fild dword ptr[esp] //3; 4; pi*r^3
        pop eax
        
        fdiv        //4/3; pi*r^3
        fmul        //4/3*pi*r^3

        fstp y;
    }
    return y;
}


float fun_w3(float r)
{
    float y;
    __asm {
        fld r
        fld r
        fmul    //r*r
        fldpi   //pi; r*r
        fmul    //pi*r*r

        mov eax, 4
        push eax
        fild dword ptr[esp] //4; pi*r*r
        pop eax

        fmul 
        fstp y
    }
    return y;
}

float fun_w4(float a, float b, float c, float x)
{
    float y;
    __asm {
        fld c       //c
        fld b       //b; c
        fsub        //c-b
        fld a
        fmul        //a(c-b)

        fld b       //b; a(c-b)
        fld a       //a; b; a(c-b)
        fsub        //b-a; a(c-b)
        fld c       //c; b-a; a(c-b)
        fmul        //c(b-a); a(c-b)
        fadd        //c(b-a) + a(c-b)

        fld a       //a; c(b-a) + a(c-b)
        fld1        //1; a; c(b-a) + a(c-b)
        fsub        //a-1; c(b-a) + a(c-b)

        fld st      //a-1; a-1; c(b-a) + a(c-b)
        fmul st, st(1)//a-1*a-1; a-1; c(b-a) + a(c-b)
        fmul        //(a-1)^3; c(b-a) + a(c-b)

        fld x       //x; (a-1)^3; c(b-a) + a(c-b)
        fmul        //x*(a-1)^3; c(b-a) + a(c-b)
        fadd        //x*(a-1)^3 c(b-a) + a(c-b)
        fstp y      
    }
    return y;
}

float fun_pole(float a, float b, float c)
{
    float y;
    __asm {
       fld a
       fld b
       fmul     //a*b

       fld a
       fld c
       fmul    //a*c; a*b

       fld b
       fld c
       fmul    //b*c; a*c; a*b

       fadd
       fadd

       fld st
       fadd

       fstp y
    }
    return y;
}

double fun_w5(double* x, double* z, int N)
{
    double wynik;
    __asm {
        mov ecx, N; //rozmiar
        mov esi, x;
        mov edi, z;
        fldz

        label1:
            fld qword ptr[esi]; //x
            fld qword ptr[edi]; //z; x
            fmul
            fadd;
            add esi, 8; //kolejny element x
            add edi, 8; //kolejny element z
            dec ecx;
        jnz label1
        fstp wynik;
    }
    return wynik;
}

double fun_w6(double* x, int N)
{
    double wynik;
    __asm {
        mov eax, N
        mov esi, x
        
        fldz //0 - suma
        petla1:
            fld qword ptr[esi]//x; s
            fld st      //x; x; s
            fmul        //x*x; s
            fadd        //s
            add esi, 8
            dec eax
        jnz petla1

        fsqrt

        fstp wynik

    }
    return wynik;
}


int main()
{
    cout << "zadanie 1\n";
    cout << fun_w1(1.5, 1.6, 1, 1, 2) << endl;

    cout << "zadanie 2\n";
    cout << fun_w2(4) << endl;

    cout << "zadanie 3\n";
    cout << fun_w3(4) << endl;

    cout << "zadanie 4\n";
    cout << fun_w4(3.5,6.7,5,-4) << endl;
                 //a,  b,  c, x

    cout << "zadanie Pole\n";
    cout << fun_pole(2.2,3.3,4.4) << endl;

    int N = 4;

    double* x = new double[N];
    double* z = new double[N];

    for (int i = 0; i < N; i++)
    {
        x[i] = i+1;
        cout << x[i] << ", ";
    }
    cout << endl;
    for (int i = 0; i < N; i++)
    {
        z[i] = i + 2;
        cout << z[i] << ", ";
    }
    cout << endl;


    cout << "zadanie 5\n";
    cout << fun_w5(x,z,N) << endl;

    cout << "zadanie Dlugosc wektora \n";
    cout << fun_w6(x, N) << endl;
}

