#include <iostream>

using namespace std;

extern "C" __int64 sum(int, int);
extern "C" __int64 roz(int, int);
extern "C" __int64 mno(int, int);
extern "C" __int64 dzi(int, int);
extern "C" __int64 fun1(int, int, int, int);
extern "C" __int64 fun2(int, int, int);

int main()
{
	int x = -2;
	int a = 1;
	int b = 2;
	int c = 3;


	//cout << "suma: " << sum(a, b) << endl;
	//cout << "roznica: " << roz(a, b) << endl;
	//cout << "iloczyn: " << mno(a, b) << endl;
	//cout << "iloraz: " << dzi(a, b) << endl;
	
	cout << "Funkcja: " << fun1(x, a, b, c) << endl; //11
	cout << "Funkcja powinna zwacac: " << a * x * x + b * x + c << endl;

	int h = 4;

	cout << "Funkcja pole trapezu: " << fun2(a, b, h) << endl;
	cout << "Funkcja powinna zwacac: " << ((a + b)*h)/2 << endl;

	return 0;
}
