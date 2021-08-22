#ifndef BOW_HPP_
#define BOW_HPP_

#include <algorithm>
#include <chrono>
#include <convert_dataset.hpp>
#include <ctime>
#include <execution>
#include <functional>
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/core/mat.hpp>
#include <serialize.hpp>
#include <string>
#include <thread>
#include <vector>

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

class BowDictionary {
private:
  BowDictionary() = default;
  ~BowDictionary() = default;

public:
  BowDictionary(const BowDictionary &) = delete;
  void operator=(const BowDictionary &) = delete;
  static BowDictionary &GetInstance() {
    static BowDictionary instance;
    return instance;
  }

private:
  cv::Mat m_dictionary;

public:
  // Getters methods
  int size() const {
    return m_dictionary.rows;
  }; // number of centroids / codewords
  cv::Mat vocabulary() const { return m_dictionary; };
  cv::Mat &vocabulary() { return m_dictionary; };
  bool empty() { return m_dictionary.empty(); };
  // Setters methods
  void build(int iterations, int size, const std::vector<cv::Mat> &descriptors);
  void set_vocabulary(const std::string &filename);

  void save_vocabulary(const std::string &filename);
};

class Histogram {
public:
  Histogram();
  Histogram(std::vector<int> &data);
  Histogram(cv::Mat &descriptors, cv::Mat &dictionary);

  friend std::ostream &operator<<(std::ostream &out,
                                  const Histogram &histogram) {
    for (const auto &data_point : histogram.data_) {
      out << data_point << " ";
    }
    out << std::endl;
    return out;
  }
  void WriteToCSV(const std::string &filename);
  void ReadFromCSV(const std::string &filename);

  // Imitate stl_vector functionality
  int &operator[](int i) { return data_[i]; };
  int operator[](int i) const { return data_[i]; };
  std::vector<int> data() const { return data_; };
  int size() const { return data_.size(); };
  bool empty() const { return data_.size() > 0 ? true : false; }
  std::vector<int>::const_iterator begin() const { return data_.begin(); }
  std::vector<int>::const_iterator cbegin() const { return data_.cbegin(); }
  std::vector<int>::const_iterator end() const { return data_.end(); }
  std::vector<int>::const_iterator cend() const { return data_.cend(); }

private:
  // data members:
  std::vector<int> data_;
  inline static cv::Ptr<cv::DescriptorMatcher> matcher_ = nullptr;
  inline static std::vector<std::vector<cv::DMatch>> knn_matches;
  inline static std::ifstream fin = std::ifstream();
  inline static std::ofstream fout = std::ofstream();
};

} // namespace ipb
#endif