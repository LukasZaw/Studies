#include <iostream>
#include <string>

class B {
public:
    virtual ~B() {}
    virtual void print() const = 0;
};

class P1 : public B {
private:
    std::string* data;

public:
    P1(const std::string& str) : data(new std::string(str)) {}

    ~P1() {
        delete data;
    }

    void print() const override {
        std::cout << *data << std::endl;
    }
};

class P2 : public B {
private:
    P1* data;

public:
    P2(const std::string& str) : data(new P1(str)) {}

    ~P2() {
        delete data;
    }

    void print() const override {
        data->print();
    }
};

class P3 : public P2 {
private:
    int number;

public:
    P3(const std::string& str, int num) : P2(str), number(num) {}

    void print() const override {
        P2::print();
        std::cout << " " << number << std::endl;
    }
};

int main() {
    const P1* wsk1 = new P1("Ala");
    const P2* wsk2 = new P2("koty");
    const P3* wsk3 = new P3("ma", 2);

    P1 x;
    x = *wsk1;
    delete wsk1;

    P2 y;
    y = *wsk2;
    delete wsk2;

    P3 z;
    z = *wsk3;
    delete wsk3;

    const B* tab1[3];
    tab1[0] = new P1(x);
    tab1[1] = new P2(y);
    tab1[2] = new P3(z);

    for (int i = 0; i < 3; ++i) {
        tab1[i]->print();
    }

    for (int i = 0; i < 3; ++i) {
        delete tab1[i];
    }

    return 0;
}
