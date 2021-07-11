
#include "serialize.hpp"

void ipb::serialization::Serialize(const cv::Mat &m,
                                   const std::string &filename) {
  std::ofstream bin_file(filename, std::ios_base::out | std::ios_base::binary);
  int rows = m.rows;
  int cols = m.cols;
  int channels = m.channels();
  int type = m.type();
  int element_size = int(m.elemSize() / channels);
  uchar *data = m.data;
  bin_file.write(reinterpret_cast<char *>(&rows), sizeof(rows));
  bin_file.write(reinterpret_cast<char *>(&cols), sizeof(cols));
  bin_file.write(reinterpret_cast<char *>(&channels), sizeof(channels));
  bin_file.write(reinterpret_cast<char *>(&type), sizeof(type));
  bin_file.write(reinterpret_cast<char *>(&element_size), sizeof(element_size));
  std::cout << rows << " " << element_size << " " << channels << " " << type
            << std::endl;
  for (size_t i = 0; i < rows * cols * channels * element_size; i++) {
    bin_file.write(reinterpret_cast<char *>(&data[i]), sizeof(data[i]));
  }
  std::cout << "File written successfully\n";
};

cv::Mat ipb::serialization::Deserialize(const std::string &filename) {
  std::ifstream bin_file(filename, std::ios_base::out | std::ios_base::binary);
  int rows;
  int cols;
  int type;
  int channels;
  int element_size;
  bin_file.read(reinterpret_cast<char *>(&rows), sizeof(rows));
  bin_file.read(reinterpret_cast<char *>(&cols), sizeof(cols));
  bin_file.read(reinterpret_cast<char *>(&channels), sizeof(channels));
  bin_file.read(reinterpret_cast<char *>(&type), sizeof(type));
  bin_file.read(reinterpret_cast<char *>(&element_size), sizeof(element_size));
  cv::Mat m(rows, cols, type);
  uchar *data = m.data;
  for (size_t i = 0; i < rows * cols * channels * element_size; i++) {
    bin_file.read(reinterpret_cast<char *>(&data[i]), sizeof(data[i]));
  }
  std::cout << "File read successfully\n";
  return m;
}

int main() {
  auto detector = cv::xfeatures2d::SiftFeatureDetector::create();
  auto extractor = cv::xfeatures2d::SiftDescriptorExtractor::create();
  std::vector<cv::KeyPoint> keypoints;
  cv::Mat image = cv::imread("../data/lenna.png", cv::IMREAD_UNCHANGED);
  cv::Mat img_with_keypoints;
  cv::Mat descriptors;
  detector->detect(image, keypoints);
  extractor->compute(image, keypoints, descriptors);
  cv::drawKeypoints(image, keypoints, img_with_keypoints);
  cv::namedWindow("serialized");
  cv::namedWindow("deserialized");
  ipb::serialization::Serialize(descriptors, "../test.bin");
  cv::Mat deserialized_img = ipb::serialization::Deserialize("../test.bin");
  cv::imshow("serialized", descriptors);
  cv::imshow("deserialized", deserialized_img);
  cv::waitKey(0);
}