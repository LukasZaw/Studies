#include <iostream>
#include <iomanip>

int main() {
    double x1 = 1.00E+21;
    double x2 = 17.0;
    double x3 = -10.0;
    double x4 = 130.0;
    double x5 = -1.00E+21;

    double s0 = x1 + x2 + x3 + x4 + x5;
    std::cout<<"s0: "<<s0<<std::endl; 

    // (((x1 + x2) + x3) + x5) + x4;
    double s1 = (((x1 + x2) + x3) + x5) + x4;
    std::cout << "s1: " << s1 << std::endl;

    // (((x1 + x2) + x4) + x3) + x5;
    double s2 = (((x1 + x2) + x4) + x3) + x5;
    std::cout << "s2: " << s2 << std::endl;

    // (((x1 + x2) + x5) + x3) + x4;
    double s3 = (((x1 + x2) + x5) + x3) + x4;
    std::cout << "s3: " << s3 << std::endl;

    // (((x1 + x5) + x3) + x4) + x2;
    double s4 = (((x1 + x5) + x3) + x4) + x2;
    std::cout << "s4: " << s4 << std::endl;

    // (((x1 + x2) + x5) + x3) + x4;
    double s5 = (((x1 + x2) + x5) + x3) + x4;
    std::cout << "s5: " << s5 << std::endl;

    // (((x1 + x3) + x2) + x4) + x5;
    double s6 = (((x1 + x3) + x2) + x4) + x5;
    std::cout << "s6: " << s6 << std::endl;

    return 0;
}
