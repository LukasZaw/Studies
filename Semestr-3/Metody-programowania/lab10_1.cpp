#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <iterator>
#include <random>

constexpr void println(auto const &a) { std::cout << a << std::endl; }

using namespace std;


class losuj {
  int min_val, max_val;

public:
  losuj(int min, int max) : min_val(min), max_val(max) {}

  int operator()() const {
    cout << ".";
    static random_device rd;
    static mt19937 gen(rd());
    uniform_int_distribution<> dis(min_val, max_val);
    return dis(gen);
  }
};

class alg1 {
  int min_val, max_val;

public:
  alg1(int min, int max) : min_val(min), max_val(max) {}

  bool operator()(int val) const {
    return (val < min_val || val > max_val);
  }
};




int main(){
  vector<int> ve1(20), ve2(20);
  list<int> li1, li2;
  ostream_iterator<int> out_it(cout, ", ");
  int min1(30), max1(80), min2(40), max2(65);

  auto view = [&out_it](auto&& ob, string txt){
    println(txt);
    copy(ob.begin(), ob.end(), out_it);
    cout << "\n\n";
  };


  generate_n(ve1.begin(), 20, losuj(min1, max1));
  generate_n(ve2.begin(), 20, losuj(min1, max1));
  cout << "\nWektor ve1 - elementy z przedziału <30, ..., 80):" << endl;
  copy(ve1.begin(), ve1.end(),  out_it );
  cout << endl << endl;

  view(ve2, "Wektor ve2 - elementy z przedziału <30, ..., 80):" );

  sort(ve2.begin(), ve2.end());
  view(ve2, "Wektor ve2 - posortowany:" );

  unique(ve2.begin(), ve2.end());
  view(ve2, "Wektor ve2 - unique():" );

  sort(ve2.begin(), ve2.end());
  vector<int>::iterator newEnd = unique(ve2.begin(), ve2.end());
  ve2.erase(newEnd, ve2.end());
  view(ve2, "Wektor ve2 - usiniete wartosci powtarzajace sie:" );

  remove_copy_if(ve2.begin(), ve2.end(), back_inserter(li1), alg1(min2, max2));
  view(li1, "Lista li1 - elementy należące do przedziału <40, ..., 65>:" );

  remove_copy_if(ve2.begin(), ve2.end(), std::back_inserter(li2),
                  [](int value) { return value < 30 || (value > 40 && value < 65) || value > 80; });
  view(li2, "Lista li2 - elementy należące do przedziałów <30, ..., 40) && (65, ..., 80):" );
  /*
*/
  return 0;
}
