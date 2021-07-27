#include <bow.hpp>

cv::Mat ipb::kMeans(const std::vector<cv::Mat> &descriptors, int k,
                    int max_iter) {

  std::vector<std::vector<float>> centroids;
  centroids.reserve(k);

  std::vector<Sift> sifts;

  // Sift array initialization
  for (const auto &element : descriptors) {
    for (int i = 0; i < element.rows; i++) {
      Sift sift = Sift(element.row(i));
      sifts.emplace_back(sift);
    }
  }

  // Centroid Random initialization
  for (int i = 0; i < k; i++) {
    std::vector<float> centroid;
    centroid.reserve(128);
    for (int j = 0; j < 128; j++) {
      centroid.emplace_back((float)(rand() % 255));
    }
    centroids.emplace_back(centroid);
  }

  for (int iter = 0; iter < max_iter; iter++) {
    for (const cv::Mat &sifts : descriptors) {
    }
  }
  cv::Mat ans_mat;
  return ans_mat;
}

int main() {
  std::vector<cv::Mat> sifts =
      ipb::serialization::sifts::LoadDataset("../test_dataset");
  for (const auto &element : sifts) {
    std::cout << " ---- " << element.size << " ---- " << std::endl;
  }
  cv::Mat ans = ipb::kMeans(sifts, 50, 10);
  std::cout << ans << std::endl;
}