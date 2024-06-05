#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
using namespace std;

class K1 {
    string *p1;

public:
    K1(): p1(new string[2]) {}

    K1(const string& a1, const string& a2): p1(new string[2]{a1, a2} ) {}
    // Konstruktor kopiujący
    K1(const K1 &other): p1(new string[2]) {
        p1[0] = other.p1[0];
        p1[1] = other.p1[1];
    }

    // Operator przypisania
    K1 &operator=(const K1 &other) {
        if (this != &other) {
            delete[] p1;
            p1 = new string[2];
            p1[0] = other.p1[0];
            p1[1] = other.p1[1];
        }
        return *this;
    }

    const string& pp0() const { return p1[0]; }
    const string& pp1() const { return p1[1]; }
    string& pp0() { return p1[0]; }
    string& pp1() { return p1[1]; }

    friend ostream& operator<< (ostream& out, const K1& k1);

    ~K1() {
        delete[] p1;
    }
};
    ostream& operator<< (ostream& out, const K1& k1){
      return out <<  k1.pp0() << " " << k1.pp1();
    }


class K2 {
    K1 w1;
    double w2;

public:
    K2(): w1("",""), w2(0){}
    K2(const string &s1, const string &s2, double d) : w1(), w2(d) {
        w1.pp0() = s1;
        w1.pp1() = s2;
    }

    // Konstruktor kopiujący
    K2(const K2 &other) : w1(other.w1), w2(other.w2) {}

    // Operator przypisania
    K2 &operator=(const K2 &other) {
        if (this == &other) {
            return *this;
        }
        w1 = other.w1;
        w2 = other.w2;
        return *this;
    }

    const double& ww2() const { return w2; }
    double& ww2() { return w2; }

    // Przeciążony operator dla wypisywania obiektu
    friend ostream &operator<<(ostream &out, const K2 &obj) {
        out << "K2: " << obj.w1 << ", " << obj.w2;
        return out;
    }
    friend istream& operator>>(istream& in, K2& t)
    {
       return in >> t.w1.pp0() >> t.w1.pp1() >> t.w2;
    }

    // Przeciążony operator odejmowania dla pola w2
    K2 operator-(double n) const {
        double t = ww2() - n;
        K2 temp(w1.pp0(), w1.pp1(), t);
        return temp;
    }
    K2& operator+=(const double& n){
      w2 +=  n;
      return *this;
    }
    K2 operator +(string a)
    {
        return K2(w1.pp0(), w1.pp1() + a, w2);
    }
    friend K2 operator +(string a,K2 t)
    {
        return K2(a+t.w1.pp0(), t.w1.pp1(), t.w2);
    }
};

int main(int argc,char *argv[]) {
    K2 ob1, ob2;

    // Inicjalizacja obiektu przy użyciu konstruktora
    const K2 *wsk1 = new K2("kawa", "z mlekiem", 4.50);
    // Inicjalizacja obiektu przy użyciu konstruktora kopiującego
    const K2 ob3(*wsk1);

    delete wsk1;
    wsk1 = nullptr;

    // Inicjalizacja obiektu przy użyciu konstruktora kopiującego
    const K2 *wsk2 = new K2(ob3);

    // Przypisanie obiektu
    ob2 = *wsk2;

    // Wypisanie obiektów
    cout << ob1 << endl;
    cout << *wsk2 << endl;

    delete wsk2;
    wsk2 = nullptr;

    // Wypisanie obiektu
    cout << ob2 << endl;

    // Operacja odejmowania dla pola w2
    cout << (ob2 - 1.25) << endl;


    K2 tab[4];
    ifstream file(argv[1]);
    for (int i = 0; i < 4; i++)
    {
        file >> tab[i];
        cout << tab[i] <<  endl;
    }

    for (int i = 0; i < 4; i++) {
        tab[i] += 1;
        cout << tab[i] << endl;
    }

    tab[1] = tab[1] + "with sugar";
    tab[3] = "hot" + tab[3];
    for (int i = 0; i < 4; ++i)
    {
        cout << tab[i] <<  endl;
    }
    /*
    */
    file.close();
    return 0;
}
