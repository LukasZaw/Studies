#include <iostream>

using namespace std;

class punkt{
  double x_, y_, z_;
    
public:
  punkt(): x_(0), y_(0), z_(0){}

  punkt(const double& a1, const double& a2, const double& a3 ): x_(a1), y_(a2), z_(a3){}
  
  double& x() { return x_; } // ???_02
  double& y() { return y_; }
  double& z() { return z_; }

  const double& x() const { return x_; }
  const double& y() const { return y_; }
  const double& z() const { return z_; }

  void wyswietl(){
      cout << "Punkt(" << x_ << ", " << y_ << ", " << z_  << ")" << endl;
    }
};

class prostokat{
  double x_, y_, z_, a_, b_;

public:
  prostokat(): x_(0), y_(0), z_(0), a_(0), b_(0){}

  prostokat(const double& a1, const double& a2, const double& a3, const double& a4, const double& a5 ): x_(a1), y_(a2), z_(a3), a_(a4), b_(a5){}
  prostokat(const punkt& p, const double& a4, const double& a5): x_(p.x()), y_(p.y()), z_(p.z()), a_(a4), b_(a5){}

  double& x() { return x_; }
  double& y() { return y_; }
  double& z() { return z_; }
  double& a() { return a_; }
  double& b() { return b_; }

  const double& x() const { return x_; } //????
  const double& y() const { return y_; }
  const double& z() const { return z_; }
  const double& a() const { return a_; }
  const double& b() const { return b_; }

  double pole(){   
    return a_ * b_;
  }

  double pole() const{      //?????????????
    return a_ * b_;
  }
};

class graniastoslup
{
  double x_, y_, z_, a_, b_, h_;

public:
  graniastoslup(): x_(0), y_(0), z_(0), a_(0), b_(0), h_(0){}

  graniastoslup(const double& a1, const double& a2, const double& a3, const double& a4, const double& a5, const double& a6 ): x_(a1), y_(a2), z_(a3), a_(a4), b_(a5), h_(a6){}
  graniastoslup(const punkt& p, const double& a4, const double& a5, const double& a6 ): x_(p.x()), y_(p.y()), z_(p.z()), a_(a4), b_(a5), h_(a6){}
  graniastoslup(const prostokat& pr, const double& a6 ): x_(pr.x()), y_(pr.y()), z_(pr.z()), a_(pr.a()), b_(pr.b()), h_(a6){}

  double& x() { return x_; }
  double& y() { return y_; }
  double& z() { return z_; }
  double& a() { return a_; }
  double& b() { return b_; }
  double& h() { return h_; }

  const double& x() const { return x_; }
  const double& y() const { return y_; }
  const double& z() const { return z_; }
  const double& a() const { return a_; }
  const double& b() const { return b_; }
  const double& h() const { return h_; }

  double objetosc(){
    return a_ * b_ * h_;
  }

  double objetosc() const{
    return a_ * b_ * h_;
  }
};


int main(){

  punkt p1, p2(1,2,3);         
  const punkt p3(1.1,2.2,3.3);
  cout << "Punkty: " << endl;
  cout << p1.x() << endl;
  cout << p2.x() << endl;

  cout << p3.x() << endl;
  cout << p3.x() << '\t' << p3.y() << '\t' << p3.z() << endl;

  p1.x()=1; p1.y()=10; p1.z()=100;
  cout << p1.x() << '\t' << p1.y() << '\t' << p1.z() << endl;

  prostokat pr1, pr2(1,2,3,10.5, 20.5);
  const prostokat pr3(p2,5,5);

  pr1.x()=2; pr1.y()=20; pr1.z()=200; pr1.a()= 10; pr1.b()=10;

  cout << pr1.x() << '\t' << pr1.y() << '\t' << pr1.z() << '\t'
      << pr1.a() << '\t' << pr1.b() << '\t' << endl;
  cout << pr1.pole() << endl;

  cout << pr3.x() << '\t' << pr3.y() << '\t' << pr3.z() << '\t'
      << pr3.a() << '\t' << pr3.b() << '\t' << endl;
  cout << pr3.pole() << endl;  


  graniastoslup g1, g2(1,2,3,10.5,20.5,30.5), g3(p2,100,200,300);
  const graniastoslup g4(pr3,5);  

  cout << g4.x() << '\t' << g4.y() << '\t' << g4.z() << '\n'
    << g4.a() << '\t' << g4.b() << '\t' << g4.h() << '\n'
    << g4.objetosc() << endl;


  g1.a()=10; g1.b()=10; g1.h()=10;
 
  cout << g1.x() << '\t' << g1.y() << '\t' << g1.z() << '\n'
    << g1.a() << '\t' << g1.b() << '\t' << g1.h() << '\n'
    << g1.objetosc() << endl;


  return 0;
}





