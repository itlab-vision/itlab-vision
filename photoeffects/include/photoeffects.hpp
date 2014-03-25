#pragma once

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

int sepia(cv::InputArray src, cv::OutputArray dst);

int filmGrain(cv::InputArray src, cv::OutputArray dst);

int fadeColor(cv::InputArray src, cv::OutputArray dst);

cv::Mat tint(cv::Mat& image, int hue, float sat);

int glow(cv::InputArray image, unsigned int radius, float intensity, cv::OutputArray dst);

int boost_color(cv::Mat& image);

cv::Mat antique(cv::Mat& image);
