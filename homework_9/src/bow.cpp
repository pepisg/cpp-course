#include <bow.hpp>

void ipb::BowDictionary::build(int iterations, int size,
                               const std::vector<cv::Mat> &descriptors) {
  std::cout << "Recomputing dictionary...\n";
  m_dictionary = ipb::kMeans(descriptors, size, iterations);
  std::cout << "Dictionary recomputed successfully...\n";
}

void ipb::BowDictionary::set_vocabulary(const std::string &filename) {
  m_dictionary = ipb::serialization::Deserialize(filename);
}

void ipb::BowDictionary::save_vocabulary(const std::string &filename) {
  ipb::serialization::Serialize(m_dictionary, filename);
}

void debug_img(const cv::Mat &sifts, const cv::Mat &centroids,
               const std::vector<std::vector<cv::DMatch>> &matches) {
  cv::Mat image(1000, 1600, CV_8UC3);
  int color_increment = 255 / centroids.rows;
  for (int i = 0; i < sifts.rows; i++) {
    cv::circle(image,
               cv::Point(sifts.at<float>(i, 0) * 5, sifts.at<float>(i, 1) * 5),
               2,
               cv::Scalar(255 - color_increment * matches[i][0].trainIdx,
                          color_increment * matches[i][0].trainIdx, 0),
               cv::FILLED);
  }
  for (int i = 0; i < centroids.rows; i++) {
    cv::line(image,
             cv::Point(centroids.at<float>(i, 0) * 5 - 5,
                       centroids.at<float>(i, 1) * 5),
             cv::Point(centroids.at<float>(i, 0) * 5 + 5,
                       centroids.at<float>(i, 1) * 5),
             cv::Scalar(255 - color_increment * i, color_increment * i), 2);
    cv::line(image,
             cv::Point(centroids.at<float>(i, 0) * 5,
                       centroids.at<float>(i, 1) * 5 - 5),
             cv::Point(centroids.at<float>(i, 0) * 5,
                       centroids.at<float>(i, 1) * 5 + 5),
             cv::Scalar(255 - color_increment * i, color_increment * i), 2);
  }
  cv::namedWindow("Debug Image");
  cv::imshow("Debug Image", image);
  cv::waitKey(100);
  image = cv::Mat::zeros(image.size(), image.type());
}

cv::Mat ipb::kMeans(const std::vector<cv::Mat> &descriptors, int k,
                    int max_iter) {

  cv::Mat centroids;
  centroids.reserve(k);
  std::vector<int> occurences = std::vector<int>(k);

  cv::Mat sifts;

  cv::Ptr<cv::DescriptorMatcher> matcher =
      cv::DescriptorMatcher::create(cv::DescriptorMatcher::FLANNBASED);
  std::vector<std::vector<cv::DMatch>> knn_matches;

  // Sift array initialization
  for (const auto &element : descriptors) {
    // sifts.push_back(element.colRange(cv::Range(0, 2)));
    sifts.push_back(element);
  }

  // sifts = cv::Mat(14, 2, CV_32F, test_points);

  // Centroid Random initialization
  for (int16_t i = 0; i < k; i++) {
    cv::Mat centroid = sifts.row(0);
    centroid.reserve(sifts.cols);
    for (int j = 0; j < sifts.cols; j++) {
      centroid.at<float>(0, j) = (float)(rand() % 128);
    }
    centroids.push_back(centroid);
  }

  std::cout << "Sift and centroid initialized succesfully!\n";
  std::cout << "Total Sifts: " + std::to_string(sifts.rows) << " x "
            << std::to_string(sifts.cols) + "\n"
            << "Total centroids: " + std::to_string(centroids.rows) << " x "
            << std::to_string(centroids.cols) + "\n";

  for (int iter = 0; iter < max_iter; iter++) {
    auto start_time = std::chrono::high_resolution_clock::now();

    // calculate closest centroid for each point.
    knn_matches.clear();
    matcher->knnMatch(sifts, centroids, knn_matches, 2);
    debug_img(sifts, centroids, knn_matches);
    // Recalculate centroids.

    centroids = cv::Scalar::all(0.0f);
    std::fill(occurences.begin(), occurences.end(), 0);
    std::cout << knn_matches.size() << std::endl;
    for (const auto &match : knn_matches) {
      centroids.row(match[0].trainIdx) += sifts.row(match[0].queryIdx);
      occurences[match[0].trainIdx]++;
    }
    for (int i = 0; i < centroids.rows; i++) {
      if (occurences[i] > 0) {
        centroids.row(i) = centroids.row(i) / (float)occurences[i];
        std::cout << i << "->" << occurences[i] << std::endl;
      } else {
        centroids.row(i) = sifts.row(rand() % sifts.rows);
      }
    }
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
        end_time - start_time);
    std::cout << "Iteration " << iter + 1
              << " completed in " +
                     std::to_string(((float)duration.count() / 1000.0f)) +
                     " seconds!\n";
  }
  return centroids;
}

int main() {
  // std::vector<cv::Mat> sifts =
  //     ipb::serialization::sifts::LoadDataset("../test_dataset");
  std::vector<cv::Mat> sifts =
      ipb::serialization::sifts::LoadDataset("../../dataset/final_project/bin");
  // for (const auto &element : sifts) {
  //   std::cout << " ---- " << element.size << " ---- " << std::endl;
  // }
  cv::Mat ans_mat = ipb::kMeans(sifts, 1000, 100);
  ipb::BowDictionary &dictionary = ipb::BowDictionary::GetInstance();
  // dictionary.set_params(50, 25, sifts);
  // std::cout << ans << std::endl;
}