#ifndef IMAGE_HPP_
#define IMAGE_HPP_

#include <iostream>
#include <vector>

namespace igg {
class Image {

public:
  Image();
  Image(int rows, int cols) : rows_{rows}, cols_{cols} {};

public:
  int rows() const;
  int cols() const;

public:
  bool FillFromPgm(const std::string &file_name);
  void WriteToPgm(const std::string &file_name);
  void DownScale(int scale);
  void UpScale(int scale);
  std::vector<float> ComputeHistograms(int bins);

private:
  int rows_;
  int cols_;
  std::vector<uint8_t> data_;
};

} // namespace igg

#endif