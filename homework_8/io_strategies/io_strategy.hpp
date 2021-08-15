#ifndef IO_STRATEGY_HPP_
#define IO_STRATEGY_HPP_

#include <png++/png.hpp>
#include <vector>

struct ImageData {
  int rows;
  int cols;
  std::vector<png::rgb_pixel> data;
};

struct IoStrategy {
  virtual ImageData Read(const std::string &file_name) const = 0;
  virtual bool Write(const ImageData &image,
                     const std::string &file_name) const = 0;
};

struct PngIoStrategy : public IoStrategy {
  ImageData Read(const std::string &file_name) const override;
  bool Write(const ImageData &image,
             const std::string &file_name) const override;
};

struct PpmIoStrategy : public IoStrategy {
  ImageData Read(const std::string &file_name) const override;
  bool Write(const ImageData &image,
             const std::string &file_name) const override;
};

#endif