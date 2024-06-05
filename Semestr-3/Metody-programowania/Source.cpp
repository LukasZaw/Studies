#include <iostream>
#include <ostream>
#include <string>
using namespace std;

class figura {
protected:
    string* colo;
    int wym;

public:
    ~figura() {
        delete colo;
    }
    figura() : colo(new string()), wym(0) {}
    figura(string a, int b) : colo(new string(a)), wym(b) {}
    figura(const figura& a) : colo(new string(*a.colo)), wym(a.wym) {}

    figura& operator=(const figura& ob) {
        if (this != &ob) {
            delete colo;
            colo = new string(*ob.colo);
            wym = ob.wym;
        }
        return *this;
    }

    virtual double pole() const = 0;
    virtual ostream& wypisz(ostream&) const = 0;
};

class kolo : public figura {
public:
    kolo() : figura() {}
    kolo(string a, int b) : figura(a, b) {}

    double pole() const {
        return 3.14 * wym * wym;
    }

    ostream& wypisz(ostream& out) const {
        return out << *colo << " " << wym;
    }
};

class prost : public figura {
protected:
    int wym2;

public:
    prost() : figura(), wym2(0) {}
    prost(string a, int b, int c) : figura(a, b), wym2(c) {}

    double pole() const {
        return wym * wym2;
    }

    ostream& wypisz(ostream& out) const {
        return out << *colo << " " << wym << " " << wym2;
    }
};

class prostop : public prost {
protected:
    int wym3;

public:
    prostop() : prost(), wym3(0) {}
    prostop(string a, int b, int c, int d) : prost(a, b, c), wym3(d) {}

    double pole() const {
        return wym * wym2 * wym3;
    }

    ostream& wypisz(ostream& out) const {
        return out << *colo << " " << wym << " " << wym2 << " " << wym3;
    }
};

ostream& operator<<(ostream& out, const figura& a) {
    return a.wypisz(out);
}

int main() {
    const kolo test1("czarny", 100);
    const prostop test2("szary", 2, 2, 2);
    figura* tab[5];
    tab[0] = new kolo("czerwony", 1);
    tab[1] = new kolo;
    tab[2] = new prost("niebieski", 1, 1);
    tab[3] = new prostop("zielony", 1, 1, 1);
    tab[4] = new prostop;

    for (int i = 0; i < 5; ++i) {
        cout << *tab[i] << "  pole: " << tab[i]->pole() << endl;
    }

    // Zwolnienie pami�ci
    for (int i = 0; i < 5; ++i) {
        delete tab[i];
    }

    return 0;
}
