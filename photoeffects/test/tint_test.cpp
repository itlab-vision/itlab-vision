#include <gtest/gtest.h>

#include "photoeffects.hpp"

using namespace cv;

TEST(photoeffects, TintTest)
{
    Mat image(10, 10, CV_8UC3), image1(10, 10, CV_8UC3);
    Vec3b color;
    image = Scalar(0);
    color.all(0);
    EXPECT_EQ(0, tint(image, image1, &color, 0.0));
}
