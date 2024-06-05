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
    P1() : data(nullptr) {}
    P1(const std::string& str) : data(new std::string(str)) {}

    P1(const P1& other) : data(other.data ? new std::string(*other.data) : nullptr) {}

    ~P1() {
        delete data;
    }

    P1& operator=(const P1& other) {
        if (this != &other) {
            delete data;
            if (other.data != nullptr) {
                data = new std::string(*other.data);
            } else {
                data = nullptr;
            }
        }
        return *this;
    }

    void print() const override {
        std::cout << *data << std::endl;
    }
};


class P2 : public B {
private:
    P1* data;

public:

    P2() : data(nullptr) {}
    P2(const std::string& str) : data(new P1(str)) {}

    P2(const P2& other) : data(nullptr) {
        if (other.data != nullptr) {
            data = new P1(*other.data);
        }
    }

    P2& operator=(const P2& other) {
        if (this != &other) {
            delete data;
            if (other.data != nullptr) {
                data = new P1(*other.data);
            } else {
                data = nullptr;
            }
        }
        return *this;
    }

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
  P3() : number(0) {}
  P3(const std::string& str, int num) : P2(str), number(num) {}

    void print() const override {
        P2::print();
        std::cout << number << std::endl;
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

    B* tab1[3];
    tab1[0] = new P1(x);
    tab1[1] = new P3(z);
    tab1[2] = new P2(y);

    for (int i = 0; i < 3; ++i) {
        tab1[i]->print();
    }

    for (int i = 0; i < 3; ++i) {
        delete tab1[i];
    }
    /*
*/
    return 0;
}
