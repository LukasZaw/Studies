#include<iostream>
#include<fstream>
#include<cmath>
#include<string>
#include<cstring>
#ifdef _WIN32
  #include <windows.h>
#endif // _WIN32 and _WIN64 too

using namespace std;
// class uint{
//   unsigned v;
// public:
//   uint():v(0){}
//   uint(const unsigned& a):v(a){}
//   operator unsigned()const { return v; }
//   friend
//   ostream& operator<<(ostream& out, const uint& r){ return out << r.v; }
//   friend
//   istream& operator>>(istream& in,  uint& r){ return in >> r.v; }
// };

//using naturalne = uint;
using naturalne = unsigned; // Typ unsigned tego nie gwarantuje wartosc obiektu = 0.

//---===*****===---
struct blad {
  string txt;
  unsigned lp;
  blad():lp(0){}
  blad(const string& a, unsigned b):txt(a), lp(b){}
};
ostream& operator<<(ostream& out, const blad& p){
  return out << p.txt << ' ' << p.lp << endl;
}
//---===*****===---


class polygon;

class point {
    double x, y;
  public:
    point(): x(0), y(0){}
    point(const double& a, const double& b): x(a), y(b){}
    double distance(const point& a)const;
    friend class polygon;
    friend istream& operator>>(istream&, point&);
    friend ostream& operator<<(ostream&, const point&);
};
double point::distance(const point& a)const {
    double c2 = (a.x-x)*(a.x-x)+(a.y-y)*(a.y-y);
    if(c2<1e-20)
        return 0;
    return sqrt(c2);
}
istream& operator>>(istream& in, point& p){
    return in >> p.x >> p.y;
}
ostream& operator<<(ostream& out, const point& p){
    return out << "(" << p.x << ", "<<p.y << ")";
}
//---===*****===---


class polygon{
  unsigned n;
  point* points;
  naturalne* order;

 public:
  polygon():n(0), points(nullptr), order(nullptr){}
  polygon(const polygon& a);
  polygon& operator=(const polygon& a);
  ~polygon();

  void read(ifstream& );
  void read_check(ifstream& );
  double obwod()const;
  double pole()const;
};

polygon::polygon(const polygon& a): n(a.n), points(a.n != 0 ? new point[a.n] : nullptr), order(a.n != 0 ? new naturalne[a.n] : nullptr) {
  for( unsigned i = 0; i < a.n; i++){
    points[i] = a.points[i];
    order[i] = a.order[i];
  }
}

polygon& polygon::operator=(const polygon& a){
  if(this != &a){
   if(points != nullptr){
     delete[] points;
     points = nullptr;
   }
   if(order != nullptr){
     delete[] order;
     order = nullptr;
   }
   n = a.n;
   points = a.n != 0 ? new point[a.n] : nullptr;
   order = a.n != 0 ? new naturalne[a.n] : nullptr;
   for(unsigned i = 0; i < a.n; i++){
     points[i] = a.points[i];
     order[i] = a.order[i];
   }
  }
  return *this;
}

polygon::~polygon(){
  delete[] points;
  delete[] order;
  cout << "\n\n!!!~polygon()!!!\n\n";
}


void polygon::read(ifstream& f){
  cout << "Wczytywanie danych z pliku... " << endl;
  string buf;

  getline(f, buf);
  cout << buf << endl;

  getline(f, buf);
  cout << buf << endl;

  f >> n ;
  getline(f, buf);

  cout << n << endl;
  if(n<3) throw string("Liczba punktów mniejsza od 3");

  getline(f, buf);
  cout << buf << endl;

  if(points != nullptr){
    delete[] points;
    points = nullptr;
  }
  points = new point[n];

  for(unsigned i = 0; i < n; i++){
    int num;
    f >> num;
    double x, y;
    f >> x >> y;
    points[num - 1] = point(x, y);
    cout << num - 1 << ": " << points[num - 1] << endl;
  }
  getline(f, buf);
  getline(f, buf);
  cout << buf << endl;

  if(order != nullptr){
    delete[] order;
    order = nullptr;
  }
  order = new naturalne[n];
  for(unsigned i = 0; i < n; i++){
    f >> order[i];
    cout << order[i] << " ";
  }
  cout << endl;
  cout << "Koniec wczytywania danych. \n\n";
}

