#include "action.h"
#include <sudare.h>
#include <cmath>

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
  m = (m + 5) % 200;
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
  m = (m + 3) % 60;
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

void back_front::operator()(cv::Mat const &img) {
  sudare_clear();
  m = (m + 2) % 30;
  for (int x = 0; x < img.cols; ++x) {
    for (int y = 0; y < img.rows; ++y) {
      auto v = img.at<cv::Vec3b>(y, x);
      int rgb = (v[2] << 16) + (v[1] << 8) + (v[0] & 0xFF);
      for (int z = 0; z < 2; ++z) {
        sudare_set_led_rect(x, y, z + m, rgb);
      }
    }
  }
  sudare_send();
}

void in_the_water::operator()(cv::Mat const &img) {
  sudare_clear();
  m = (m + 1) % 30;
  for (int x = 0; x < img.cols; ++x) {
    int z0 = static_cast<int>(std::sin((x + m) * M_PI / 2) * 7 + 14);
    for (int y = 0; y < img.rows; ++y) {
      auto v = img.at<cv::Vec3b>(y, x);
      int rgb = (v[2] << 16) + (v[1] << 8) + (v[0] & 0xFF);
      for (int z = z0; z < z0 + 2; ++z) {
        sudare_set_led_rect(x, y, z, rgb);
      }
    }
  }
  sudare_send();
}

void vibration::operator()(cv::Mat const &img) {
  sudare_clear();
  m = (m + 1) % 40;
  int dx = (m < 20) ? 0 : (m % 2) ? 1 : -1;
  int dy = (20 <= m) ? 0 : (m % 2) ? 1 : -1;
  for (int x = 0; x < img.cols; ++x) {
    for (int y = 0; y < img.rows; ++y) {
      auto v = img.at<cv::Vec3b>(y, x);
      int rgb = (v[2] << 16) + (v[1] << 8) + (v[0] & 0xFF);
      for (int z = 14; z < 16; ++z) {
        sudare_set_led_rect(x + dx, y + dy, z, rgb);
      }
    }
  }
  sudare_send();
}

void jump::operator()(cv::Mat const &img) {
  sudare_clear();
  m = (m + 1) % 10;
  int dy = std::sin(M_PI / 10 * m) * 30;
  for (int x = 0; x < img.cols; ++x) {
    for (int y = 0; y < img.rows; ++y) {
      auto v = img.at<cv::Vec3b>(y, x);
      int rgb = (v[2] << 16) + (v[1] << 8) + (v[0] & 0xFF);
      for (int z = 14; z < 16; ++z) {
        sudare_set_led_rect(x, y + dy, z, rgb);
      }
    }
  }
  sudare_send();
}
}  // namespace sudare