#include <iostream>

using namespace std;

extern "C" __int64 szescian(int a);
extern "C" __int64 funk(int, int, int, int);

int main()
{
	int a = 2;
	int c;
	c = szescian(a);
	cout << "Szescian = " << c << endl;

	a = 2;
	int b = 1;
	c = 1;
	int x = 3;
	int wyn;
	
	//x		a	b	c
	//rcx, rdx, r8, r9
	wyn = funk(x, a, b, c);
	cout << "Wartosc = " << wyn << endl;


	system("PAUSE");
	return 0;
}