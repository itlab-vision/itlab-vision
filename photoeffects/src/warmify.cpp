#include "photoeffects.hpp"

using namespace cv;

int warmify(cv::InputArray src, cv::OutputArray dst, uchar delta)
{
    if (src.type() != CV_8UC3)
    {
        return 1;
    }
    Mat img_src(src.size(), CV_8UC3);
    img_src = src.getMat();
    Mat img_dst(img_src.size(), CV_8UC3);
    Vec3b intensity, intensity_new;
    int r = 0;
    int g = 0;

    for (int i = 0; i < img_src.rows; i++)
    {
        for (int j = 0; j < img_src.cols; j++)
        {
            intensity = img_src.at<Vec3b>(i, j);
            intensity_new.val[0] = intensity.val[0];
            g = intensity.val[1] + delta;
            if (g > 255) g = 255;
            r = intensity.val[2] + delta;
            if (r > 255) r = 255;
            intensity_new.val[1] = (uchar)g;
            intensity_new.val[2] = (uchar)r;
            img_dst.at<Vec3b>(i, j) = intensity_new;
        }
    }
    img_dst.convertTo(dst, img_src.type());
    return 0;
}

