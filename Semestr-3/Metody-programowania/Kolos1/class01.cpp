#include <iostream>

using namespace std;

class dupa {
    string x_;
    double y_;

public:
    // Konstruktor domyslny
    dupa (): x_(""), y_(0) {}

    //Konstruktor z argumentami
    dupa (const string& a1,const double& a2): x_(a1), y_(a2) {}

    //Metoda dostępu poprzez referecje do pola prywatnego(modyfikacja)
    string& x() { return x_; }

    //Stała metoda dostępu
    const string& x() const { return x_; }

    // Metoda publiczna
    void wypisz() {
        cout << x_ << ", " << y_ << endl;
    }

    // Destruktor
    ~dupa() {
        cout << "~dupa() Destruktor wywolany" << endl;
    }
};

int main() {
    dupa xd("cos asd", 12); // Tworzenie obiektu klasy
    xd.wypisz();
    cout << "Wartość pola x: " << xd.x() << endl;
    xd.x() = "coscos123"; // Wywołanie metody publicznej

    cout << xd.x() << endl;

    return 0;
}
