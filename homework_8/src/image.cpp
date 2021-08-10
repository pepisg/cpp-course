#include <igg_image/io_tools.hpp>
#include <image.hpp>

igg::Image::Image(int rows, int cols) {
  rows_ = rows;
  cols_ = cols;
  data_.reserve(rows * cols);
}

int igg::Image::rows() const { return rows_; }

int igg::Image::cols() const { return cols_; }

png::rgb_pixel &igg::Image::at(int row, int col) {
  return data_[row * cols_ + col];
}

png::rgb_pixel igg::Image::at(int row, int col) const {
  return data_[row * cols_ + col];
}

void igg::Image::UpScale(int scale) {
  int scale_squared = scale * scale;
  std::vector<png::rgb_pixel> orig_data = data_;
  int orig_cols = cols_;
  rows_ = (int)rows_ * scale;
  cols_ = (int)cols_ * scale;
  data_.resize(rows_ * cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      data_[i * cols_ + j] = orig_data[(i / scale) * orig_cols + j / scale];
    }
  }
}

void igg::Image::DownScale(int scale) {
  int k = 0;
  for (int i = 0; i < rows_; i = i + scale) {
    for (int j = 0; j < cols_; j = j + scale) {
      data_[++k] = data_[i * cols_ + j];
    }
  }
  rows_ = (int)rows_ / scale;
  cols_ = (int)cols_ / scale;
  data_.resize(rows_ * cols_);
}

int main() {
  std::cout << "hello" << std::endl;
  igg::Image img{26, 5};
  img.UpScale(3);
  // img.DownScale(3);
  std::cout << "\n" << img.rows() << " " << img.cols() << std::endl;
  return 0;
}