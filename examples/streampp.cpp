#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>

#include "umaumaxcpp/streampp.hpp"

int main(int argc, char* argv[]) {
  {
    std::vector<int> vec{0, 1, 2, 3};
    std::cout << vec << std::endl;
  }
  {
    std::map<std::string, int> m{
        {"one", 1},
        {"two", 2},
    };
    std::cout << m << std::endl;
  }
  {
    std::cout << false << std::endl;
    std::cout << true << std::endl;
  }
  return 0;
}
