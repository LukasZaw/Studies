#include <iostream>

using namespace std;

void vec_avx_sub_float(float* t1, float* t2, float* t3, int n)
{
    __asm {
        mov ecx, n  //8
        shl ecx, 2  //
        mov esi, t1
        mov edi, t2
        mov edx, t3

        petla:
            sub ecx, 32
            vmovups ymm0, ymmword ptr[esi + ecx]
            vmovups ymm1, ymmword ptr[edi + ecx]
            vsubps ymm2, ymm1, ymm0             //Vector SUB Packed Single
            vmovups ymmword ptr[edx + ecx], ymm2
        jnz petla
    }
}

double vec_avx_mul_double(double* x, int n) {
    double wynik = 0;
    __asm {
        push esi
        push edi
        push ecx

        mov ecx, n
        shl ecx, 3
        mov esi, x

        petla:
            sub ecx, 32
            vmovupd ymm0, ymmword ptr[esi + ecx]
            vmovupd ymm1, ymmword ptr[esi + ecx]
            vmulpd ymm2, ymm1, ymm0
            vaddpd ymm3, ymm3, ymm2

        jnz petla
            vmovsd wynik, xmm3

        pop ecx
        pop edi
        pop esi
    }
    return wynik;
}



void mtx2_avx_sub_float(float** t1, float** t2, float** t3, int n, int m)
{
    __asm {
        mov eax, n

        petlaN:
            mov esi, t1
            mov esi, dword ptr[esi + 4 * eax - 4]
            mov esi, t2
            mov edi, dword ptr[edi + 4 * eax - 4]
            mov esi, t3
            mov edx, dword ptr[edx + 4 * eax - 4]

            mov ecx, m
            shl ecx, 2
            petlaM:
                sub ecx, 32
                vmovups ymm0, ymmword ptr[esi + ecx];
                vmovups ymm1, ymmword ptr[edi + ecx];
                vsubps ymm2, ymm1, ymm0;
                vmovups ymmword ptr[edx + ecx], ymm2;
            jnz petlaM;
            dec eax;
            jnz petlaN;
            pop edi;
            pop esi;
    }
}




int main()
{
    cout << "Odejmowanie wektorow float" << endl;
    const int n = 8;
    float t1[n] = { 1, 2, 3 ,4 ,5 ,6 ,7 ,8  };
    for (int i = 0; i < n; i++)
    {
        cout << t1[i] << "\t";
    }
    cout << endl;
    float t2[n] = { 5 ,2 ,3.3 ,24 ,1 ,5 ,1 ,2  };
    for (int i = 0; i < n; i++)
    {
        cout << t2[i] << "\t";
    }
    cout << endl;
    float t3[n]; 
    cout << endl;

    vec_avx_sub_float(t1, t2, t3, n);
    for (int i = 0; i < n; i++)
    {
        cout << t3[i] << "\t";
    }
    cout << endl;

    //mtx2_avx_sub_float(t1, t2, t3, n, m);
    cout << "Iloczyn skalarny wektora" << endl;

    int n1 = 8;
    double* x = new double[n1];
    for (int i = 0; i < n1; i++)
    {
        x[i] = i * 2;
        cout << x[i] << "\t";
    }
    cout << endl;

    cout << vec_avx_mul_double(x, n);
}