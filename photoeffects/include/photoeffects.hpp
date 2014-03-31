#pragma once

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

int sepia(cv::InputArray src, cv::OutputArray dst, 
	cv::Scalar hue = cv::Scalar(19), 
	cv::Scalar saturation = cv::Scalar(78),
	cv::Scalar value = cv::Scalar(20));

int filmGrain(cv::InputArray src, cv::OutputArray dst);

int fadeColor(cv::InputArray src, cv::OutputArray dst);

cv::Mat tint(cv::Mat& image, int hue, float sat);

int glow(cv::Mat& image);

int boost_color(cv::Mat& image);

cv::Mat antique(cv::Mat& image);
