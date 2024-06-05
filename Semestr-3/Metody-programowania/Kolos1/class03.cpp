#include <iostream>
#include <string>

using namespace std;

class produkt {

  string nazwa;
  double cena;

public:
  //Konstruktory
  produkt (): nazwa(""), cena(0) {}
  produkt (const string& a1, const double& a2): nazwa(a1), cena(a2){}


  ostream& view(ostream& out) const{
    return out << nazwa << " - "  << cena << " zl";
  }

  string& getNazwa(){
    return nazwa;
  }

  friend ostream& operator<< (ostream& out, const produkt& r);

  //Destruktor
  ~produkt (){ /*cout << "~produkt() ";*/ }
};

ostream& operator<<(ostream& out, const produkt& r){
  return r.view(out);
}

class opis {
  string kategoria;
  int ilosc;
  produkt* prod;

public:
  opis(): kategoria("brak"), ilosc(0), prod(new produkt) {}
  opis(const string& a1, const int& a2, const produkt& a3): kategoria(a1), ilosc(a2), prod(new produkt(a3)) {}
  opis(const opis& a1): kategoria(a1.kategoria), ilosc(a1.ilosc), prod(new produkt(*a1.prod)) {}


  ~opis() { delete prod; }

  string& nazwa(){
    return prod->getNazwa();
  }


  opis& operator= (const opis& o){
    if (this == &o) {
      return *this;
    }
    kategoria = o.kategoria;
    ilosc = o.ilosc;
    delete prod;
    prod = new produkt(*o.prod);
    return *this;
  }

  friend ostream& operator<< (ostream& out, opis& o);
};

  ostream& operator<< (ostream& out, opis& o){
      return out << *o.prod << " | Kategoria: " << o.kategoria << " ,Ilosc: " << o.ilosc << endl;
  }


int main(){
  cout << "Produkty: \n";
  produkt* wsk = new produkt("Cola", 8.50);
  cout << *wsk << '\n';

  produkt a1(*wsk);
  delete wsk;
  wsk=nullptr;

  const produkt* wsk1 = new produkt("Chleb", 5.00);
  cout << *wsk1 << '\n';

  produkt a2;
  cout << a2 << '\n';
  a2 = a1;
  cout << a2 << '\n';


  cout << "Opisy: \n";
  opis o1("Pieczywo", 25, *wsk1);
  delete wsk1;
  cout << o1 << '\n';

  opis o2(o1);

  o2.nazwa()="Chleb pelnozianisty";

  cout << o1 << '\n';
  opis o3;
  cout << o3 << '\n';

  o3 = o2;

  o1.nazwa()="KOKA KOLA";

  cout << o3 << '\n';

  return 0;
}
