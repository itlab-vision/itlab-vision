#include <gtest/gtest.h>

#include "photoeffects.hpp"

using namespace cv;

TEST(photoeffects, TintTest) {
    Mat image(10, 10, CV_8UC1), image1(10, 10, CV_8UC1);
    Vec3b color;
    color.all(0);
    EXPECT_EQ(0, tint(image, color, 0.0, image1));
}
