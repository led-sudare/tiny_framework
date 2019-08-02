#include "action.h"
#include <sudare.h>

namespace sudare {
void stop::operator()(cv::Mat const &img) {}

bottom_up::bottom_up() : m(0) {}
void bottom_up::operator()(cv::Mat const &img) {}

left_right::left_right() : m(0) {}
void left_right::operator()(cv::Mat const &img) {}

back_front::back_front() : m(0) {}
void back_front::operator()(cv::Mat const &img) {}
}  // namespace sudare