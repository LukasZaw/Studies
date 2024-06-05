#include <iostream>
#include <iomanip>
int main() {
 float suma = 0.0;
 for(int i=0; i<100; ++i)
 suma+=0.1f;
 std::cout <<std::fixed<<std::setprecision(20);
 std::cout <<"suma="<<suma<<std::endl;
 return 0;
}
