#include <iostream>
using namespace std;

extern "C" __int64 zad2_32(int**, int**, int**, int, int);

int main()
{
    cout << "== Suma z warunkiem ==" << endl;
    int n1 = 3;
    int m1 = 4;

    cout << "Tab 1 \n";
    int** tab1 = new int* [n1];
    for (int i = 0; i < n1; i++)
        tab1[i] = new int[m1];

    int num = 0;
    for (int i = 0; i < n1; i++)
    {
        for (int j = 0; j < m1; j++)
        {
            tab1[i][j] = num;
            cout << tab1[i][j] << "\t";
            num++;
        }
        cout << endl;
    }

    cout << "Tab 2 \n";
    int** tab2 = new int* [n1];
    for (int i = 0; i < n1; i++)
        tab2[i] = new int[m1];

    for (int i = 0; i < n1; i++)
    {
        for (int j = 0; j < m1; j++)
        {
            tab2[i][j] = i + j * 2;
            cout << tab2[i][j] << "\t";
        }
        cout << endl;
    }

    cout << "Tab 3 \n";
    int** tab3 = new int* [n1];
    for (int i = 0; i < n1; i++)
        tab3[i] = new int[m1];

    for (int i = 0; i < n1; i++)
    {
        for (int j = 0; j < m1; j++)
        {
            tab3[i][j] = 0;
            cout << tab3[i][j] << "\t";
        }
        cout << endl;
    }

    zad2_32(tab1, tab2, tab3, n1, m1);

    cout << "Wynik:\n";
    for (int i = 0; i < n1; i++)
    {
        for (int j = 0; j < m1; j++)
        {
            cout << tab3[i][j] << "\t";
        }
        cout << endl;
    }
}
