#include "action.h"
#include <sudare.h>

namespace sudare {
void stop::operator()(cv::Mat const &img) {
  sudare_clear();
  for (int x = 0; x < img.cols; ++x) {
    for (int y = 0; y < img.rows; ++y) {
      auto v = img.at<cv::Vec3b>(y, x);
      int rgb = (v[2] << 16) + (v[1] << 8) + (v[0] & 0xFF);
      for (int z = 14; z < 16; ++z) {
        sudare_set_led_rect(x, y, z, rgb);
      }
    }
  }
  sudare_send();
}

void bottom_up::operator()(cv::Mat const &img) {
  sudare_clear();
  m = (m % 200) + 5;
  for (int x = 0; x < img.cols; ++x) {
    for (int y = 0; y < img.rows; ++y) {
      auto v = img.at<cv::Vec3b>(y, x);
      int rgb = (v[2] << 16) + (v[1] << 8) + (v[0] & 0xFF);
      for (int z = 14; z < 16; ++z) {
        sudare_set_led_rect(x, y + m - 100, z, rgb);
      }
    }
  }
  sudare_send();
}

void left_right::operator()(cv::Mat const &img) {
  sudare_clear();
  m = (m % 60) + 3;
  for (int x = 0; x < img.cols; ++x) {
    for (int y = 0; y < img.rows; ++y) {
      auto v = img.at<cv::Vec3b>(y, x);
      int rgb = (v[2] << 16) + (v[1] << 8) + (v[0] & 0xFF);
      for (int z = 14; z < 16; ++z) {
        sudare_set_led_rect(x + m - 30, y, z, rgb);
      }
    }
  }
  sudare_send();
}

void back_front::operator()(cv::Mat const &img) {}
}  // namespace sudare