#include <io_strategy.hpp>

ImageData PngIoStrategy::Read(const std::string &file_name) const{
    std::ifstream in(file_name, std::ios_base::in);
    if (!in) {
      return {0, 0, {}};
    }
    png::image< png::rgb_pixel > image(file_name);
    ImageData output_data;
    output_data.rows = image.get_height();
    output_data.cols = image.get_width();
    output_data.data.reserve(output_data.rows*output_data.cols);
    for(int i =0; i<output_data.rows*output_data.cols;i++){
        output_data.data.push_back(image.get_pixel(i%output_data.cols, i/output_data.cols));
    }
    return output_data;
}

bool PngIoStrategy::Write(const ImageData &image, const std::string &file_name) const{
    png::image< png::rgb_pixel > out_img(image.rows, image.cols);
    for (int r = 0; r < image.rows; ++r) {
        for (int c = 0; c < image.cols; ++c) {
            out_img[r][c] = image.data[r*image.cols+c];
        }
    }
    out_img.write(file_name);
    return true;
}

ImageData PpmIoStrategy::Read(const std::string &file_name) const{
    std::ifstream in(file_name, std::ios_base::in);
    if (!in) {
      return {0, 0, {}};
    }
    return {0, 0, {}};
}

bool PpmIoStrategy::Write(const ImageData &image, const std::string &file_name) const{
    return true;
}