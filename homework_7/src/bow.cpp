#include <bow.hpp>

void debug_img(const std::vector<ipb::sift> &sifts,
               const std::vector<ipb::sift> &centroids) {
  cv::Mat image(1000, 1000, CV_8UC3);
  int color_increment = 255 / centroids.size();
  for (const ipb::sift &sift : sifts) {
    cv::circle(image, cv::Point(sift.descriptor[0] * 6, sift.descriptor[1] * 6),
               2,
               cv::Scalar(255 - color_increment * sift.cluster,
                          color_increment * sift.cluster, 0),
               cv::FILLED);
  }
  for (const ipb::sift &centroid : centroids) {
    cv::line(
        image,
        cv::Point(centroid.descriptor[0] * 6 - 5, centroid.descriptor[1] * 6),
        cv::Point(centroid.descriptor[0] * 6 + 5, centroid.descriptor[1] * 6),
        cv::Scalar(255 - color_increment * centroid.cluster,
                   color_increment * centroid.cluster, 0),
        2);
    cv::line(
        image,
        cv::Point(centroid.descriptor[0] * 6, centroid.descriptor[1] * 6 - 5),
        cv::Point(centroid.descriptor[0] * 6, centroid.descriptor[1] * 6 + 5),
        cv::Scalar(255 - color_increment * centroid.cluster,
                   color_increment * centroid.cluster, 0),
        2);
  }
  cv::namedWindow("Debug Image");
  cv::imshow("Debug Image", image);
  cv::waitKey(0);
}

cv::Mat ipb::kMeans(const std::vector<cv::Mat> &descriptors, int k,
                    int max_iter) {

  std::vector<sift> centroids;
  centroids.reserve(k);

  std::vector<sift> sifts;

  // Sift array initialization
  for (const auto &element : descriptors) {
    for (int i = 0; i < element.rows; i++) {
      sift descriptor = sift(element.row(i));
      sifts.emplace_back(descriptor);
    }
  }
  std::cout << "initialized\n";

  // Centroid Random initialization
  for (int16_t i = 0; i < k; i++) {
    std::vector<int> centroid;
    centroid.reserve(sifts[0].descriptor.size());
    for (int j = 0; j < sifts[0].descriptor.size(); j++) {
      centroid.emplace_back((rand() % 255));
    }
    centroids.emplace_back(sift(centroid, i));
    std::cout << i << std::endl;
  }

  std::cout << "centroids\n";

  for (int iter = 0; iter < max_iter; iter++) {

    // calculate closest centroid for each point
    for (sift &descriptor : sifts) {
      for (const sift &centroid : centroids) {
        unsigned long int d = descriptor.distance(centroid);
        if (d < descriptor.distance_to_cluster) {
          descriptor.distance_to_cluster = d;
          descriptor.cluster = centroid.cluster;
        }
      }
    }
    for (sift &descriptor : sifts) {
      std::cout << descriptor.cluster << " ";
    }

    std::cout << "closest centroids\n";

    // Recalculate centroids
    for (const sift &descriptor : sifts) {
      // std::cout << descriptor.cluster << std::endl;
      centroids.at(descriptor.cluster) += descriptor;
      centroids.at(descriptor.cluster).associated_points++;
    }
    for (sift &centroid : centroids) {
      if (centroid.associated_points > 0) {
        centroid = centroid / centroid.associated_points;
      }
      centroid.associated_points = 0;
      centroid.print();
    }
  }

  // visualize result
  debug_img(sifts, centroids);

  // generate output Mat
  cv::Mat ans_mat;
  for (const sift &centroid : centroids) {
    ans_mat.push_back(centroid.descriptor);
  }
  return ans_mat;
}

int main() {
  std::vector<cv::Mat> sifts =
      ipb::serialization::sifts::LoadDataset("../test_dataset");
  for (const auto &element : sifts) {
    std::cout << " ---- " << element.size << " ---- " << std::endl;
  }
  cv::Mat ans = ipb::kMeans(sifts, 10, 10);
  // std::cout << ans << std::endl;
}