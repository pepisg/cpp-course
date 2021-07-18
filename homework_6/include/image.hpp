#ifndef IMAGE_HPP_
#define IMAGE_HPP_

#include <iostream>
#include <math.h>
#include <vector>

namespace igg {
class Image {

public:
  Image();
  Image(int rows, int cols);

public:
  int rows() const;
  int cols() const;

public:
  int at(int row, int col) const;
  int &at(int row, int col);

public:
  bool FillFromPgm(const std::string &file_name);
  void WriteToPgm(const std::string &file_name);
  void DownScale(int scale);
  void UpScale(int scale);
  std::vector<float> ComputeHistograms(int bins) const;

private:
  int rows_ = 0;
  int cols_ = 0;
  std::vector<int> data_ = {};
};

} // namespace igg

#endif