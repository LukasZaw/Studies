#include <iostream>
#include <utility> // move()
#include <string>

using namespace std;

class K1 {
public:
    K1() = default;

    // Konstruktor parametryczny biorący dwa stringi, tworzący nową tablicę i przypisującą wartość tych stringów
    K1(const string& str1, const string& str2) : p1(new string[2]{ str1, str2 }) {}

    // Konstruktor kopiujący tworzący nową tablicę i przypisujący wartości z innego obiektu K1 (jesli tablica w innym obiekcie K1 nie istnieje zostanie nadana wartosc nullptr)
    K1(const K1& inna) : p1(inna.p1 ? new string[2]{ inna.p1[0], inna.p1[1] } : nullptr) {}

    K1(K1&& inna)  {
        p1 = move(inna.p1);
        inna.p1 = nullptr;
    }

    ~K1() {
        delete[] p1;
    }

    K1& operator=(const K1& inna) {
        if (this != &inna) {
            delete[] p1;
            p1 = new string[2]{ inna.p1[0], inna.p1[1] };
        }
        return *this;
    }

    K1& operator=(K1&& inna)  {
        if (this != &inna) {
            delete[] p1;
            p1 = move(inna.p1);
            inna.p1 = nullptr;
        }
        return *this;
    }

    const string* GetP1() const {
        return p1;
    }

    friend ostream& operator<<(ostream& out, const K1& w1);

private:
    string* p1 = nullptr;
};

ostream& operator<<(ostream& out, const K1& w1) {
    const string* p1 = w1.GetP1();
    if (p1) {
        out << "[" << p1[0] << ", " << p1[1] << "]";
    }
    else {
        out << "nullptr";
    }
    return out;
}

class K2 {
public:
    K2() : w1("", ""), w2(0.0) {}

    K2(const string& str1, const string& str2, double val) : w1(str1, str2), w2(val) {}

    K2(const K2& k2) : w1(k2.w1), w2(k2.w2) {}

    K2(K2&& k2) : w1(move(k2.w1)), w2(k2.w2) {}

    ~K2() {}

    K2& operator=(const K2& k2) {
        if (this != &k2) {
            w1 = k2.w1;
            w2 = k2.w2;
        }
        return *this;
    }

    K2& operator=(K2&& k2)  {
        if (this != &k2) {
            w1 = move(k2.w1);
            w2 = k2.w2;
        }
        return *this;
    }

    double operator-(double l) {
        return w2 - l;
    }

    friend ostream& operator<<(ostream& out, const K2& k2);

private:
    K1 w1;
    double w2;
};

ostream& operator<<(ostream& out, const K2& k2) {
    out << "w1: " << k2.w1 << ", w2: " << k2.w2;
    return out;
}

int main()
{
    K2 ob1, ob2;
    const K2* wsk1 = new K2("kawa", "z mlekiem", 4.50);
    const K2 ob3(*wsk1);
    delete wsk1;
    wsk1 = 0;
    const K2* wsk2 = new K2(ob3);
    ob2 = *wsk2;
    cout << ob1 << " - " << wsk2;
    delete wsk2;
    wsk2 = 0;
    cout << ob2 << "";
    cout << ob2 - 1.25;

    return 0;
}
