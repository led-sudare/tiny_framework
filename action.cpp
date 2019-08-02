#include "action.h"
#include <sudare.h>

namespace sudare {
void stop::operator()(cv::Mat const &img) {
  sudare_clear();
  for (int x = 0; x < img.cols; ++x) {
    for (int y = 0; y < img.rows; ++y) {
      auto v = img.at<cv::Vec3b>(y, x);
      int z = 15;
      int rgb = (v[2] << 16) + (v[1] << 8) + (v[0] & 0xFF);
      sudare_set_led_rect(x, y, z, rgb);
    }
  }
  sudare_send();
}

bottom_up::bottom_up() : m(0) {}
void bottom_up::operator()(cv::Mat const &img) {}

left_right::left_right() : m(0) {}
void left_right::operator()(cv::Mat const &img) {}

back_front::back_front() : m(0) {}
void back_front::operator()(cv::Mat const &img) {}
}  // namespace sudare