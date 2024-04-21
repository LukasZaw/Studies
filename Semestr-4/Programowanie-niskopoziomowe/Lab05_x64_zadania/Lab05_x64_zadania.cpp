#include <iostream>
using namespace std;

extern "C" __int64 zad2_32(int**, int**, int**, int, int);
extern "C" __int64 zad4(int**, int);
extern "C" __int64 zad5(int**, int);


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

    //zad2_32(tab1, tab2, tab3, n1, m1);

    cout << "Wynik:\n";
    for (int i = 0; i < n1; i++)
    {
        for (int j = 0; j < m1; j++)
        {
            cout << tab3[i][j] << "\t";
        }
        cout << endl;
    }

    cout << "== Kwardrat elementow nad przekatna ==" << endl;

    int n2 = 4;
    cout << "Tab 4 \n";
    int** tab4 = new int* [n2];
    for (int i = 0; i < n2; i++)
        tab4[i] = new int[n2];

    num = 1;
    for (int i = 0; i < n2; i++)
    {
        for (int j = 0; j < n2; j++)
        {
            tab4[i][j] = num;
            cout << tab4[i][j] << "\t";
            num++;
        }
        cout << endl;
    }

    zad4(tab4, n2);
    cout << "Wynik: " << endl;
    for (int i = 0; i < n2; i++)
    {
        for (int j = 0; j < n2; j++)
        {
            cout << tab4[i][j] << "\t";
        }
        cout << endl;
    }

    cout << "== Zerowanie co drugiego elementu (szchownica) ==" << endl;

    int n3 = 4;
    cout << "Tab 5 \n";
    int** tab5 = new int* [n3];
    for (int i = 0; i < n3; i++)
        tab5[i] = new int[n3];

    num = 1;
    for (int i = 0; i < n3; i++)
    {
        for (int j = 0; j < n3; j++)
        {
            tab5[i][j] = num * 3;
            cout << tab5[i][j] << "\t";
            num++;
        }
        cout << endl;
    }

    zad5(tab5, n3);
    cout << "Wynik: " << endl;
    for (int i = 0; i < n3; i++)
    {
        for (int j = 0; j < n3; j++)
        {
            cout << tab5[i][j] << "\t";
        }
        cout << endl;
    }
}
