#include <iostream>
#include <cmath>

using namespace std;

class point {
    double tab[3];

public:
    point() {
        for (int i = 0; i < 3; i++) {
            tab[i] = 0.0;
        }
    }

    point(double x, double y, double z) : tab{ x, y, z } {}

    point(const double (&arr)[3]) {
        for (int i = 0; i < 3; i++) {
            tab[i] = arr[i];
        }
    }

    double operator[](int index) const {
        return tab[index];
    }

    double &operator[](int index) {
        return tab[index];
    }

    double distance(const point &p) const {
        double sum = 0.0;
        for (int i = 0; i < 3; i++) {
            sum += (tab[i] - p[i]) * (tab[i] - p[i]);
        }
        return sqrt(sum);
    }

    const double* T3()const{ return tab; }

    point operator+(const point &p) const {
        return point(tab[0] + p[0], tab[1] + p[1], tab[2] + p[2]);
    }

    point operator-(const point &p) const {
        return point(tab[0] - p[0], tab[1] - p[1], tab[2] - p[2]);
    }

    point operator*(double pa) const {
        return point(tab[0] * pa, tab[1] * pa, tab[2] * pa);
    }

    // friend point operator*(double scalar, const point &p) {
    //     return p * scalar;
    // }

    // bool operator<(const point &p) const {
    //     double dist1 = distance(point());
    //     double dist2 = p.distance(point());
    //     return dist1 < dist2;
    // }

    // bool operator==(const point &p) const {
    //     for (int i = 0; i < 3; i++) {
    //         if (abs(tab[i] - p[i]) >= 1e-10) {
    //             return false;
    //         }
    //     }
    //     return true;
    // }

    friend istream &operator>>(istream &in, point &p) {
        for (int i = 0; i < 3; i++) {
            cout << "podaj punkt " << i+1 << ": ";
            in >> p[i];
        }
        return in;
    }

    friend ostream &operator<<(ostream &out, const point &p) {
        out << "(" << p[0] << ", " << p[1] << ", " << p[2] << ")";
        return out;
    }
};

point operator*(double scalar, const point &p) {
    return p * scalar;
}

bool operator==(const point &la, const point &pa) {
    return abs(la.distance(point()) -pa.distance(point())) < 1e-10;
}

bool operator<(const point &la, const point &pa){
    double dist1 = pa.distance(point());
    double dist2 = la.distance(point());
    return dist1 < dist2;
}

int main() {
    double x[2][3] = {{1.0, 1.0, 1.0}, {1.0, 2.0, 3.0}};
    // cout << *x[0]; cout << x[0][0];
    point p1(x[0]), p2(x[1]); //????
    const point p3(0.4, 0.2, 0.1);

    cout << p1 << ", " << p2 << '\n';
    cout << p3[0] << ' ' << p3[1] << ' ' << p3[2] << '\n';

    cout << p1.distance(point()) << endl;
    cout << p3.distance(p1) << endl;

    cout << "p1 + p2: "  << p1 + p2 << endl;
    cout << "p1 - p3: "  << p1 - p3 << endl;


    cout << "X * p2: " << 3.14 * p2 << endl;
    cout << "p2 * X: " << p2 * 3.14 << endl;

    cout << (p1 < p3) << endl;
    if(p1 == point(1.0, 1.0, 1.0)){
      cout << "Punkty sa rowne.\n";
    }
    else{
      cout << "Punkty sa rozne.\\n";
    }

    cout << "Podaj 3 punkty:\n";
    cin >> p1;
    cout << p1 << '\n';


      cout << "\n***e0**\n";
      point e0;
      cout << &e0 << '\n' << e0.T3() << '\n' << e0 << endl;

      cout << "\n***e1**\n";
      point e1(x[0]);
      cout << x << "  " << x[0] << "  (" << x[0][0] << ")  " << &x[0][0] << '\n';
      cout << &e1 << '\n' << e1.T3() << '\n' << e1 << endl;

      cout << "\n***e2**\n";
      point e2(e1);
      cout << &e2 << '\n' << e2.T3() << '\n' << e2 << endl;

      cout << "\n***e0**\n";
      e0 = e2;
      cout << &e0 << '\n' << e0.T3() << '\n' << e0 << endl;


    return 0;
}
