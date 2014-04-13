#include <gtest/gtest.h>
#include "photoeffects.hpp"

using namespace cv;

TEST(photoeffects, VignetteTest)
{
    Mat image(100, 100, CV_8UC3), dst;
    Size rectangle;
    rectangle.width = image.cols / 2;
    rectangle.height = image.rows / 2;
    EXPECT_EQ(0, vignette(image, dst, rectangle));
}
