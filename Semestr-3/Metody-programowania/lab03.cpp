#ifdef _WIN32
  #include <windows.h>
#endif // _WIN32 and _WIN64 too
#include <iostream>
#include <cmath>

using namespace std;

class punkt{
    double x_, y_;

    public:
        punkt (): x_(0), y_(0) {};
        punkt (double a1, double a2): x_(a1), y_(a2) {};

        double& x() { return x_; }
        double& y() { return y_; }

        const double& x() const { return x_; }
        const double& y() const { return y_; }

        double odleglosc(const punkt& other) const {
            double dx = x_ - other.x();
            double dy = y_ - other.y();
            return sqrt(dx * dx + dy * dy);

        }

        friend ostream& operator<<(ostream& out, const punkt& p) {
            out << "(" << p.x_ << ", " << p.y_ << ")";
            return out;
        }
};


class wielobok {
    size_t roz;
    punkt* wsk;

    public:
        wielobok() : roz(0), wsk(nullptr) {} //????? wsk(new punkt)

        wielobok(const punkt* b, const punkt* e) : roz(e - b > 0 ? e - b : 0), wsk(roz ? new punkt[roz] : nullptr) { //????
          // cout << *(b+1) << " " << *(e+1) << endl;
        for (size_t i = 0; i < roz; ++i) {
            wsk[i] = b[i];
            }
        }

        wielobok(const wielobok& r) : roz(r.roz), wsk(new punkt[roz]) {
            for (size_t i = 0; i < roz; ++i) {
                wsk[i] = r.wsk[i];
            }
        }

        wielobok& operator=(const wielobok& r) {
            if (this != &r) {
                delete[] wsk;
                roz = r.roz;
                wsk = roz ? new punkt[roz] : nullptr; //??
                for (size_t i = 0; i < roz; ++i) {
                    wsk[i] = r.wsk[i];
                }
            }
            return *this;
        }

        ~wielobok() {
            delete[] wsk;
        }

        punkt& operator[](size_t i) {
            return wsk[i];
        }

        size_t ilosc() const {
            return roz;
        }

        double obwod() const {
            if (roz < 2) {
                return 0;
            }

            double obwod = 0;
            for (size_t i = 0; i < roz - 1; ++i) {
                obwod += wsk[i].odleglosc(wsk[i + 1]);
            }
            obwod += wsk[roz - 1].odleglosc(wsk[0]);

            return obwod;
        }

        friend ostream& operator<<(ostream& out, const wielobok& w) {
            out << "Wielobok[" << w.roz << "]: ";
            for (size_t i = 0; i < w.roz; ++i) {
                out << w.wsk[i] << " ";
            }
            return out;
        }
};



int main(){
    #ifdef _WIN32
        SetConsoleOutputCP(CP_UTF8);
    #endif

    punkt p(2, 3);
    cout << p.x() << ' ' << p.y() << '\n';
    p.x() = 1;
    p.y() = 1;
    cout << p.x() << ' ' << p.y() << '\n';
    cout << p.odleglosc( punkt() ) << "\n\n";

    const punkt t[] = { punkt(0, 0), punkt(0, 1), punkt(1, 1), punkt(1, 0) };
    for (size_t i = 0; i < sizeof(t) / sizeof(punkt); ++i) {
        cout << i + 1 << ")  " << t[i] << endl;
    }

    // cout << *(t+4) << endl;
    // cout << *t << endl;
    // cout << t[0] << ' ' << *(t) << ' ' << t[4] << ' ' << *(t+1) << endl;


    cout << "\n*****\n";
    wielobok w1(t, t + 4);
    cout << w1.obwod() << '\n';

    w1[1] = punkt(0.5, 0.5);
    cout << w1.obwod() << '\n';
    cout << "***\n\n";

    wielobok w2;
    w2 = wielobok(t, t + 3);
    cout << w2.obwod() << '\n';

    for (size_t i = 0; i < w2.ilosc(); ++i) {
        cout << w2[i].x() << ' ' << w2[i].y() << '\n';
    }

    cout << "\n*****\n";
    wielobok w3(w2);
    w3[1] = punkt(0, -1);
    w3[2] = punkt(-1, -1);
    for (size_t i = 0; i < w3.ilosc(); ++i) {
        cout << w3[i] << endl;
    }
    cout << "***\n\n";

    cout << "\n*****\n";
    cout << w2 << "\n" << w3 << "\n";
    cout << "*****\n";

    cout << w2.obwod() - w3.obwod() << "\n";

    cout << "*****\n";
    const punkt t1[] = { punkt(0, 0), punkt(0, 4), punkt(4, 0), punkt(4, 4), punkt(8,8) };
    wielobok w4(t1, t1+5);
    cout << w4 << "\n";
    cout << w4.obwod() << "\n\n";;
    return 0;
}
