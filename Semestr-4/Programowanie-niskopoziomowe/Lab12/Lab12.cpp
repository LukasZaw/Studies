#include <iostream>

using namespace std;

double max_float(float a, float b, float c) {
	double wynik;
	__asm {
		fld a		//a
		fld b		//b; a
		fcomi st, st(1)//5 <= 7
		jnc skok1
			fxch
		skok1:

			fld c		//c; max(b, a)
			fcomi st, st(1)//c <= max(b, a)
			jnc skok2	

				fxch
			skok2:
						//max(c,b,a)
		fstp wynik
	}

	return wynik;
}

double min_float(float a, float b, float c) {
	double wynik;
	__asm {
		fld a		//a
		fld b		//b; a
		fcomi st, st(1)//b > a
		jc skok1
			fxch

		skok1:
		fld c		//c; b; a
		fcomi st, st(1)//c > max
		jc skok2
			fxch
		skok2:
		fstp wynik
	}

	return wynik;
}

double fun3(double x) {
	double wynik;
	__asm {
		fld x		//x
		fldz		//0; x
		fcomip st, st(1)//0 ? x
		jc skok	//0 >= x
			fldln2
			fmul

		jmp koniec
		skok:	//0 < x
			fstp x
			fld1
			fld x
			fyl2xp1

		koniec:
		fstp wynik
	}

	return wynik;
}


int main()
{
	cout << "Zadanie 1 - max z 3 liczb float" << endl;
	cout << max_float(7, 5, 9.9) << endl;

	cout << "Zadanie 2 - min z 3 liczb float" << endl;
	cout << min_float(0.7, 3, 9) << endl;

	cout << "Zadanie 3 - obliczanie log dla x" << endl;
	cout << fun3(-3) << endl;
}