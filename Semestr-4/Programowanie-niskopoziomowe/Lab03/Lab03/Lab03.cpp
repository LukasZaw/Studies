#include <iostream>

using namespace std;

extern "C" __int64 if_1(int, int);
extern "C" __int64 if_2(int, int);
extern "C" __int64 if_3(int, int);
extern "C" __int64 switch_1(int, int);
extern "C" __int64 for_1(int);
extern "C" __int64 for_2(int); //a^2
extern "C" __int64 silnia(int); // !a


int main()
{
    int a = 4;  //rcx
    int b = 2; 
    int op = 3; //rdx
    int N = 4;
    //cout << a << " ? " << b << ": " << endl;

    //cout << for_2(a) << ", " << a*a; 

    cout << silnia(a) << endl;

}


