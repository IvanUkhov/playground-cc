#ifndef PROBLEM_MATRIX_ROTATION_H_
#define PROBLEM_MATRIX_ROTATION_H_

#include <cstddef>
#include <vector>

namespace problem {

// Given an image represented by an NxN matrix, where each pixel in the image is
// 4 bytes, write a method to rotate the image by 90 degrees. Can you do this in
// place?
template <typename T>
void MatrixRotation(std::vector<T>& data, std::size_t size) {
  for (std::size_t i1 = 0; i1 < size; ++i1) {
    for (std::size_t j1 = i1; j1 < size - i1 - 1; ++j1) {
      int i2 = j1, j2 = size - i1 - 1;
      int i3 = j2, j3 = size - i2 - 1;
      int i4 = j3, j4 = size - i3 - 1;
      T value = data[i1 * size + j1];
      data[i1 * size + j1] = data[i4 * size + j4];
      data[i4 * size + j4] = data[i3 * size + j3];
      data[i3 * size + j3] = data[i2 * size + j2];
      data[i2 * size + j2] = value;
    }
  }
}

} // namespace problem

#endif // PROBLEM_MATRIX_ROTATION_H_
