#include<iostream>
#include<string>
#include<fstream>

using namespace std;

class K1
{
    string w1, w2;
    double w3;
public:
    K1(): w1(""), w2(""), w3(0){}
    K1(const string& s1, const string& s2, const double& d): w1(s1), w2(s2), w3(d){}
    K1(const K1& k1): w1(k1.w1), w2(k1.w2), w3(k1.w3){}

    string& ww1() {return w1; }
    string& ww2() {return w2; }
    double& ww3() {return w3; }

    const string& ww1() const {return w1; }
    const string& ww2() const {return w2; }
    const double& ww3() const {return w3; }

    friend ostream& operator<< (ostream& out, const K1& k1);
};

ostream& operator<< (ostream& out, const K1& k1)
{
    return out << k1.ww1() << ' ' << k1.ww2() << ' ' << k1.ww3();
}

class K2
{
    K1* p1;
public:
    K2(): p1(0){}
    K2(const string& s1, const string& s2, const double& d): p1(new K1(s1, s2, d)){}
    K2(const K1* k1): p1(new K1(*k1)){}
    K2(const K2& k2): p1(0)
    {
        p1 = new K1(*k2.p1);
    }

    K2& operator= (const K2& k2)
    {
        delete p1;
        p1 = new K1(*k2.p1);
        return *this;
    }

    K2 operator- (const double& n)
    {
        double t = p1->ww3() - n;
        return K2(p1->ww1(), p1->ww2(), t);
    }

    K2& operator+=(const double& n)
    {
        p1->ww3() += n;
        return *this;
    }

    friend K2 operator+(const string& s, const K2& k2);

    friend ostream& operator<< (ostream& out, const K2& k2);

};

K2 operator+(const string& s, const K2& k2)
{
    return K2(s + k2.p1->ww1(), k2.p1->ww2(),k2.p1->ww3());
}

ostream& operator<< (ostream& out, const K2& k2)
{
    return out << *k2.p1;
}

int main()
{
    K2 ob1, ob2;
    K1* wsk1 = new K1("kawa", " zmlekiem", 4.5);
    K2 ob3(wsk1);
    ob2 = ob3;
    K2* wsk2 = new K2(ob2);
    cout << ob2 << *wsk2 << '\n';

    cout << ob2 - 1.25 << '\n';

    ifstream read;
    read.open("dane.txt");
    K2 tab[4];
    for(int i = 0; i< 4;i++)
    {
        string a, b;
        double c;
        read >> a >> b >> c;
        tab[i] = K2(a,b,c);
        cout << tab[i] << '\n';
    }
    read.close();
}
