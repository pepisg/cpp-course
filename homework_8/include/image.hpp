#ifndef IMAGE_HPP_
#define IMAGE_HPP_

#include <iostream>
#include <math.h>
#include <png++/png.hpp>
#include <vector>
#include <memory>
#include <io_strategy.hpp>

namespace igg {

class Image {

public:
  Image();
  Image(int rows, int cols);

public:
  int rows() const;
  int cols() const;

public:
  png::rgb_pixel at(int row, int col) const;
  png::rgb_pixel &at(int row, int col);

public:
  bool FillFromPgm(const std::string &file_name);
  void WriteToPgm(const std::string &file_name);
  void DownScale(int scale);
  void UpScale(int scale);
  void ReadFromDisk(const std::string &file_name);
  void WriteToDisk(const std::string &file_name);
  void SetIoStrategy(std::shared_ptr<IoStrategy> strategy_ptr);


private:
  int rows_ = 0;
  int cols_ = 0;
  std::vector<png::rgb_pixel> data_ = {};
  std::shared_ptr<IoStrategy> io_strategy_ = nullptr;
};

} // namespace igg

#endif