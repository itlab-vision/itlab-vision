#include <gtest/gtest.h>
#include "test_utils.hpp"
#include "photoeffects.hpp"

using namespace cv;

TEST(photoeffects, MatteTest)
{
    Mat srcUCThreeChannels(10, 10, CV_8UC3);
    Point fisrtpoint(0, 0);
    Point secondpoint(10, 10);
    Mat srcFCThreeChannels(10, 10, CV_32FC3);
    EXPECT_EQ(0, matte(image, image, fisrtpoint, secondpoint, 1.0f, 1.0f));
}

TEST(photoeffects, MatteInvalidImageFormat)
{
    Mat src(10, 10, CV_8UC1);
    Mat dst;
    Point firstpoint(0, 0);
    Point secondpoint(10, 10);
    EXPECT_ERROR(CV_StsAsset, matte(src, dst, firstpoint, secondpoint, 1.0f, 1.0f));
}

