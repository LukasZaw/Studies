#include<iostream>
#include<string>

using namespace std;


class adres{
    string mia, ul;
    int nr;

  public:
    adres(): mia("brak"), ul("brak"), nr(0) {}
    adres(const string& a1, const string& a2, int a3): mia(a1), ul(a2), nr(a3) {}

    ostream& view(ostream& out) const{
      return out << mia << ", " << ul << ", " << nr << '\n';
    }

    string& miasto(){
      return mia;
    }

    friend ostream& operator<< (ostream& out, const adres& r);
};

ostream& operator<< (ostream& out, const adres& r){
    return r.view(out);
}


class osoba{
    string im;
    int wi;
    adres* adr;
  public:
    osoba(): im("brak"), wi(0), adr(new adres) {}
    osoba(const string& a1, const int a2, const adres& a3):im(a1), wi(a2), adr(new adres(a3)){}
    osoba(const osoba& a1):  im(a1.im), wi(a1.wi), adr(new adres(*a1.adr)) {}

    ~osoba(){ delete adr; }

    string& miasto(){
      return adr->miasto();
    }

    friend ostream& operator<< (ostream& out, const osoba& r);

    osoba& operator=(const osoba& a1){
        if (this == &a1) {
          return *this; // ?????
        }
        im = a1.im;
        wi = a1.wi;
        delete adr;
        adr = new adres(*(a1.adr)); // ??????
        return *this;
    }
};

ostream& operator<< (ostream& out, const osoba& r){
    out << "Imie: " << r.im << ", Wiek: " << r.wi << ", Adres: " << *r.adr;
    return out;
}



int main(){
  #ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
  #endif
  cout << "Adresy: \n";
  adres* wsk = new adres("Częstochowa", "Dąbrowskiego", 73);

  cout <<  wsk << '\n';
  cout << *wsk << '\n';

  adres a1(*wsk);

  delete wsk;
  wsk=nullptr;

  const adres* wsk1 = new adres("Łódź", "Piotrkowska", 33);

  cout << a1 << '\n';
  cout << *wsk1 << '\n';

  adres a2;
  cout << a2 << '\n';

  a2 = a1;
  cout << a2 << '\n';

  cout << "Osoby: \n";
  osoba os1("Ala", 25, *wsk1);
  delete wsk1;

  cout << os1 << '\n';

  osoba os2(os1);

  os2.miasto()="Zmieniono miasto osoby 1.";

  cout << os1 << '\n';
  osoba os3;
  cout << os3 << '\n';

  os3 = os2;

  os1.miasto()="Drugi raz zmieniono miasto osoby 1.";

  cout << os3 << '\n';
  
#ifdef _WIN32
  system("PAUSE");
#endif
return 0;
}
