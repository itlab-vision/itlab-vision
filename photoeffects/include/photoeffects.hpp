#pragma once

#include <opencv2/core/core.hpp>

int sepia(cv::InputArray src, cv::OutputArray dst);

int filmGrain(cv::InputArray src, cv::OutputArray dst);

int fadeColor(cv::InputArray src, cv::OutputArray dst);

int tint(cv::InputArray src, cv::Vec3b* colorTint, float density, cv::OutputArray dst);

int glow(cv::Mat& image);

int boost_color(cv::Mat& image);

cv::Mat antique(cv::Mat& image);
