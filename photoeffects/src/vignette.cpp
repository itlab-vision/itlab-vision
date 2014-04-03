#include "photoeffects.hpp"

using namespace cv;

int vignette(InputArray src, OutputArray dst, int diff_height, int diff_width, int opacity)
{
    Mat img_src = src.getMat();
    Mat img_dst(img_src.size(), CV_8UC3);
    Vec3b intensity;
    //intensity.all(Vec3b(0));
    Vec3b intensity_new;
    //intensity_new.all(Scalar(0));

    uchar red, green, blue;

    for (int i = 0; i < img_src.rows; i++)
    {
        for (int j = 0; j < img_src.cols; j++)
        {
            intensity = img_src.at<Vec3b>(i, j);
            blue = intensity.val[0];
            green = intensity.val[1];
            red = intensity.val[2];
            blue = (uchar)(blue / 3);
            green = (uchar)(green / 3);
            red = (uchar)(red / 3);
            intensity_new.val[0] = blue;
            intensity_new.val[1] = green;
            intensity_new.val[2] = red;
            img_dst.at<Vec3b>() = intensity_new;
        }
    }
    img_dst.convertTo(dst, CV_8UC3);
    return 0;
}
