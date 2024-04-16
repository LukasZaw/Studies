#include <iostream>
#include <windows.h>

using namespace std;

extern "C" void dlugosc32(INT32**, INT32*, INT32, INT32);
int main()
{
	//Push i pop dla macierzy
	const int m = 5, n = 7;
	int** mm = new int* [m];
	int* v = new int[n];
	for (int i = 0; i < n; ++i) mm[i] = new int[n];
	for (int i = 0; i < m; ++i)
		for (int j = 0; j < n; ++j)
			mm[i][j] = i + j + 5;
	for (int i = 0; i < n; ++i) v[i] = i + 5;
	cout << "Wektor wejsciowy v:\n";
	for (int i = 0; i < n; ++i) cout << v[i] << " ";
	cout << "\n\nMacierz wejsciowa mm:\n";
	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < n; ++j)
			cout << mm[i][j] << " ";
		cout << endl;
	}
		/* Wersja C++
		for (int i = 0; i < m; ++i)
		for (int j = 0; j < n; ++j)
		mm[i][j] = sqrt(pow(mm[i][j], 2) + pow(v[j], 2));
		//*/

	dlugosc32(mm, v, m, n);		// z wykorzystaniem podprogramu pierwiastkujacego
	cout << "\n\nMacierz wyjsciowa mm:\n";
	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < n; ++j)
			cout << mm[i][j] << " ";
		cout << endl;
	}
	system("PAUSE");
	return 0;

	//
}
