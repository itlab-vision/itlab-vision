#pragma once

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

int sepia(cv::InputArray src, cv::OutputArray dst);

int filmGrain(cv::InputArray src, cv::OutputArray dst);

int fadeColor(cv::InputArray src, cv::OutputArray dst);

int tint(cv::InputArray src, cv::OutputArray dst, const cv::Vec3b &colorTint, float density);

int edgeBlur(cv::InputArray src, cv::OutputArray dst, int indentTop, int indentLeft);

int glow(cv::Mat& image);

int boost_color(cv::Mat& image);

cv::Mat antique(cv::Mat& image);