void polygon::read_check(ifstream& f){

  string buf;
  getline(f, buf);
  if(buf != "[POLYGON]"){
    // cout << buf;
    // cout << "Brak naglowka" << endl;
    throw string("Brak naglowka \"[POLYGON]\"");
  }
  cout << buf << endl;

  getline(f, buf);
  // if(buf!="[NUMBER OF NODES]") throw string("Brak nagłówka \"[NUMBER OF NODES]\"");
  cout << buf << endl;

  f >> n ;
  getline(f, buf);

  // if(!f || buf[0]!='\0' ) throw string("Nieprawidłowy format parmetru \"n\"");
  cout << n << endl;

  if(n<3) throw string("Liczba punktów mniejsza od 3");

  getline(f, buf);
  // if(buf!="[NODES]") throw string("Brak nagłówka \"[NODES]\"");
  cout << buf << endl;


  //resztę dopisz sam
  //Wykorzystaj klasę blad do zgłasznia wyjątku.
  //Oprócz komunikatu tekstowego będziesz mógł wskazać np., w którym wierszu lub kolumnie
  //zidentyfikowany został błąd formatu pliku z danymi.
}

double polygon::obwod()const{
  double obw=0;
  if(!order) throw string ("Brak tablicy order.");
  if(!points) throw string ("Brak tablicy points.");
  for(int i=0, j=0; (unsigned)i < n; ++i){
    j = order[i] - 1;
    int nnn = n;
    if(j < 0) throw string ("Niedozwolona wartość 0 w tablicy order.");
    if(j >= nnn) throw string("Niedozwolona wartość w tablicy order.");
    obw += points[j].distance(points[order[(i + 1) % n] - 1]); //???
  }
  return obw;
}

double polygon::pole()const{
  double pole = 0;
  if (!points) throw string("Brak tablicy points.");
  for (unsigned i = 0; i < n; ++i) {
    unsigned j = order[i] - 1;
    unsigned k = order[(i + 1) % n] - 1; //???
    pole += (points[j].x * points[k].y - points[k].x * points[j].y);
  }
  if(pole >= 0) {
    throw blad("Pole jest ujemne, zle dane", 2);
  }
  return 0.5 * abs(pole);
}







int main (int argc, char* argv[])try {
  #ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
  #endif

  if (argc !=2) throw int(0);
  if (strlen(argv[1]) < 5 ) throw 1;
  if (string(argv[1]+(strlen(argv[1])-3))!="txt") throw 2 ;

  ifstream file(argv[1]);
  if(!file) throw 3;
  {
    try{
     polygon poly;

     poly.read(file);
     cout<< "Obwod : " << poly.obwod()<< endl;
     cout<< "Pole  : " << poly.pole()<< endl;
    }
    catch ( const string& e ){ cout << e << endl;}
    catch ( const blad&   e ){ cout << e ;}
    file.close();
  }

  #ifdef _WIN32
    system("PAUSE");
  #endif
  return 0;
}
catch (int err){
  switch (err) {
    case 0: cout << err <<": Zła liczba parametrów programu.\n";
    break;
    case 1: cout << err <<": Zła nazwa pliku z danymi.\n";
    break;
    case 2: cout << err <<": Złe rozszerzenie pliku z danymi - musi być *.txt .\n";
    break;
    case 3: cout << err <<": Brak pliku o nazwie "<< argv[1] << " .\n";
  }
}
catch ( ... ) { cout << "Nieznana sytuacja wyjątkowa.\n"; }
