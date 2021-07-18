#include <igg_image/io_tools.hpp>
#include <image.hpp>

int find_interval(std::vector<int> thresholds, int current_low,
                  int current_high, int value) {
  int mid_idx = current_low + (current_high - current_low) / 2;
  if (value - thresholds[mid_idx] >= 0 &&
      value - thresholds[mid_idx] <
          thresholds[mid_idx + 1] - thresholds[mid_idx]) {
    return mid_idx;
  } else if (value - thresholds[mid_idx] < 0) {
    return find_interval(thresholds, current_low, mid_idx - 1, value);
  } else {
    return find_interval(thresholds, mid_idx + 1, current_high, value);
  }
}

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

void igg::Image::UpScale(int scale) {
  int scale_squared = scale * scale;
  std::vector<int> orig_data = data_;
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

std::vector<float> igg::Image::ComputeHistograms(int bins) const {
  std::vector<int> thresholds;
  std::vector<float> histogram;
  float pixel_increment = 1.0f / (rows_ * cols_);
  thresholds.reserve(bins + 1);
  histogram.resize(bins);
  for (int i = 0; i <= bins; i++) {
    thresholds.emplace_back(255 * i / bins);
  }
  for (int i = 0; i < rows_ * cols_; i++) {
    int value_interval = find_interval(thresholds, 0, bins, data_[i]);
    histogram[value_interval] += pixel_increment;
  }
  return histogram;
}

int main() {
  std::cout << "hello" << std::endl;
  igg::Image img{26, 5};
  img.FillFromPgm(
      "/home/pepis/Documents/cpp-course/homework_6/data/lena.ascii.pgm");
  img.UpScale(3);
  // img.DownScale(3)
  img.WriteToPgm("../data/output_lenna.pgm");
  std::vector<float> histogram = img.ComputeHistograms(7);
  for (float val : histogram) {
    std::cout << val << " ";
  }
  std::cout << "\n" << img.rows() << " " << img.cols() << std::endl;
  return 0;
}