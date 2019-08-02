#include <sudare.h>
#include <iostream>
#include <map>
#include <mutex>  // lock_guard
#include <opencv2/opencv.hpp>
#include <string>
#include <thread>
#include <vector>
#include "picojson.h"
#include "udp_server.h"

namespace {
const std::vector<std::string> charactors{
    "btc",    "doraemon",    "droid",    "krillin", "miku",      "pikachu",
    "rocket", "slimeknight", "ultraman", "chopper", "dorami",    "elsa",
    "makey",  "minion",      "r2d2",     "slime",   "spiderman", "popteamepic"};
template <typename iterator>
std::map<std::string, cv::Mat> make_image_map(iterator begin, iterator end) {
  std::map<std::string, cv::Mat> dst;
  for (auto it = begin; it != end; ++it) {
    std::string const path = "./img/" + *it + ".png";
    cv::Mat m = cv::imread(path, 1);
    if (m.empty()) {
      std::cerr << "failed to read " << path << std::endl;
      continue;
    }
    std::cout << *it << " -> " << path << std::endl;
    cv::resize(m, m, cv::Size(30, 100));
    dst[*it] = m;
  }
  return dst;
}

}  // namespace
int main(int argc, const char* argv[]) {
  if (argc <= 2) {
    std::cerr << "input [ZMQ ex:192.168.11.20:5511] [UDP PORT]" << std::endl;
    return 1;
  }
  const auto images = make_image_map(charactors.begin(), charactors.end());
  sudare::udp_server udp(atoi(argv[2]), 0);
  if (sudare_init_sdk(argv[1])) return 1;
  std::mutex mtx;
  std::thread th([&mtx, &images]() {
    for (;;) {
    }
  });
  for (;;) {
  }
  return 0;
}
