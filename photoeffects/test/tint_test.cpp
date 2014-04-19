#include "photoeffects.hpp"
#include "test_utils.hpp"
#include <gtest/gtest.h>

using namespace cv;

TEST(photoeffects, TintTest) {
    Mat src(10, 10, CV_8UC3), dst;
    Vec3b color;
    EXPECT_EQ(0, tint(src, dst, color, 0.0f));
}

TEST(photoeffects, TintWrongImage)
{
    Mat src(10, 10, CV_8UC2), dst;
    Vec3b color;
    EXPECT_ERROR(CV_StsAssert, tint(src, dst, color, 0.5f));
}

TEST(photoeffects, TintWrongDensity)
{
    Mat src(10, 10, CV_8UC3), dst;
    Vec3b color;

    EXPECT_ERROR(CV_StsAssert, tint(src, dst, color, 15.0f));
    EXPECT_ERROR(CV_StsAssert, tint(src, dst, color, -1.0f));
}

TEST(photoeffects, TintTestOutputImage)
{
    Mat src(256, 256, CV_8UC3), dstOrigin(256, 256, CV_8UC3), dstFromAlg;
    Vec3b color(255, 0, 255);
    float den = 0.2f;
    float negDen = 1 - den;

    for (int i = 0; i < 256; i++)
    {
        for (int j = 0; j < 256; j++)
        {
             src.at<Vec3b>(i, j) = Vec3b(i, j, 0);
             dstOrigin.at<Vec3b>(i, j) = color * den + Vec3b(i, j, 0) * negDen;
        }
    }
    tint(src, dstFromAlg, color, den);

    Mat diff = abs(dstOrigin - dstFromAlg);
    Mat mask = diff.reshape(1) > 1;
    EXPECT_EQ(0, countNonZero(mask));
}
