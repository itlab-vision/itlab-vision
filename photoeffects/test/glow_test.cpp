#include "photoeffects.hpp"
#include "test_utils.hpp"
#include <gtest/gtest.h>

using namespace cv;

TEST(photoeffects, GlowTest) {
    Mat image(10, 10, CV_32FC3), dst;

    EXPECT_EQ(0, glow(image, dst, 1.0f, 0.5f));
}

TEST(photoeffects, GlowTestRegression) {
    Mat image, dst, rightDst;

    image = imread("glow_test.png", CV_LOAD_IMAGE_COLOR);
    rightDst = imread("glow_test_result.png", CV_LOAD_IMAGE_COLOR);

    EXPECT_EQ(0, glow(image, dst, 7.0f, 0.9f));

    for (int i = 0; i < dst.rows; i++)
    {
    	for (int j = 0; j < dst.cols; j++)
    	{
    		for (int k = 0; k < 3; k++)
    		{
    			ASSERT_EQ(rightDst.at<Vec3b>(i, j)[k], dst.at<Vec3b>(i, j)[k]);
    		}
    	}
    }
}

TEST(photoeffects, GlowTestBadSigma) {
    Mat image(10, 10, CV_32FC3), dst;

    EXPECT_ERROR(CV_StsAssert, glow(image, dst, -1.0f, 0.5f));
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