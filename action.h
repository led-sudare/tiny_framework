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
  bottom_up() : m(0) {}
  virtual ~bottom_up(){};
  void operator()(cv::Mat const &img);
};
class left_right : public action {
  int m;

 public:
  left_right() : m(0) {}
  virtual ~left_right(){};
  void operator()(cv::Mat const &img);
};
class back_front : public action {
  int m;

 public:
  back_front() : m(0) {}
  virtual ~back_front(){};
  void operator()(cv::Mat const &img);
};
class in_the_water : public action {
  int m;

 public:
  in_the_water() : m(0) {}
  virtual ~in_the_water(){};
  void operator()(cv::Mat const &img);
};
class vibration : public action {
  int m;

 public:
  vibration() : m(0) {}
  virtual ~vibration(){};
  void operator()(cv::Mat const &img);
};
class jump : public action {
  int m;

 public:
  jump() : m(0) {}
  virtual ~jump(){};
  void operator()(cv::Mat const &img);
};
class huge : public action {
  int m;

 public:
  huge() : m(0) {}
  virtual ~huge(){};
  void operator()(cv::Mat const &img);
};
class circle : public action {
  int m;

 public:
  circle() : m(0) {}
  virtual ~circle(){};
  void operator()(cv::Mat const &img);
};
}  // namespace sudare