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

TEST(photoeffects, VignetteRegressionTest)
{
    string input = "./testdata/vignette_test.png";
    string expectedOutput = "./testdata/vignette_test_result.png";

    Mat image, dst, rightDst;
    image = imread(input, CV_LOAD_IMAGE_COLOR);
    rightDst = imread(expectedOutput, CV_LOAD_IMAGE_COLOR);

    if (image.empty())
    {
        FAIL() << "Can't read " + input + " image";
    }
    if (rightDst.empty())
    {
        FAIL() << "Can't read " + expectedOutput + " image";
    }

    Size rect;
    rect.height = image.rows / 1.5f;
    rect.width = image.cols / 2.0f;

    EXPECT_EQ(0, vignette(image, dst, rect));

    Mat diff = abs(rightDst - dst);
    Mat mask = diff.reshape(1) > 1;
    EXPECT_EQ(0, countNonZero(mask));
}
