#include <gtest/gtest.h>

#include "photoeffects.hpp"

using namespace cv;

TEST(photoeffects, GlowTest) {
    Mat image;

    EXPECT_EQ(0, glow(image, 1.0, 0.0, image));
}