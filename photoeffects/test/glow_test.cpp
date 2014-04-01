#include <gtest/gtest.h>

#include "photoeffects.hpp"

using namespace cv;

TEST(photoeffects, GlowTest) {
    Mat image(10, 10, CV_32FC3), dst;

    EXPECT_EQ(0, glow(image, 1.0f, 0.5f, dst));
}

TEST(photoeffects, GlowTestBadRadius) {
    Mat image(10, 10, CV_32FC3), dst;

    EXPECT_EQ(2, glow(image, -1.0f, 0.5f, dst));
}

TEST(photoeffects, GlowTestBadIntensity) {
    Mat image(10, 10, CV_32FC3), dst;

    EXPECT_EQ(3, glow(image, 5.0f, 5.0f, dst));
    EXPECT_EQ(3, glow(image, 5.0f, -5.0f, dst));
}

TEST(photoeffects, GlowTestBadImage) {
    Mat image(10, 10, CV_8UC1), dst;

    EXPECT_EQ(1, glow(image, 5.0f, 0.5f, dst));
}