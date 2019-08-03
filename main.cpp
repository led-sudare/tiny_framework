#include <sudare.h>
#include <unistd.h>
#include <iostream>
#include <map>
#include <mutex>  // lock_guard
#include <string>
#include <thread>
#include <vector>
#include "action.h"
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
    // cv::flip(m, m, 1);
    cv::flip(m, m, 0);
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
  if (sudare_init_sdk(argv[1])) return 1;
  std::mutex mtx;
  cv::Mat current_image;
  bool enable = true;
  std::shared_ptr<sudare::action> currect_action =
      std::make_shared<sudare::stop>();
  std::thread th0([&mtx, &enable]() {
    for (;;) {
      sleep(1);
      int res = system("ruby get_start_stop.rb");
      std::lock_guard<std::mutex> lock(mtx);
      enable = res == 0;
    }
  });
  std::thread th1([&mtx, &enable, &current_image, &currect_action]() {
    for (;;) {
      sudare_sleep(100);
      try {
        std::lock_guard<std::mutex> lock(mtx);
        if (!enable || current_image.empty()) continue;
        (*currect_action)(current_image);
      } catch (std::exception const& e) {
        std::cerr << e.what() << std::endl;
      }
    }
  });
  const auto images = make_image_map(charactors.begin(), charactors.end());
  sudare::udp_server udp(atoi(argv[2]), 0);
  std::vector<char> buf(1024);
  for (;;) {
    int res = udp.recv(buf.data(), buf.size());
    std::cout << "udp recv " << res << "bytes" << std::endl;
    if (res <= 0) continue;
    picojson::value json;
    std::string err = picojson::parse(json, buf.data());
    if (err.size()) {
      std::cerr << "failed to parse json " << buf.data() << std::endl;
      continue;
    }
    std::cout << json << std::endl;
    picojson::object& obj = json.get<picojson::object>();
    if (json.contains("image")) {
      std::string image = obj["image"].get<std::string>();
      auto img = images.find(image);
      if (img == images.end() || img->second.empty()) {
        std::cerr << "not found " << image << std::endl;
        continue;
      };
      std::lock_guard<std::mutex> lock(mtx);
      current_image = img->second;
    }
    if (json.contains("action")) {
      std::string action = obj["action"].get<std::string>();
      std::lock_guard<std::mutex> lock(mtx);
      currect_action = std::make_shared<sudare::stop>();
      if (action == "bottom_up")
        currect_action = std::make_shared<sudare::bottom_up>();
      if (action == "left_right")
        currect_action = std::make_shared<sudare::left_right>();
      if (action == "back_front")
        currect_action = std::make_shared<sudare::back_front>();
      if (action == "in_the_water")
        currect_action = std::make_shared<sudare::in_the_water>();
      if (action == "vibration")
        currect_action = std::make_shared<sudare::vibration>();
      if (action == "jump") currect_action = std::make_shared<sudare::jump>();
      if (action == "huge") currect_action = std::make_shared<sudare::huge>();
      if (action == "circle")
        currect_action = std::make_shared<sudare::circle>();
    }
  }
  th0.join();  // unreachable
  th1.join();  // unreachable
  return 0;
}
