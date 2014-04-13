#include "photoeffects.hpp"
#include "test_utils.hpp"
#include <gtest/gtest.h>

using namespace cv;

const char *ORIGINAL_IMAGE_TEST="../itlab-vision/photoeffects/test/images/fadeColor_test.png";
const char *FADE_IMAGE_TEST="../itlab-vision/photoeffects/test/images/fadeColor_result.png";
TEST(photoeffects, FadeColorInvalidImageFormat)
{
    Mat src(10, 20, CV_8UC2);
    Mat dst;

    EXPECT_ERROR(CV_StsAssert, fadeColor(src, dst, Point(5, 5), Point(5, 10)));
}
TEST(photoeffects, FadeColorInvalidArgument)
{
    Mat src(10, 20, CV_8UC1);
    Mat dst;

    EXPECT_ERROR(CV_StsAssert, fadeColor(src, dst, Point(50,5), Point(5,10)));
    EXPECT_ERROR(CV_StsAssert, fadeColor(src, dst, Point(5,5), Point(5,-10)));
    EXPECT_ERROR(CV_StsAssert, fadeColor(src, dst, Point(5,5), Point(5,5)));
}
TEST(photoeffects, FadeColorTest) {
    Mat imageWithOneChannel(10, 20, CV_8UC1);
    Mat imageWithThreeChannel(10, 20, CV_8UC3);
    Mat dst;
    EXPECT_EQ(0, fadeColor(imageWithOneChannel, dst, Point(5,5), Point(5,10)));
    EXPECT_EQ(0, fadeColor(imageWithThreeChannel, dst, Point(5,5), Point(5,10)));
}
TEST(photoeffects, FadeColorRegressionTest)
{
    Mat image, dst, rightDst;
    image = imread(ORIGINAL_IMAGE_TEST, CV_LOAD_IMAGE_COLOR);
    rightDst = imread(FADE_IMAGE_TEST, CV_LOAD_IMAGE_COLOR);

    EXPECT_EQ(0, fadeColor(image, dst, Point(100, 100), Point(250, 250)));

    for (int i=0; i<dst.rows; i++)
    {
        for (int j=0; j<dst.cols; j++)
        {
            for (int k=0; k<3; k++)
            {
                ASSERT_EQ(rightDst.at<Vec3b>(i, j)[k], dst.at<Vec3b>(i, j)[k]);
            }
        }
    }
}
