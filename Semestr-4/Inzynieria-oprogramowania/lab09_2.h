#include <string>
#include <vector>

using namespace std;

class BazowaG
{
public:
    virtual void op1() = 0;
    virtual void op2() = 0;
    virtual double op3(double a) = 0;
};

class KlasaF : public BazowaG
{
public:
    void op1();
    void op2();
    double op3(double a);

private:
    int x;
    int y;
    string nap;
};

class CzescA
{
public:
    CzescB op1(int a);

private:
    int l1;
    int l2;
    BazowaG *obiektG;
};

class CzescB
{
public:
    void op1();
    bool op2(double a);
    int op3();

private:
    int cs;
};

class KlasaE
{
private:
    string nap;
    vector<CzescA> obiektA;

public:
    CzescA op1(int a, string b) {};
    void op2(double a) {};
};

class KlasaC
{
private:
    int lp;
    string np;
    double wt;

    KlasaD &klasac;

public:
    void op1(bool a);
};

class KlasaD
{
private:
    double sm1;
    string nap1;
    string nap2;

    KlasaE *klasaC;

public:
    void op1(bool a);
};