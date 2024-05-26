#include <iostream>

using namespace std;

double wielomian_v0(double a, double b, double c, double d, double x)
{
    return a * x * x * x + b * x * x + c * x + d;
}

double wielomian_v1(double a, double b, double c, double d, double x)
{
    double wynik = 0;
    __asm
    {
        vmovsd xmm0, a;
        vmovsd xmm1, b;
        vmovsd xmm2, c;
        vmovsd xmm3, d;
        vmovsd xmm4, x;
        vmulsd xmm2, xmm2, xmm4 //cx
        vmulsd xmm5, xmm4, xmm4 //xx
        vmulsd xmm1, xmm1, xmm5 //bxx
        vmulsd xmm4, xmm4, xmm5 //xxx
        vmulsd xmm0, xmm0, xmm4 //axxx
        vaddsd xmm0, xmm0, xmm1 //axxx + bxx 
        vaddsd xmm0, xmm0, xmm2 //axxx + bxx + cx
        vaddsd xmm0, xmm0, xmm3 //axxx + bxx + cx + d

        vmovsd wynik, xmm0;
    }
    return wynik;
}

int main()
{
    cout << "Zadanie 1 - Wielomian\n";
    cout << wielomian_v0(2, 3, 4, 5, 2) << endl;
    cout << wielomian_v1(2, 3, 4, 5, 2) << endl;

}