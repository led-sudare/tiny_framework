#include "action.h"
#include <sudare.h>
#include <cmath>

namespace sudare {
int get_rgb(cv::Vec3b const &v) {
  return (v[2] << 16) + (v[1] << 8) + (v[0] & 0xFF);
}
void stop::operator()(cv::Mat const &img) {
  sudare_clear();
#if 0
  for (int x = 0; x < img.cols; ++x) {
    for (int y = 0; y < img.rows; ++y) {
      auto v = img.at<cv::Vec3b>(y, x);
      int rgb = (v[2] << 16) + (v[1] << 8) + (v[0] & 0xFF);
      for (int z = 14; z < 16; ++z) {
        sudare_set_led_rect(x, y, z, rgb);
      }
    }
  }
#else
  for (int a = 0; a < 30; ++a) {
    for (int r = 0; r < 15; ++r) {
      int x0 = 15 - r;
      int x1 = r + 15;
      for (int y = 0; y < 100; ++y) {
        sudare_set_led_polar(a, r, y, get_rgb(img.at<cv::Vec3b>(y, x0)));
        sudare_set_led_polar(a + 30, r, y, get_rgb(img.at<cv::Vec3b>(y, x1)));
      }
    }
  }
#endif
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

void huge::operator()(cv::Mat const &img) {
  sudare_clear();
  m = (m + 5) % 100;
  cv::Size size = img.size();
  size.width += 2 * m;
  size.height += 2 * m;
  cv::Mat img2;
  cv::resize(img, img2, size);
  for (int x = 0; x < img.cols; ++x) {
    for (int y = 0; y < img.rows; ++y) {
      auto v = img2.at<cv::Vec3b>(y + m, x + m);
      int rgb = (v[2] << 16) + (v[1] << 8) + (v[0] & 0xFF);
      for (int z = 14; z < 16; ++z) {
        sudare_set_led_rect(x, y, z, rgb);
      }
    }
  }
  sudare_send();
}

void circle::operator()(cv::Mat const &img) {
  sudare_clear();
  m = (m + 1) % 10;
  double theta = M_PI / 5 * m;
  int dx = static_cast<int>(std::sin(theta) * 10);
  int dy = static_cast<int>(std::cos(theta) * 10);
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
}  // namespace sudare