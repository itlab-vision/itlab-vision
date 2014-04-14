#pragma once

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

int sepia(cv::InputArray src, cv::OutputArray dst);

int filmGrain(cv::InputArray src, cv::OutputArray dst, int grainValue=8);

int fadeColor(cv::InputArray src, cv::OutputArray dst);

cv::Mat tint(cv::Mat& image, int hue, float sat);

int glow(cv::Mat& image);

int boostColor(cv::Mat& image);

cv::Mat antique(cv::Mat& image);
