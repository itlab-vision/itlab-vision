#include <gtest/gtest.h>

#include "photoeffects.hpp"

using namespace cv;

TEST(photoeffects, SepiaFakeTest) {
    Mat src(10, 10, CV_8UC1), dst;

    EXPECT_EQ(0, sepia(src, dst));
}

TEST(photoeffects, SepiaFailTest) {
    Mat src(10, 10, CV_8UC3), dst;

    EXPECT_EQ(1, sepia(src, dst));
}

TEST(photoeffects, SepiaTest) {
    Mat src(10, 10, CV_8UC1), dst, hsvDst;
    vector<Mat> channels(3);

    EXPECT_EQ(0, sepia(src, dst));
    cvtColor(dst, hsvDst, CV_BGR2HSV);
    split(hsvDst, channels);
    EXPECT_LE(19 - 1, channels[0].at<uchar>(0, 0)); // hue = 19
    EXPECT_GE(19 + 1, channels[0].at<uchar>(0, 0));
    EXPECT_LE(78 - 1, channels[1].at<uchar>(0, 0)); // saturation = 78
    EXPECT_GE(78 + 1, channels[1].at<uchar>(0, 0));
    EXPECT_LE(src.at<uchar>(0, 0) + 20 - 1, channels[2].at<uchar>(0, 0));
    EXPECT_GE(src.at<uchar>(0, 0) + 20 + 1, channels[2].at<uchar>(0, 0));
}

