#include <iostream>

using namespace std;

class punkt
{
    double x_, y_, z_;

  public:
    punkt(): x_(0), y_(0), z_(0) {}
    punkt(const double& a1, const double& a2, const double& a3): x_(a1), y_(a2), z_(a3){}

    double& x() { return x_; }
    double& y() { return y_; }
    double& z() { return z_; }

    const double& x() const { return x_; }
    const double& y() const { return y_; }
    const double& z() const { return z_; }
};


class prostokat
{
    punkt punkt_;
    double a_, b_;

  public:
    prostokat(): punkt_(0, 0, 0), a_(0), b_(0) {}
    prostokat(const punkt& pkt, const double& a1, const double a2): punkt_(pkt), a_(a1), b_(a2) {}
    prostokat(const double& a1, const double a2, const double& a3,  const double& a4,  const double& a5): punkt_(a1, a2, a3), a_(a4), b_(a5) {}

    double& x() { return punkt_.x(); }
    double& y() { return punkt_.y(); }
    double& z() { return punkt_.z(); }
    double& a() { return a_; }
    double& b() { return b_; }

    const double& x() const { return punkt_.x(); }
    const double& y() const { return punkt_.y(); }
    const double& z() const { return punkt_.z(); }
    const double& a() const { return a_; }
    const double& b() const { return b_; }

    double pole() const;
};

double prostokat::pole() const {
  return a_ * b_;
}

class graniastoslup
{
    prostokat prostokat_;
    double h_;
  public:
    graniastoslup(): prostokat_(0, 0, 0, 0, 0), h_(0) {}
    graniastoslup(const prostokat& pro, const double& a1): prostokat_(pro), h_(a1) {}
    graniastoslup(const punkt& pkt, const double& a1, const double& a2, const double& a3): prostokat_(pkt, a1, a2), h_(a3) {}
    graniastoslup(const double& a1, const double& a2, const double& a3, const double& a4, const double& a5, const double& a6): prostokat_(a1, a2, a3, a4, a5), h_(a6) {}

    double& x() { return prostokat_.x(); }
    double& y() { return prostokat_.y(); }
    double& z() { return prostokat_.z(); }
    double& a() { return prostokat_.a(); }
    double& b() { return prostokat_.b(); }
    double& h() { return h_; }

    const double& x() const { return prostokat_.x(); }
    const double& y() const { return prostokat_.y(); }
    const double& z() const { return prostokat_.z(); }
    const double& a() const { return prostokat_.a(); }
    const double& b() const { return prostokat_.b(); }
    const double& h() const { return h_; }

    double objetosc() const{
      return prostokat_.pole() * h_;
    }
};

int main(){
  cout << "Punkty: \n";
  punkt p1, p2(1,2,3);         // ???_01
  const punkt p3(1.1,2.2,3.3);
  cout << p1.x() << endl;
  cout << p2.x() << endl;

  cout << p3.x() << '\t' << p3.y() << '\t' << p3.z() << endl;

  p1.x()=1; p1.y()=10; p1.z()=100;

  cout << p1.x() << '\t' << p1.y() << '\t' << p1.z() << endl;


  cout << "Prostokaty: \n";
  prostokat pr1, pr2(1,2,3,10.5, 20.5);
  const prostokat pr3(p2,5,5);

  pr1.x()=2; pr1.y()=20; pr1.z()=200; pr1.a()= 10; pr1.b()=10;
  cout << pr1.x() << '\t' << pr1.y() << '\t' << pr1.z() << '\t'
       << pr1.a() << '\t' << pr1.b() << '\t' << endl;
  cout << "Pole: " << pr1.pole() << endl;


  cout << pr3.x() << '\t' << pr3.y() << '\t' << pr3.z() << '\t'
       << pr3.a() << '\t' << pr3.b() << '\t' << endl;

  cout << "Pole: " << pr3.pole() << endl;

  cout << "Graniastoslup: \n";
  graniastoslup g1, g2(1,2,3,10.5,20.5,30.5), g3(p2,100,200,300);
  const graniastoslup g4(pr3,5);

  cout << g4.x() << '\t' << g4.y() << '\t' << g4.z() << '\n'
       << g4.a() << '\t' << g4.b() << '\t' << g4.h() << '\n';
  cout << "Objetosc: "<< g4.objetosc() << endl;

  g1.a()=10; g1.b()=10; g1.h()=10;

  cout << g1.x() << '\t' << g1.y() << '\t' << g1.z() << '\n'
       << g1.a() << '\t' << g1.b() << '\t' << g1.h() << '\n'
       << g1.objetosc() << endl;

  return 0;
}
