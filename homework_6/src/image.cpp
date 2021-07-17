#include <igg_image/io_tools.hpp>
#include <image.hpp>

igg::Image::Image(int rows, int cols) {
  rows_ = rows;
  cols_ = cols;
  data_.reserve(rows * cols);
}

int igg::Image::rows() const { return rows_; }

int igg::Image::cols() const { return cols_; }

int &igg::Image::at(int row, int col) { return data_[row * cols_ + col]; }

int igg::Image::at(int row, int col) const { return data_[row * cols_ + col]; }

bool igg::Image::FillFromPgm(const std::string &file_name) {
  igg::io_tools::ImageData converted_image =
      igg::io_tools::ReadFromPgm(file_name);
  data_.resize(converted_image.rows * converted_image.cols);
  rows_ = converted_image.rows;
  cols_ = converted_image.cols;
  for (int i = 0; i < converted_image.rows; i++) {
    for (int j = 0; j < converted_image.cols; j++) {
      data_[i * cols_ + j] = converted_image.data[i * cols_ + j];
    }
  }
  return true;
}

void igg::Image::WriteToPgm(const std::string &file_name) {
  igg::io_tools::ImageData converted_image;
  converted_image.rows = rows_;
  converted_image.cols = cols_;
  converted_image.data.resize(rows_ * cols_);
  converted_image.max_val = 255;
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++)
      converted_image.data[i * cols_ + j] = unsigned(data_[i * cols_ + j]);
  }
  igg::io_tools::WriteToPgm(converted_image, file_name);
}

int main() {
  std::cout << "hello" << std::endl;
  igg::Image img{26, 5};
  img.FillFromPgm(

      "/home/pepis/Documents/cpp-course/homework_6/data/lena.ascii.pgm");
  img.WriteToPgm("../data/output_lenna.pgm");
  std::cout << img.rows() << " " << img.cols() << std::endl;
  return 0;
}