#include <iostream>
#include <string>

using namespace std;

class Komunikator{
protected:
  string wiadomosc;

public:
  Komunikator(): wiadomosc("") {}
  Komunikator(const string& w): wiadomosc(w) {}

  virtual ostream& wypisz(ostream&) const = 0;
  virtual ~Komunikator() { cout << "~" << endl; }

  friend ostream& operator<<(std::ostream&, const Komunikator&);

};

ostream& operator<<(ostream& os, const Komunikator& k)
{
    return k.wypisz(os);
}


class K1 : public Komunikator{

public:
  K1(): Komunikator() {}
  K1(const string& w): Komunikator(w) {}

  ostream& wypisz(ostream& os) const override{
    return os << wiadomosc << endl;
  }
};


class K2 : public Komunikator{
  int liczba;

public:
  K2(): Komunikator(), liczba(0) {}
  K2(const string& w, const int& l): Komunikator(w), liczba(l){}

  ostream& wypisz(ostream& os) const override{
    return os << wiadomosc << " " << liczba << endl;
  }


};

int main()
{
  Komunikator* linia[5];

  const K1 koniec("koniec");

  linia[0] = new K1("Temp pow:");
  linia[1] = new K2("Częstochoiwa: ", -5);
  linia[2] = new K1("Opady sniegu cm:");
  linia[3] = new K2("kato: ", 10);
  linia[4] = new K1(koniec);

  for(size_t i = 0; i < 5; ++i){
    cout << *linia[i];
  }

  cout << "*********3" << endl;

  // *(static_cast<K2*>(linia[1])) += 2;
  // *(static_cast<K2*>(linia[3])) += 2;
  //
  // std::cout << Komunikator::zliczaj() << std::endl;

}
