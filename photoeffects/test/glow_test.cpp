#include <gtest/gtest.h>

#include "photoeffects.hpp"

using namespace cv;

TEST(photoeffects, GlowTest) {
    Mat image(10, 10, CV_32FC3), dst;

    EXPECT_EQ(0, glow(image, dst, 1.0f, 0.5f));
}

TEST(photoeffects, GlowTestBadSigma) {
    Mat image(10, 10, CV_32FC3), dst;

    EXPECT_EQ(2, glow(image, dst, -1.0f, 0.5f));
}

TEST(photoeffects, GlowTestBadIntensity) {
    Mat image(10, 10, CV_32FC3), dst;

    EXPECT_EQ(3, glow(image, dst, 5.0f, 5.0f));
    EXPECT_EQ(3, glow(image, dst, 5.0f, -5.0f));
}

TEST(photoeffects, GlowTestBadImage) {
    Mat image(10, 10, CV_8UC1), dst;

    EXPECT_EQ(1, glow(image, dst, 5.0f, 0.5f));
}