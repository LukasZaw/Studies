#include <iostream>
#include <iomanip>

int main() {

  float a = 0.5;
  float b = 0.5;
  float c = 0.5;

  float i1 = a* (b+c);
  float i2 = a*b + a*c;

  std::cout<<std::fixed<<std::setprecision(20);
  std::cout<<i1<<std::endl;
  std::cout<<i2<<std::endl;

  return 0;
}
