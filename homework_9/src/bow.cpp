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
    auto start_time = std::chrono::high_resolution_clock::now();

    // calculate closest centroid for each point. Parallel computing for more
    // speed
    std::for_each(std::execution::par, sifts.begin(), sifts.end(),
                  [centroids](sift &descriptor) {
                    descriptor.closest_centroid(centroids);
                  });

    // Recalculate centroids. Parallel computing for more speed
    std::for_each(std::execution::par, centroids.begin(), centroids.end(),
                  [](sift &centroid) { centroid.clear(); });

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
  // dictionary.set_params(50, 25, sifts);
  // std::cout << ans << std::endl;
}