#include <iostream>
#include <bitset>
#include <limits>
#include <iomanip>

template<typename T>
void show_32_bits(T tmp) {
 const unsigned int tmpSize =32;
 unsigned long int bits = *(unsigned long int*) (&tmp);
 std::bitset<(tmpSize)> tmpBits(bits);
 std::cout<<tmpBits <<" "<<tmpSize <<" bits "<<" "<<std::fixed<<std::setprecision(20)<<tmp<<std::endl;
}

template<typename T>
void show_64_bits(T tmp) {
    const unsigned int tmpSize = 64;
    unsigned long long int bits = *(unsigned long long int*)(&tmp);
    std::bitset<(tmpSize)> tmpBits(bits);
    std::cout << tmpBits << " " << tmpSize << " bits " << " " << std::fixed << std::setprecision(20) << tmp << std::endl;
}

int main() {


    int a = -91;
    show_32_bits(a);
    int b = 91;
    show_32_bits(b);
    int c = std::numeric_limits<int>::min();
    show_32_bits(c);
    int d = std::numeric_limits<int>::max();
    show_32_bits(d);

    unsigned int e = 91;
    show_32_bits(e);

    float f = 91.0f;
    show_32_bits(f);
    float g = -91.0f;
    show_32_bits(g);
    float h = 0.3f;
    show_32_bits(h);
    float i = 0.1f;
    show_32_bits(i);
    float j = 1234567.1234567f;
    show_32_bits(j);

    float l = std::numeric_limits<float>::min();
    show_32_bits(l);

    float l1 = std::numeric_limits<float>::max();
    show_32_bits(l1);

    double m = 91.0;
    show_64_bits(m);
    double n = -91.0;
    show_64_bits(n);
    double o = 0.3;
    show_64_bits(o);
    double p = 0.1;
    show_64_bits(p);
    double q = 1234567.1234567;
    show_64_bits(q);
    double r = std::numeric_limits<double>::min();
    show_64_bits(r);
    double s = std::numeric_limits<double>::max();
    show_64_bits(s);

    return 0;
}
