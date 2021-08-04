#include <bow.hpp>

void ipb::BowDictionary::set_max_iterations(int iterations) {
  m_max_iterations = iterations;
  recompute();
}

void ipb::BowDictionary::set_size(int size) {
  m_n_words = size;
  recompute();
}

void ipb::BowDictionary::set_descriptors(std::vector<cv::Mat> descriptors) {
  m_descriptors = descriptors;
  recompute();
}

void ipb::BowDictionary::set_params(int iterations, int size,
                                    std::vector<cv::Mat> descriptors) {
  m_max_iterations = iterations;
  m_descriptors = descriptors;
  m_n_words = size;
  recompute();
}

void debug_img(const std::vector<ipb::sift> &sifts,
               const std::vector<ipb::sift> &centroids) {
  cv::Mat image(1000, 1600, CV_8UC3);
  int color_increment = 255 / centroids.size();
  for (const ipb::sift &sift : sifts) {
    cv::circle(image, cv::Point(sift.descriptor[0] * 5, sift.descriptor[1] * 5),
               2,
               cv::Scalar(255 - color_increment * sift.cluster,
                          color_increment * sift.cluster, 0),
               cv::FILLED);
  }
  for (const ipb::sift &centroid : centroids) {
    cv::line(
        image,
        cv::Point(centroid.descriptor[0] * 5 - 5, centroid.descriptor[1] * 5),
        cv::Point(centroid.descriptor[0] * 5 + 5, centroid.descriptor[1] * 5),
        cv::Scalar(255 - color_increment * centroid.cluster,
                   color_increment * centroid.cluster, 0),
        2);
    cv::line(
        image,
        cv::Point(centroid.descriptor[0] * 5, centroid.descriptor[1] * 5 - 5),
        cv::Point(centroid.descriptor[0] * 5, centroid.descriptor[1] * 5 + 5),
        cv::Scalar(255 - color_increment * centroid.cluster,
                   color_increment * centroid.cluster, 0),
        2);

    // cv::putText(image, std::to_string(centroid.associated_points),
    //             cv::Point(centroid.descriptor[0] * 5,
    //                       centroid.descriptor[1] * 5),
    //             cv::FONT_HERSHEY_COMPLEX_SMALL, 0.8, cv::Scalar(255, 255,
    //             255));
  }
  cv::namedWindow("Debug Image");
  cv::imshow("Debug Image", image);
  cv::waitKey(75);
  image = cv::Mat::zeros(image.size(), image.type());
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

  // Centroid Random initialization
  for (int16_t i = 0; i < k; i++) {
    std::vector<int> centroid;
    centroid.reserve(sifts[0].descriptor.size());
    for (int j = 0; j < sifts[0].descriptor.size(); j++) {
      centroid.emplace_back((rand() % 128));
    }
    centroids.emplace_back(sift(centroid, i));
  }

  std::cout << "Sift and centroid initialized succesfully!\n";
  std::cout << "Total Sifts: " + std::to_string(sifts.size()) + "\n";

  for (int iter = 0; iter < max_iter; iter++) {
    // visualize debug image
    debug_img(sifts, centroids);

    auto start_time = std::chrono::high_resolution_clock::now();

    // calculate closest centroid for each point. Parallel computing for more
    // speed
    std::for_each(std::execution::par, sifts.begin(), sifts.end(),
                  [centroids](sift &descriptor) {
                    descriptor.closest_centroid(centroids);
                  });

    // for (sift &descriptor : sifts) {
    //   descriptor.reset();
    //   for (const sift &centroid : centroids) {
    //     unsigned long int d = descriptor.distance(centroid);
    //     if (d < descriptor.distance_to_cluster) {
    //       descriptor.distance_to_cluster = d;
    //       descriptor.cluster = centroid.cluster;
    //     }
    //   }
    // }

    // Recalculate centroids. Parallel computing for more speed
    std::for_each(std::execution::par, centroids.begin(), centroids.end(),
                  [](sift &centroid) { centroid.clear(); });

    // for (sift &centroid : centroids) {
    //   centroid.clear();
    // }

    for (const sift &descriptor : sifts) {
      centroids.at(descriptor.cluster) += descriptor;
      centroids.at(descriptor.cluster).associated_points++;
    }
    for (sift &centroid : centroids) {
      if (centroid.associated_points > 0) {
        centroid = centroid / centroid.associated_points;
      }
      centroid.associated_points = 0;
    }
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
        end_time - start_time);
    std::cout << "Iteration " << iter + 1
              << " completed in " +
                     std::to_string(((float)duration.count() / 1000.0f)) +
                     " seconds!\n";
  }

  // generate output Mat
  cv::Mat ans_mat;
  for (const sift &centroid : centroids) {
    ans_mat.push_back(centroid.descriptor);
  }
  return ans_mat;
}

int main() {
  // std::vector<cv::Mat> sifts =
  //     ipb::serialization::sifts::LoadDataset("../test_dataset");
  std::vector<cv::Mat> sifts =
      ipb::serialization::sifts::LoadDataset("../../dataset/final_project/bin");
  // for (const auto &element : sifts) {
  //   std::cout << " ---- " << element.size << " ---- " << std::endl;
  // }
  ipb::BowDictionary &dictionary = ipb::BowDictionary::GetInstance();
  dictionary.set_params(50, 25, sifts);
  // std::cout << ans << std::endl;
}