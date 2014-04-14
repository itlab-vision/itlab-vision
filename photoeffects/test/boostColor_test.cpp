#include "photoeffects.hpp"
#include "test_utils.hpp"
#include <gtest/gtest.h>

using namespace cv;

TEST(photoeffects, BoostColorTest)
{
    Mat image(10, 10, CV_32FC3), dst;

    EXPECT_EQ(0, boostColor(image, dst, 0.5f));
}

TEST(photoeffects, BoostColorRegressionTest)
{
    Mat image, dst, rightDst;
    image = imread("../itlab-vision/photoeffects/test/images/boostColor_test.png",  CV_LOAD_IMAGE_COLOR);
    rightDst = imread("../itlab-vision/photoeffects/test/images/boostColor_test_result.png",  CV_LOAD_IMAGE_COLOR);

    EXPECT_EQ(0, boostColor(image, dst, 0.5f));

    for (int i = 0; i < dst.rows; i++)
    {
        for (int j = 0; j < dst.cols; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                ASSERT_LE(rightDst.at<Vec3b>(i, j)[k] - 1, dst.at<Vec3b>(i, j)[k]);
                ASSERT_GE(rightDst.at<Vec3b>(i, j)[k] + 1, dst.at<Vec3b>(i, j)[k]);
            }
        }
    }    
}

TEST(photoeffects, BoostColorTestBadIntensity)
{
    Mat image(10, 10, CV_32FC3), dst;

    EXPECT_ERROR(CV_StsAssert, boostColor(image, dst, -1.0f));
    EXPECT_ERROR(CV_StsAssert, boostColor(image, dst, 2.0f));
}

TEST(photoeffects, BoostColorTestBadImage)
{
    Mat image(10, 10, CV_8UC1), dst;

    EXPECT_ERROR(CV_StsAssert, boostColor(image, dst, 0.5f));
}