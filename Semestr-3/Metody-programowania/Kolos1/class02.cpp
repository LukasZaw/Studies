#include <iostream>

using namespace std;

class punkt {
private:
  double x_, y_;

public:
  //Konstruktory
  punkt (): x_(0), y_(0) {}
  punkt (const double& a1, const double& a2): x_(a1), y_(a2){}

  //Metody dostepowe
  double& x() { return x_; }
  double& y() { return y_; }
  const double& x() const { return x_; }
  const double& y() const { return y_; }

  //Destruktor
  ~punkt (){ cout << "~punkt() "; }
};


class kwadrat
{
  punkt punkt_;
  double a_;

public:
  kwadrat(): punkt_(0, 0), a_(0) {}
  kwadrat(const punkt& pkt, const double a1): punkt_(pkt), a_(a1) {}
  kwadrat(const double& a1, const double& a2, const double& a3): punkt_(a1, a2), a_(a3) {}

  double& x() { return punkt_.x(); }
  //...
  const double& x() const { return punkt_.x(); }
  //...
  ~kwadrat(){ cout << "~kwadrat() "; }

  double pole() const;

};

double kwadrat::pole() const {
  return a_ * a_;
}



int main(){
  cout << "Punkty: \n";
  punkt p1, p2(1,2);
  const punkt p3(1.1,2.2);
  cout << p1.x() << endl;
  cout << p2.x() << endl;
  cout << p3.x() << endl;

  p1.x()=1;

  cout << p1.x() << endl;


  cout << "Kwadrat: \n";
  kwadrat kw1, kw2(1, 2, 10.5);
  const kwadrat kw3(p2,5);

  kw1.x()=2;
  cout << kw1.x() << '\t' << endl;
  cout << "Pole: " << kw1.pole() << endl;

  cout << kw3.x() << endl;

  cout << "Pole: " << kw3.pole() << endl;


  return 0;
}
