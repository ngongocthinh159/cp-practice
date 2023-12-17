#include <bits/stdc++.h>
using namespace std;

struct Food {
  string name;
  int rating;

  Food(string name, int rating) : name(name), rating(rating) {}

  bool operator== (const Food& b) const {
    return this->name == b.name;
  }
};

template <>
struct std::hash<Food> {
  size_t operator()(const Food& food) const {
    return std::hash<string>()(food.name);
  }
};

int cnt = 100;

int main() {
  unordered_map<Food, int> mp;
  mp[Food("a", 100)] = 1; 
  mp[Food("a", 101)] = 2; 

  for (auto& [food, val] : mp) {
    cout << food.name << " " << food.rating << " " << val << "\n";
  }

  return 0;
}
