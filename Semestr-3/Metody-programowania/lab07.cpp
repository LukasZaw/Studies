#include <iostream>
#include <string>

using namespace std;

class pomiar{
 protected:
  string opis;
  size_t roz;
  double* tab;

 public:
  pomiar(): opis(""), roz(0), tab(nullptr){}
  pomiar(const string& a):opis(a), roz(0),tab(nullptr){}
  pomiar(const string& a, const double* p, const double* k): opis(a), roz(k - p > 0 ? k - p : 0), tab(roz ? new double[roz] : nullptr){
    for (size_t i = 0; i < roz; ++i) {
        tab[i] = p[i];
        }
      }
  pomiar(const pomiar& a): opis(a.opis), roz(a.roz), tab(roz ? new double[roz] : nullptr) {
      for (size_t i = 0; i < roz; ++i) {
          tab[i] = a.tab[i];
      }
  }

  pomiar& operator=(const pomiar& a);
  pomiar& operator+=(const string& r);
  pomiar& operator+=(const double& r);
  pomiar& operator*=(const double& r);
  virtual double oblicz_wynik() const = 0;
  virtual ostream& pokaz_opis(ostream&) const = 0;
  virtual ~pomiar();

  friend ostream& operator<< (ostream& a, const pomiar& r);
  friend pomiar& operator+(const string& la, pomiar& pa);

};

ostream& operator<< (ostream& a, const pomiar& r) {
    return r.pokaz_opis(a);
}


pomiar& operator+(const string& la, pomiar& pa){
  pa.opis = la + pa.opis;
  return pa;
}

pomiar& pomiar::operator=(const pomiar& a){
    if (this != &a) {
        opis = a.opis;
        roz = a.roz;
        delete[] tab;
        tab = roz ? new double[roz] : nullptr;
        for (size_t i = 0; i < roz; ++i) {
            tab[i] = a.tab[i];
        }
    }
    return *this;
}

pomiar& pomiar::operator+=(const string& r){
  opis = opis + ' ' + r;
  return *this;
}

pomiar& pomiar::operator+=(const double& r){
  for (size_t i = 0; i < roz; ++i) {
      tab[i] += r;
  }
  return *this;
}

pomiar& pomiar::operator*=(const double& r){
  for (size_t i = 0; i < roz; ++i) {
      tab[i] *= r;
  }
  return *this;
}

pomiar::~pomiar() {
    delete[] tab;
}

class ciezar : public pomiar
{

public:
    ciezar(): pomiar(){}
    ciezar(const string& o,double * b = nullptr, double * e = nullptr): pomiar(o,b,e){}

    ostream& pokaz_opis(ostream& os) const override {
        return os << "Ciężar - \"" << opis << "\"";
    }

    double oblicz_wynik() const override {
        double suma = 0.0;
        for (size_t i = 0; i < roz; ++i) {
            suma += tab[i];
        }
        return suma;
    }
};
class temp : public pomiar
{

public:
    temp():pomiar(){}
    temp(const string& o,double * b = nullptr, double * e = nullptr): pomiar(o,b,e){}

    ostream& pokaz_opis(ostream& os) const override {
        return os << "Temperatura - \"" << opis << "\"";
    }

    double oblicz_wynik() const override {
        double suma = 0.0;
        for (size_t i = 0; i < roz; ++i) {
            suma += tab[i];
        }
        return suma / roz;
    }
};

void pokaz_wszystko(ostream& os, const pomiar& p) {
    os << p << ", WYNIK : " << p.oblicz_wynik() << endl;
}

int main(){
  double dane[] = { 0.0, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8 };
  // pomyśl jakiego typu ma być zmienna tab

  pomiar* tab[5];

  tab[0] = new ciezar("cytryny");
  tab[1] = new temp("poranki", dane+3, dane+6);
  tab[2] = new ciezar("jabłka", dane+1, dane+3);
  tab[3] = new temp("wieczory", dane+1, dane+9);
  tab[4] = new ciezar;
  cout << "********** 1 **********" << endl;
  for (int i=0; i<5; ++i)
    cout << *tab[i] << endl ;  // Tu powinieneś zobaczyć polimorficzne dziłanie funkcji pokaz_opis(...)


  cout << "\n********** 2 **********" << endl;

  for (int i = 0; i < 5; ++i){
    cout << *tab[i] << ", WYNIK : " << tab[i]->oblicz_wynik() << endl;
  }

  cout << "\n********** 2a *********" << endl;
  // Tu modyfikujesz obiekty na różne sposoby
  // Zastanów się, jak wywoływane są kolejne operatory

  *tab[0] =  ciezar("cytryny", dane, dane+1);
  *tab[0] =  ("[kg] " + *tab[0]) += "po wyprzedaży";  //Zastanów się jaki jest typ i co jest wartością wyrażenia ("[kg] " + *tab[0])
  *tab[1] =  "Wiosenne " + *tab[1];
  *tab[2] += "ANTONÓWKI suszone";
  *tab[2] *= 0.1;
  *tab[3] += "po korekcie odczytu";
  *tab[3] += 0.1;

  for (int i = 0; i < 5; ++i)
      cout << *tab[i] << ", WYNIK : " << tab[i]->oblicz_wynik() << endl;

  for (int i = 0; i < 5; ++i)
      delete tab[i];



  cout << "\n********** 3 **********" << endl;
  const ciezar test1("gruszki", dane, dane+9);
  const temp test2;

  // Napisz funkcję pokaz_wszystko(...).
  // Funkcja ta powinna umożliwiać dynamiczne (późne) wiązanie funkcji wirtualnych.
  // ???_01 Poeksperymentuj ze sposobem przekazywania argumentów tej funkcji
  pokaz_wszystko(cout, test1);
  pokaz_wszystko(cout, test2);
  pokaz_wszystko(cout, ciezar());
  pokaz_wszystko(cout, temp("Jakaś tam", dane+8, dane+9));

  /*
*/
  return 0;
}
