#include <image.hpp>
#include <opencv2/core/matx.hpp>
#include <opencv2/highgui.hpp>
#include <png++/rgb_pixel.hpp>
#include <vector>

void debug_image(const igg::Image& image){
  cv::Mat debug_img(image.rows(), image.cols(), CV_8UC3);
  int idx = 0;
  for(const png::rgb_pixel& pixel : image.data()){
    debug_img.at<cv::Vec3b>(idx) = cv::Vec3b(pixel.blue, pixel.green, pixel.red);
    idx++;
  }
  cv::namedWindow("test");
  cv::imshow("test", debug_img);
  cv::waitKey(0);
}

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

std::vector<png::rgb_pixel> igg::Image::data() const{
  return data_;
}

void igg::Image::UpScale(int scale) {
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
  int r = 0;
  int c = 0;
  for (int i = 0; i < rows_; i = i + scale) {
    r++;
    for (int j = 0; j < cols_; j = j + scale) {
      data_[++k] = data_[i * cols_ + j];
      c++;
    }
  }
  rows_ = r;
  cols_ = k/r;
  data_.resize(rows_ * cols_);
}

void igg::Image::SetIoStrategy(std::shared_ptr<IoStrategy> strategy_ptr){
  io_strategy_ = strategy_ptr;
}

void igg::Image::ReadFromDisk(const std::string &file_name){
  if(!io_strategy_){
    return;
  }else{
    ImageData image = io_strategy_->Read(file_name);
    rows_ = image.rows;
    cols_ = image.cols;
    data_ = image.data;
  }
}

void igg::Image::WriteToDisk(const std::string &file_name){
  if(!io_strategy_){
    return;
  }else{
    ImageData image {rows_, cols_, data_};
    io_strategy_->Write(image, file_name);
  }
}

int main() {
  std::cout << "hello" << std::endl;
  igg::Image img{26, 5};
  img.SetIoStrategy(std::make_shared<PngIoStrategy>());
  img.ReadFromDisk("../tests/lenna.png");
  img.UpScale(2);
  debug_image(img);
  // img.DownScale(3);
  img.WriteToDisk("../tests/lenna_out.png");
  std::cout << "\n" << img.rows() << " " << img.cols() << std::endl;
  return 0;
}