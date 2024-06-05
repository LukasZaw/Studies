#include <iostream>
#include <vector>

using namespace std;

class robot;
using wsk = robot*;

class robot {
protected:
    static int l_ob;

public:
    robot(){ l_ob++; }
    static int l_obiektow() { return l_ob; }

    virtual void praca() const = 0;
    virtual robot* clone() const = 0;

    virtual ~robot() { cout << "~robot()" << endl;}
};

int robot::l_ob = 0;

class r1 : public robot {
public:
    r1() {}
    r1(const r1& r) {}

    void praca() const override {
        cout << "Robot typu r1" << endl;
    }

    robot* clone() const override {
        return new r1(*this);
    }

    ~r1() { cout << "~r1()" << endl; l_ob--; }
};

class r2 : public robot {
public:
  r2() {}
  r2(const r2& r) {}

  void praca() const override {
    cout << "Robot typu r2" << endl;
  }

  robot* clone() const override {
    return new r2(*this);
  }

  ~r2() { cout << "~r2()" << endl; l_ob--; }
};

class line {
    vector<wsk> ve;

public:
    line() {}
    line(int r) : ve(r) {
        cout << "Wartości wektora ve : ";
        for (size_t i = 0; i < ve.size(); ++i)
            cout << ve[i] << ", ";
        cout << endl;
    }

    line(const wsk* b, const wsk* e) : ve(b, e) {}

    line(const line& arg) : ve(arg.ve.size()) {
        for (size_t i = 0; i < arg.ve.size(); ++i)
            ve[i] = arg.ve[i]->clone();
    }

    line& operator=(const line& a) {
        if (this != &a) {
            for (auto& elem : ve)
                delete elem;

            ve.resize(a.ve.size());

            for (size_t i = 0; i < a.ve.size(); ++i)
                ve[i] = a.ve[i]->clone();
        }
        return *this;
    }

    void dodaj_ostatni(const wsk& arg) {
        ve.push_back(arg);
    }

    void dodaj_ity(int i, const wsk& arg) {
          ve.insert(ve.begin() + i, arg);
    }

    void usun_ity(int i) {
        if (i >= 0 && static_cast<size_t>(i) < ve.size()) {
            delete ve[i];
            ve.erase(ve.begin() + i);
        }
    }

    void usun_ostatni() {
        if (!ve.empty()) {
            delete ve.back();
            ve.pop_back();
        }
    }

    void do_roboty() {
        for (auto& elem : ve) {
            elem->praca();
        }
    }

    ~line() {
        for (auto& elem : ve) {
            delete elem;
        }
        // ve.clear();
        cout << "~line() \n";
      }
};

void liczba_obiektow() {
    cout << "liczba_obiektów = " << robot::l_obiektow() << endl;
}

int main(){
  {
    cout << "Poczatek: ";
    liczba_obiektow();
    { line l1 ;    }
    { line l2(5) ; }
    liczba_obiektow();
    cout << "--==**1**==--" << endl;
    line lp1, lp2;
    liczba_obiektow();
    lp1.dodaj_ostatni(new r1);
    lp1.dodaj_ostatni(new r1);
    lp1.dodaj_ostatni(new r2);
    lp1.dodaj_ostatni(new r2);
    liczba_obiektow();
    lp2=lp1;
    liczba_obiektow();
    {
      line lp3;
      liczba_obiektow();
      lp3.dodaj_ostatni(new r1);
      lp3.dodaj_ostatni(new r2);
      lp3.dodaj_ostatni(new r1);
      lp3.dodaj_ostatni(new r2);
      //liczba_obiektow();
      lp3.usun_ostatni();
      //liczba_obiektow();
      cout << "--==**2**==--" << endl;
      //liczba_obiektow();
      lp3.do_roboty();
      //liczba_obiektow();
      lp1 = lp3;
      cout << "--==**2a**==--" << endl;
      //liczba_obiektow();
    }
    //liczba_obiektow();
    cout << "--==**3**==--" << endl;
    lp1.do_roboty();
    cout << "--==**4**==--" << endl;

   wsk TabAdrRob[] = {new r2, new r2};
   //liczba_obiektow();
   line lp4(TabAdrRob, TabAdrRob+2 );
   lp4.dodaj_ity(1, new r1); //Dodaj na pozycję o indeksie 1 robot (jego adres) typu r1
   //liczba_obiektow();
   lp4.do_roboty();
    cout << "--==**5**==--" << endl;
    //liczba_obiektow();
    lp4 = lp2;
    lp4.do_roboty();
    cout << "--==**6**==--" << endl;
    line lp6(lp1);
    lp6.usun_ity(1);
    //Usuń robot na pozycji o indeksie 1
    lp6.do_roboty();
    cout << "--==**7**==--" << endl;


    //liczba_obiektow();
    // delete[] TabAdrRob;
    /*
    delete TabAdrRob[0];
    delete TabAdrRob[1];
    */
  }
  cout << "Koniec: ";
  liczba_obiektow();

  return 0;
}
