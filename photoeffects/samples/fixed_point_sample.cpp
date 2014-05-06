#include <stdio.h>
#include <iostream>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

#if 1
   #include <stdio.h>
   #define TIMER_START(name) int64 t_##name = getTickCount()
   #define TIMER_END(name) printf("TIMER_" #name ":\t%6.2fms\n", \
               1000.f * ((getTickCount() - t_##name) / getTickFrequency()))
#else
   #define TIMER_START(name)
   #define TIMER_END(name)
#endif

int compare(Mat m1, Mat m2)
{
	int tolerance = 1; // We allow difference = 1

    Mat diff = abs(m1 - m2);    
    Mat mask = diff.reshape(1) > tolerance; 
    return countNonZero(mask);
}

int main(int argc, char **argv)
{
    Size sz(1920, 1080);
    Mat src1(sz, CV_8UC3);//, Scalar(255, 0, 0));
    Mat src2(sz, CV_8UC3);//, Scalar(0, 255, 0));
	randu(src1, 0, 256);
	randu(src2, 0, 256);
    float alpha = 0.7;

    TIMER_START(1_SIMPLE_SUM);
    Mat dst1 = src1 * alpha + src2 * (1 - alpha);
    TIMER_END(1_SIMPLE_SUM);
    std::cout << dst1.col(0).row(0) << std::endl;

    // This is not correct, because we have saturation after first subtraction
    // This is also slower, because we have two operations with 8UC3 matrices
    TIMER_START(2_OPEN_BRACKETS);
    Mat dst2 = (src1 - src2) * alpha + src2; 
    TIMER_END(2_OPEN_BRACKETS);
    std::cout << dst2.col(0).row(0) << std::endl;
    if (compare(dst1, dst2))
        printf("ERROR: dst1 != dst2\n");

    TIMER_START(3_FIXED_POINT);
    uchar coeff = static_cast<uchar>(alpha * 256.0 + 0.5);
    Mat dst3 = (src1 * coeff + src2 * (256 - coeff)) / 256;
    TIMER_END(3_FIXED_POINT);
    std::cout << dst3.col(0).row(0) << std::endl;
    if (compare(dst1, dst3))
        printf("ERROR: dst1 != dst3\n");

    // imshow("dst1", dst1);
    // waitKey(0);
}