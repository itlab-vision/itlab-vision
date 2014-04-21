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
