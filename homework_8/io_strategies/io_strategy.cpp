#include <io_strategy.hpp>
#include <png++/rgb_pixel.hpp>

ImageData PngIoStrategy::Read(const std::string &file_name) const {
  std::ifstream in(file_name, std::ios_base::in);
  if (!in) {
    return {0, 0, {}};
  }
  png::image<png::rgb_pixel> image(file_name);
  ImageData output_data;
  output_data.rows = image.get_height();
  output_data.cols = image.get_width();
  output_data.data.reserve(output_data.rows * output_data.cols);
  for (int i = 0; i < output_data.rows * output_data.cols; i++) {
    output_data.data.push_back(
        image.get_pixel(i % output_data.cols, i / output_data.cols));
  }
  return output_data;
}

bool PngIoStrategy::Write(const ImageData &image,
                          const std::string &file_name) const {
  png::image<png::rgb_pixel> out_img(image.rows, image.cols);
  for (int r = 0; r < image.rows; ++r) {
    for (int c = 0; c < image.cols; ++c) {
      out_img[r][c] = image.data[r * image.cols + c];
    }
  }
  out_img.write(file_name);
  return true;
}

ImageData PpmIoStrategy::Read(const std::string &file_name) const {
  // not working with comments
  std::ifstream in(file_name, std::ios_base::in);
  if (!in) {
    return {0, 0, {}};
  }
  std::string type;
  int rows = 0;
  int cols = 0;
  int max_val = 0;
  std::vector<png::rgb_pixel> data;
  in >> type >> rows >> cols >> max_val;
  data.resize(rows * cols);
  int red, green, blue;
  for (int r = 0; r < rows; ++r) {
    for (int c = 0; c < cols; ++c) {
      in >> red >> green >> blue;
      data[r * cols + c] = png::rgb_pixel(red, green, blue);
    }
  }
  return {rows, cols, data};
}

bool PpmIoStrategy::Write(const ImageData &image,
                          const std::string &file_name) const {
  std::ofstream out(file_name);
  if (!out) {
    return false;
  }
  int line_chars = 0;
  out << "P3" << std::endl
      << image.rows << " " << image.cols << std::endl
      << 255 << std::endl;
  for (int r = 0; r < image.rows; ++r) {
    for (int c = 0; c < image.cols; ++c) {
      out << unsigned(image.data[r * image.cols + c].red) << " "
          << unsigned(image.data[r * image.cols + c].green) << " "
          << unsigned(image.data[r * image.cols + c].blue) << " ";
      line_chars += 9;
      if (line_chars > 70) {
        line_chars = 0;
        out << std::endl;
      }
    }
  }
  return true;
}