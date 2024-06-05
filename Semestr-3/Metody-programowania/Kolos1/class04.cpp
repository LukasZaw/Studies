#include <iostream>
#include <string>
#include<fstream>

using namespace std;

class produkt {

  string nazwa;
  double cena;

public:
  //Konstruktory
  produkt (): nazwa(""), cena(0) {}
  produkt (const string& a1, const double& a2): nazwa(a1), cena(a2){}
  produkt (const produkt& p): nazwa(p.nazwa), cena(p.cena) {}

  string& getNazwa(){ return nazwa; }
  double& getCena(){ return cena; }

  ostream& view(ostream& out) const{
    return out << nazwa << " - "  << cena << " zl";
  }

  friend ostream& operator<< (ostream& out, const produkt& r);

  //Destruktor
  ~produkt (){ /*cout << "~produkt() ";*/ }
};

ostream& operator<<(ostream& out, const produkt& r){
  return r.view(out);
}

class opis {
  produkt* prod;

public:
  opis(): prod(new produkt) {}
  opis(const string& a1, const double& a2): prod(new produkt(a1, a2)) {}
  opis(const produkt* p): prod(new produkt(*p)){}
  opis(const opis& a1): prod(new produkt(*a1.prod)) {}


  ~opis() { delete prod; }


  opis& operator= (const opis& o){
    if (this == &o) {
      return *this;
    }
    delete prod;
    prod = new produkt(*o.prod);
    return *this;
  }

  opis operator- (double n){
    double t = prod->getCena() - n;
    return opis(prod->getNazwa(), t);
  }

  opis& operator+ (const double& n){
    prod->getCena() += n;
    return *this;
  }

  void read(ifstream&);
  friend opis operator-(double n, const opis& o);
  friend opis& operator+(opis& o, const string& x);
  friend ostream& operator<< (ostream& out, const opis& o);
  friend istream& operator>> (istream& in, opis& o);
};
  opis& operator+(opis& o, const string& x){
    return opis(o.prod->getNazwa() + x, o.prod->getCena());
  }

  opis operator-(double n, const opis& o){
    // return o - n;
    double t = o.prod->getCena() - n;
    return opis(o.prod->getNazwa(), t);
  }
  ostream& operator<< (ostream& out, const opis& o){
    return out << *o.prod << endl;
  }
  istream& operator>> (istream& in, opis& o){
    return in >> o.prod->getNazwa() >> o.prod->getCena();
  }

void opis::read(ifstream& f){
  cout << "Wczytywanie... \n";
  // string a;
  // double b;
  // f >> a >> b;
  // tab[0] =
}

int main (int argc, char* argv[]){
  cout << "Produkty: \n";
  opis ob1, ob2;
  produkt* wsk1 = new produkt("kawa", 4.5);
  opis ob3(wsk1);
  cout << ob1 << ob2 << ob3;

  cout << ob3 - 1.5;

  cout << ob3 + 10;
  cout << 0.5 - ob3;

  cout << ob3;

  // opis ob4;
  // cin >> ob4;
  // cout << ob4;

  ifstream file(argv[1]);
  if(!file){
    cerr << "Blad wczytania z pliku \n";
    return 1;
  }

  opis tab[3];
  // tab[0].read(file);
  for(size_t i = 0; i < 3; i++){
    string a;
    double b;
    file >> a;
    file >> b;
    tab[i] = opis(a, b);
    cout << tab[i];
  }


  delete wsk1;
  wsk1=nullptr;
  file.close();
  // cout << ob3 + 10;
  ob2 = ob3;
  opis* wsk2 = new opis(ob2);
  opis ob6("coscoscos", 2);
  cout << ob2 << *wsk2 << ob6 << '\n';

  cout << ob6 + "dupa ssad" ;
  cout << ob6;
  // produkt a1(*wsk);
  // delete wsk;
  // wsk=nullptr;
  //
  // const produkt* wsk1 = new produkt("Chleb", 5.00);
  // cout << *wsk1 << '\n';
  //
  // produkt a2;
  // cout << a2 << '\n';
  // a2 = a1;
  // cout << a2 << '\n';
  //
  //
  // cout << "Opisy: \n";
  // opis o1("Pieczywo", 25, *wsk1);
  // delete wsk1;
  // cout << o1 << '\n';
  //

  // opis o2(o1);
  //
  // o2.nazwa()="Chleb pelnozianisty";
  //
  // cout << o1 << '\n';
  // opis o3;
  // cout << o3 << '\n';
  //
  // o3 = o2;
  //
  // o1.nazwa()="KOKA KOLA";
  //
  // cout << o3 << '\n';

  return 0;
}
