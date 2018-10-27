# cpp libraries

## streampp.hpp
* stream pretty print library

```
#include <iostream>
#include <vector>

#include "umaumaxcpp/streampp.hpp"

int main(int argc, char* argv[]) {
  std::vector<int> vec{0, 1, 2, 3};
  std::cout << vec << std::endl;
  return 0;
}
```

FYI: [\(C\+\+\) std::vector に std::cout を拡張 \- 絶滅]( http://chillbrains.hateblo.jp/entry/20170730_vector_cout )
