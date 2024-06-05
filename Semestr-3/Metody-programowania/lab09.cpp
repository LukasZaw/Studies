#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

template <typename T>
class vec {
private:
    size_t length;
    T* array;

public:
    vec() : length(0), array(nullptr) {}

    vec(size_t len) : length(len), array(len ? new T[len] {T()}: nullptr) {
  }

    vec(const vec& other) : length(other.length) {
        array = new T[length];
        copy(other.array, other.array + length, array);
      }

    // Konstruktor z zakresu
    template <typename InputIt>
    vec(InputIt begin, InputIt end) : length(distance(begin, end)) {
        array = new T[length];
        copy(begin, end, array);
    }

    ~vec() {
        delete[] array;
    }

    size_t size() const {
        return length;
    }

    T& operator[](size_t index) {
        return array[index];
    }

    const T& operator[](size_t index) const {
        return array[index];
    }


    template<class A>
    friend
    ostream& operator<<(ostream&, const vec<A>& );

    template<class A>
    friend
    ostream& operator>>(istream&, vec<A>&);





    vec& operator=(const vec& other) {
        if (this != &other) {
            delete[] array;
            length = other.length;
            array = new T[length];
            copy(other.array, other.array + length, array);
        }
        return *this;
    }
};

template<class A>
ostream& operator<<(ostream& os, const vec<A>& v) {
    for (size_t i = 0; i < v.length; ++i) {
        os << v[i] << " ";
    }
    os << endl;
    return os;
}

template<class A>
istream& operator>>(istream& is, vec<A>& v) {
    for (size_t i = 0; i < v.length; ++i) {
        is >> v[i];
    }
    return is;
}


// Szablon klasy para
template <typename T1, typename T2>
class para {
    T1 first;
    T2 second;

public:
    // para() {}
    para(): first(T1()), second(T2()) {}
    para(const T1& f, const T2& s) : first(f), second(s) {}


  template<class A, class B>
    friend ostream& operator<<(ostream&, const para<A, B>& );
  template<class A, class B>
    friend istream& operator>>(istream&, para<A, B>&);

};

template<class A, class B>
ostream& operator<<(ostream& os, const para<A, B>& p){
    os << "(" << p.first << ", " << p.second << ")";
    return os;
}

template<class A, class B>
istream& operator>>(istream& is, para<A, B>& p){
    is >> p.first >> p.second;
    return is;
}

int main() {
  // para<int, double> ob1;
  // para<double, int> ob2(3.14, 7);
  // para<string, double> ob3("pi", 3.14);
  // para<string, string> ob4("Ala", "kota");
  // cout << ob1 << ob2 << ob3 << ob4;


    vec<int> t1(4);
    for (size_t i = 0; i < t1.size(); ++i) {
        cout << t1[i] << " ";
        t1[i] = i;
    }
    cout << endl << t1;

    string s[] = {"Ala", "ma", "kota"};
    const vec<string> s1(s, s + 3);
    cout << s1;

    vec<int> t2(t1);
    cout << t2;

    vec<string> s2;
    s2 = s1;
    cout << s2;

    vec<para<string, int>> vp1;
    ifstream plik("data2.csv");

    // ...

    /*
    plik >> vp1;
    cout << vp1;
    */
    return 0;
}
