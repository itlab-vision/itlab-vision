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

TEST(photoeffects, TintRegressionTest)
{
    string input = "./testdata/tint_test.png";
    string expectedOutput = "./testdata/tint_test_result.png";

    Mat src, dst, rightDst;

    src = imread(input, CV_LOAD_IMAGE_COLOR);
    rightDst = imread(expectedOutput, CV_LOAD_IMAGE_COLOR);

    if (src.empty())
        FAIL() << "Can't read " + input + " image";
    if (rightDst.empty())
        FAIL() << "Can't read " + expectedOutput + " image";

    Vec3b color(128, 255, 0);
    EXPECT_EQ(0, tint(src, dst, color, 0.1f));

    Mat diff = abs(rightDst - dst);
    Mat mask = diff.reshape(1) > 1;
    EXPECT_EQ(0, countNonZero(mask));
}