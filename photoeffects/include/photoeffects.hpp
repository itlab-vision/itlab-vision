#pragma once

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

int sepia(cv::InputArray src, cv::OutputArray dst);

int filmGrain(cv::InputArray src, cv::OutputArray dst);

int fadeColor(cv::InputArray src, cv::OutputArray dst);

cv::Mat tint(cv::Mat& image, int hue, float sat);

int glow(cv::InputArray src, cv::OutputArray dst, float sigma = 1.0f, float intensity = 0.0f);

int boostColor(cv::InputArray src, cv::OutputArray dst, float intensity = 0.0f);

cv::Mat antique(cv::Mat& image);

int vignette(cv::InputArray src, cv::OutputArray dst, cv::Size rect);
