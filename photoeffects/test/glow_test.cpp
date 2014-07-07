#include "photoeffects.hpp"
#include "test_utils.hpp"
#include <gtest/gtest.h>

using namespace cv;

TEST(photoeffects, GlowTest) {
    Mat image(10, 10, CV_32FC3), dst;
    image = Mat::zeros(10, 10, CV_32FC3);

    EXPECT_EQ(0, glow(image, dst, 1.0f, 0.5f));
}

TEST(photoeffects, GlowTestRegression) {
    string input = "./testdata/glow_test.png";
    string expectedOutput = "./testdata/glow_test_result.png";

    Mat image, rightDst;

    image = imread(input, CV_LOAD_IMAGE_COLOR);
    rightDst = imread(expectedOutput, CV_LOAD_IMAGE_COLOR);

    if (image.empty())
        FAIL() << "Can't read " + input + " image";
    if (rightDst.empty())
        FAIL() << "Can't read " + expectedOutput + " image";

    Mat dst;
    EXPECT_EQ(0, glow(image, dst, 33, 0.9f));
    Mat diff = abs(rightDst - dst);
    Mat mask = diff.reshape(1) > 1;
    EXPECT_EQ(0, countNonZero(mask));
}

TEST(photoeffects, GlowTestBadRadius) {
    Mat image(10, 10, CV_32FC3), dst;

    EXPECT_ERROR(CV_StsAssert, glow(image, dst, -1, 0.5f));
}

TEST(photoeffects, GlowTestBadIntensity) {
    Mat image(10, 10, CV_32FC3), dst;

    EXPECT_ERROR(CV_StsAssert, glow(image, dst, 5.0f, 5.0f));
    EXPECT_ERROR(CV_StsAssert, glow(image, dst, 5.0f, -5.0f));
}

TEST(photoeffects, GlowTestBadImage) {
    Mat image(10, 10, CV_8UC1), dst;

    EXPECT_ERROR(CV_StsAssert, glow(image, dst, 5.0f, 0.5f));
}