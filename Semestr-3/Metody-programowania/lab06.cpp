#include <iostream>
#include <string>
using namespace std;

class osoba {
protected:
    string naz;
    int wi;

public:
    osoba() : naz(""), wi(0) {}
    osoba(const string& a1, int a2) : naz(a1), wi(a2) {}

    const string& nazwisko() const {
        return naz;
    }

    int liczba_lat() const {
        return wi;
    }

    void pokaz() const {
        cout << "Nazwisko: " << naz << ", Wiek: " << wi << endl;
    }
};

class pracownik : public osoba {
    string stan;
    double plac;

public:
    pracownik() : stan(""), plac(0.0) {}

    pracownik(const string& a1, int a2, const string& a3, const double& a4) : osoba(a1, a2), stan(a3), plac(a4) {}

    const string& stanowisko() const {
        return stan;
    }

    double placa() const {
        return plac;
    }

    void pokaz() const {
        osoba::pokaz();
        cout << "Stanowisko: " << stan << ", Płaca: " << plac << endl;
    }
};




int main(){
  #ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
  #endif

  cout << "\n#o\n";
  osoba os("Dolas", 26);
  os.pokaz();

  cout << "\np1#\n";
  const pracownik pr1("Dyzma", 35, "mistrz", 2222.0);
  cout << pr1.nazwisko() << "  " << pr1.liczba_lat()  << endl;
  cout << pr1.stanowisko() << "  " << pr1.placa() << endl;

  cout << "\n#p2\n";
  pracownik pr2(pr1);
  pr2.pokaz();

  cout << "\n#p3\n";
  pracownik pr3("Kos", 45, "kierownik", 4444.0);
  pr3.pokaz();
  cout << "#=\n";
  pr3 = pr2;
  pr3.pokaz();

  osoba* w = &os;
  cout <<"\n---=====***=====---\n";
  w->pokaz();

  w = &pr3;                             // Zastanów się jaki jest typ wskaźnika w
                                        // i adres jakiego obiektu przechowuje w tej chwili.
  cout <<"\n---=====***=====---\n";
  w->pokaz();                           // Teraz zastanów się z jakiego zasięgu wywoływana jest funkcja pokaz
                                        // ???_01
                                        // Spóbuj wywołać inne metody, które zdefiniowałeś

  cout <<"---====*****====---\n";
  cout <<"---=====***=====---\n";
  static_cast<pracownik*>(w)->pokaz();  // Jeśli pierwszy raz widzisz operator static_cast < new_type > ( expression )
                                        // poczytaj na jego temat: https://en.cppreference.com/w/cpp/language/static_cast

                                        // Jeśli zrobiłeś eksperyment ???_01
                                        // ???_02 powtórz go jeszcze raz dokonując konwersji wskaźnika w.
cout <<"\n\n";
/*
// */
}
