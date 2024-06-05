#include <iostream>
#include <list>
#include <vector>
#include <deque>
#include <algorithm>
#include <iterator>

using namespace std;


template<class iter, class predicate>
void sortuj(iter b, iter e, predicate pred) {
    for (auto i = b; i != e; ++i) {
        for (auto j = b; j != std::prev(e); ++j) {
            if (pred(*(next(j)), *j)) {
                iter_swap(j, next(j));
            }
        }
    }
}

class student {
public:
    string name;
    int score;

    student(string n, int s) : name(n), score(s) {}

    friend ostream& operator<<(ostream& os, const student& s) {
        os << s.name << " - " << s.score;
        return os;
    }

    bool operator>(const student& other) const {
        return this->score < other.score;
    }

    bool operator<(const student& other) const {
        return this->score > other.score;
    }
};

struct moj_alg1 {
    bool operator()(const student& a, const student& b) const {
        return a.name.length() < b.name.length();
    }
};


template<typename T, std::size_t N>
constexpr std::size_t RozmiarTablicy(T(&)[N]) noexcept { return N; }



int main(){
  int tab1[] = {9, 4, 3, 0, 2, 5, 1};
  list<int> lis1(tab1, tab1+7);
  vector<int> vec1(tab1, tab1+7);
  ostream_iterator<int> out1(cout, " ");

  cout << "tab1 : ";
  copy(tab1, tab1+7, out1 );

  sortuj(lis1.begin(), lis1.end(), greater<int>());
  cout << "\nlis1 : ";
  copy(lis1.begin(), lis1.end(), out1);

  cout << "\nvec1 : ";
  sortuj(vec1.begin(), vec1.end(), less<int>());
  copy(vec1.begin(), vec1.end(), out1);
  cout << "\n********************\n\n";


  string tab2[] = {"Ola","Ewa", "Iza", "Ala", "Ula" };
  deque<string> deq2(tab2, tab2+RozmiarTablicy(tab2)  );
  ostream_iterator<string> out2(cout, ", ");

  cout << "tab2 : ";
  copy(tab2, tab2+RozmiarTablicy(tab2), out2 );

  sortuj(deq2.begin(), deq2.end(), less<string>());
  cout << "\ndeq2 : ";
  copy(deq2.begin(), deq2.end(), out2);
  cout << "\n*******************************\n\n";


  student tab3[] = {student("Aleksandra", 7),student("Ewa",3),
                    student("Izabela",5), student("Alicja",1), student("Urszula",2) };
  vector<student> vec3(tab3, tab3+RozmiarTablicy(tab3)  );
  ostream_iterator<student> out3(cout, "; ");

  cout << "tab3 : ";
  copy(tab3, tab3+RozmiarTablicy(tab3), out3 );

  cout << "\nvec3 - rosnąco : ";
  sortuj(vec3.begin(), vec3.end(), greater<student>());
  copy(vec3.begin(), vec3.end(), out3);

  cout << "\nvec3 - malejąco : ";
  sortuj(vec3.begin(), vec3.end(), less<student>());
  copy(vec3.begin(), vec3.end(), out3);

  cout << "\nvec3 - po długości imienia :\n       ";
  sortuj(vec3.begin(), vec3.end(), moj_alg1());
  copy(vec3.begin(), vec3.end(), out3);
  cout << "\n***********************************************************\n";
  /*
*/
  return 0;
}
