#pragma once

#include <opencv2/opencv.hpp>

namespace sudare {
class action {
 public:
  virtual ~action(){};
  virtual void operator()(cv::Mat const &img) = 0;
};
class stop : public action {
 public:
  virtual ~stop(){};
  void operator()(cv::Mat const &img);
};
class bottom_up : public action {
  int m;

 public:
  bottom_up();
  virtual ~bottom_up(){};
  void operator()(cv::Mat const &img);
};
class left_right : public action {
  int m;

 public:
  left_right();
  virtual ~left_right(){};
  void operator()(cv::Mat const &img);
};
class back_front : public action {
  int m;

 public:
  back_front();
  virtual ~back_front(){};
  void operator()(cv::Mat const &img);
};
}  // namespace sudare