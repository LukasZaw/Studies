#include <iostream>
#ifdef _WIN32
  #include <windows.h>
#endif // _WIN32 and _WIN64 too

using namespace std;

class Adres{
    string miasto, ulica;
    int nr_bud;

    public:
        Adres(): miasto(""), ulica(""), nr_bud(0){}
        Adres(const string& a1, const string& a2, const int& a3 ): miasto(a1), ulica(a2), nr_bud(a3){}
        string& getMiasto() { return miasto; }
        ostream& view(ostream& out)const{
            return out << miasto << ", " << ulica << ", " << nr_bud << '\n';
        }

        friend  //????
        ostream& operator<< (ostream& out, const Adres& r);
};
ostream& operator<< (ostream& out, const Adres& r){ //????
    return r.view(out);
}

class Osoba{
    string imie;
    int wiek;
    Adres* adres;

    public:
        Osoba(): imie(""), wiek(0), adres(new Adres){}
        Osoba(const string& a1, int a2, const Adres& a3) : imie(a1), wiek(a2), adres(new Adres(a3)) {} //?
        Osoba(const Osoba& o) : imie(o.imie), wiek(o.wiek), adres(new Adres(*(o.adres))) {} //????

        Osoba& operator=(const Osoba& o) {
            if (this == &o) {
                return *this; // ?????
            }
            imie = o.imie;
            wiek = o.wiek;
            delete adres; 
            adres = new Adres(*(o.adres)); // ??????
            return *this;
        }

        ~Osoba() {
            delete adres;
        }

        string& miasto(){
            return adres->getMiasto(); // ?????
        }

        friend
        ostream& operator<< (ostream& out, const Osoba& o);
};
ostream& operator<< (ostream& out, const Osoba& o){
  out << "Imię: " << o.imie << ", Wiek: " << o.wiek << ", Adres: " << *o.adres;
  return out ;
}

int main(){
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif
    Adres* wsk = new Adres("Częstochowa", "Dąbrowskiego", 73);
    cout <<  wsk << '\n';
    cout << *wsk << '\n';

    Adres a1(*wsk);
    delete wsk;
    wsk = nullptr;

    const Adres* wsk1 = new Adres("Łódź", "Piotrkowska", 33);

    cout << a1 << '\n';
    cout << *wsk1 << '\n';

    Adres a2;
    cout << a2 << '\n';
    a2 = a1;
    cout << a2 << '\n';

    Osoba os1("Ala", 25, *wsk1);
    delete wsk1;

    cout << os1 << '\n';

    Osoba os2(os1);

    os1.miasto() = "Zmieniono miasto osoby 1.";
    cout << os1 << '\n';

    Osoba os3;
    cout << os3 << '\n';
    os3 = os2;

    os1.miasto() = "Drugi raz zmieniono miasto osoby 1.";
    cout << os1 << '\n';

    cout << os3 << '\n';

#ifdef _WIN32
    system("PAUSE");
#endif
    return 0;
}