// #include <iostream>
// #ifdef _WIN32
//   #include <windows.h>
// #endif // _WIN32 and _WIN64 too

// using namespace std;

// class Adres{
//     string miasto, ulica;
//     int nr_bud;

//     public:
//         Adres(): miasto(""), ulica(""), nr_bud(0){}
//         Adres(const string& a1, const string& a2, const int& a3 ): miasto(a1), ulica(a2), nr_bud(a3){}
//         string& getMiasto() { return miasto; }
//         ostream& view(ostream& out)const{
//             return out << miasto << ", " << ulica << ", " << nr_bud << '\n';
//         }

//         friend  //????
//         ostream& operator<< (ostream& out, const Adres& r);
// };
// ostream& operator<< (ostream& out, const Adres& r){ //????
//     return r.view(out);
// }

// class Osoba{
//     string imie;
//     int wiek;
//     Adres* adres;

//     public:
//         Osoba(): imie(""), wiek(0), adres(nullptr){}               
//         Osoba(const string& a1, int a2, const Adres& a3) : imie(a1), wiek(a2), adres(new Adres(a3)) {} //????
//         Osoba(const Osoba& o) : imie(o.imie), wiek(o.wiek), adres(new Adres(*(o.adres))) {} //????

//         Osoba& operator=(const Osoba& o) {
//             if (this == &o) {
//                 return *this; // ?????
//             }
//             imie = o.imie;
//             wiek = o.wiek;
//             delete adres; 
//             adres = new Adres(*(o.adres)); // ??????
//             return *this;
//         }

//         ~Osoba() {
//             delete adres;
//         }

//         string& miasto(){
//             return adres->getMiasto(); // ?????
//         }

//         friend 
//         ostream& operator<< (ostream& out, const Osoba& o);
// };
// ostream& operator<< (ostream& out, const Osoba& o){
//   out << "Imię: " << o.imie << ", Wiek: " << o.wiek << ", Adres: " << *o.adres;
//   return out ;  
// }

// int main(){
// #ifdef _WIN32
//     SetConsoleOutputCP(CP_UTF8); 
// #endif

//     Adres* wsk = new Adres("Częstochowa", "Dąbrowskiego", 73);
//     cout << *wsk << '\n';

//     Adres a1(*wsk);
//     delete wsk;
//     wsk = nullptr;

//     const Adres* wsk1 = new Adres("Łódź", "Piotrkowska", 33);

//     cout << a1 << '\n';
//     cout << *wsk1 << '\n';

//     Adres a2;
//     cout << a2 << '\n';
//     a2 = a1;
//     cout << a2 << '\n';

//     Osoba os1("Ala", 25, *wsk1);
//     delete wsk1;

//     cout << os1 << '\n';

//     Osoba os2(os1);

//     os1.miasto() = "Zmieniono miasto osoby 1.";
//     cout << os1 << '\n';

//     Osoba os3;
//     cout << os3 << '\n';
//     os3 = os2;

//     os1.miasto() = "Drugi raz zmieniono miasto osoby 1.";
//     cout << os1 << '\n';

//     cout << os3 << '\n';

// #ifdef _WIN32
//     system("PAUSE");
// #endif
//     return 0;
// }