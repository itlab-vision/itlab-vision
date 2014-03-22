#include <gtest/gtest.h>

#include "photoeffects.hpp"

using namespace cv;

TEST(photoeffects, GlowTest) {
    Mat image(10, 10, CV_8UC1);

    EXPECT_EQ(10, glow(image));
}