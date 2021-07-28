#ifndef BOW_HPP_
#define BOW_HPP_

#include <convert_dataset.hpp>
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/core/mat.hpp>
#include <serialize.hpp>

namespace ipb {

/**
 * @brief
 * 1. Given cluster centroids i initialized in some way,
 * 2. For iteration t=1..T:
 * 1. Compute the distance from each point x to each cluster centroid ,
 * 2. Assign each point to the centroid it is closest to,
 * 3. Recompute each centroid as the mean of all points assigned to it,
 *
 * @param descriptors The input SIFT descriptors to cluster.
 * @param k The size of the dictionary, ie, number of visual words.
 * @param max_iterations Maximum number of iterations before convergence.
 * @return cv::Mat One unique Matrix representing all the $k$-means(stacked).
 */
cv::Mat kMeans(const std::vector<cv::Mat> &descriptors, int k, int max_iter);

struct sift {
  std::vector<int> descriptor;
  int16_t cluster = -1;
  unsigned long int distance_to_cluster = pow(2, 62) - 1;
  int associated_points = 0;

  sift();
  sift(std::vector<int> d) { descriptor = d; }
  sift(std::vector<int> d, int n) {
    descriptor = d;
    cluster = n;
  }
  sift(std::vector<int> d, int n, float d_to_clust) {
    descriptor = d;
    cluster = n;
    distance_to_cluster = d_to_clust;
  }
  unsigned long int distance(const sift &p) const {
    unsigned long int d;
    for (int i = 0; i < descriptor.size(); i++) {
      d += pow((descriptor[i] - p.descriptor[i]), 2);
    }
    return d;
  }
  void print() {
    for (int i = 0; i < descriptor.size(); i++) {
      std::cout << descriptor[i] << " ";
    }
    std::cout << "\n";
  }
  sift &operator+=(sift const &obj) {
    for (int i = 0; i < this->descriptor.size(); i++) {
      this->descriptor.at(i) = this->descriptor[i] + obj.descriptor[i];
    }
    return *this;
  }
  sift &operator/(int const &denom) {
    for (int i = 0; i < descriptor.size(); i++) {
      this->descriptor.at(i) = descriptor[i] / denom;
    }
    return *this;
  }
};

class BowDictionary {};

} // namespace ipb
#endif