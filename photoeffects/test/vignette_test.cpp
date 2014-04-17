#include "photoeffects.hpp"
#include "test_utils.hpp"
#include <gtest/gtest.h>

using namespace cv;

TEST(photoeffects, VignetteInvalidArguments)
{
    Mat image(100, 100, CV_8UC1);
    Mat dst;
    Size rectangle;
    rectangle.height = 0;
    rectangle.width = 0;

    EXPECT_ERROR(CV_StsAssert, vignette(image, dst, rectangle));
}

TEST(photoeffects, VignetteTest)
{
    Mat image(100, 100, CV_8UC3);
    Mat dst;
    Size rectangle;
    rectangle.height = image.rows / 1.5f;
    rectangle.width = image.cols / 2.0f;

    EXPECT_EQ(0, vignette(image, dst, rectangle));
}
