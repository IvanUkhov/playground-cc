#ifndef ALGORITHM_SORT_BUBBLE_H_
#define ALGORITHM_SORT_BUBBLE_H_

#include <utility>

namespace algorithm { namespace sort {

template <typename T>
void Bubble(std::vector<T>& data) {
  auto size = data.size();
  for (int i = 1; i < size; ++i) {
    bool swapped = false;
    for (int j = 0; j < size - i; ++j) {
      if (data[j] > data[j + 1]) {
        std::swap(data[j], data[j + 1]);
        swapped = true;
      }
    }
    if (!swapped) {
      return;
    }
  }
}

} } // namespace algorithm::sort

#endif // ALGORITHM_SORT_BUBBLE_H_
