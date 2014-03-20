#pragma once

#include <opencv2/core/core.hpp>

cv::Mat sepia(cv::Mat& image);

cv::Mat tint(cv::Mat& image, int hue, float sat);

int glow(cv::Mat& image);

int boost_color(cv::Mat& image);
