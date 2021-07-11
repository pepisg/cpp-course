#include <convert_dataset.hpp>

void ipb::serialization::sifts::ConvertDataset(
    const std::filesystem::path &img_path) {
  auto detector = cv::xfeatures2d::SiftFeatureDetector::create();
  auto extractor = cv::xfeatures2d::SiftDescriptorExtractor::create();
  std::vector<cv::KeyPoint> keypoints;
  cv::Mat descriptors;
  cv::Mat image;

  for (const auto image_path : std::filesystem::directory_iterator(img_path)) {
    if (image_path.path().extension().string() != ".png") {
      std::cout << "skipping invalid file: " + image_path.path().string()
                << std::endl;
      continue;
    }
    image = cv::imread(image_path.path().string());
    detector->detect(image, keypoints);
    extractor->compute(image, keypoints, descriptors);
    std::string output_name = image_path.path().stem().string() + ".bin";
    ipb::serialization::Serialize(
        descriptors, "../../dataset/final_project/bin/" + output_name);
    std::cout << "saving file: " + output_name << std::endl;
  }
}

std::vector<cv::Mat>
ipb::serialization::sifts::LoadDataset(const std::filesystem::path &bin_path) {
  std::vector<cv::Mat> image_vector;
  image_vector.reserve(
      (std::size_t)std::distance(std::filesystem::directory_iterator{bin_path},
                                 std::filesystem::directory_iterator{}));
  for (const auto image_path : std::filesystem::directory_iterator(bin_path)) {
    cv::Mat image = ipb::serialization::Deserialize(image_path.path().string());
    image_vector.push_back(image);
  }
  return image_vector;
}

int main() {
  ipb::serialization::sifts::ConvertDataset(
      "../../dataset/final_project/images-freiburg-x10/data1/");
  auto img_vector = ipb::serialization::sifts::LoadDataset(
      "../../dataset/final_project/bin/");
  cv::namedWindow("serialized");
  for (const auto &image : img_vector) {
    cv::imshow("serialized", image);
    cv::waitKey(0);
  }
  return 0;
}