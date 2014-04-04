#include "photoeffects.hpp"

using namespace cv;

int vignette(InputArray src, OutputArray dst, Size rect)
{
    Mat img_src(src.size(), src.type());
    img_src = src.getMat();
    Mat img_dst(img_src.size(), img_src.type());
    Vec3b intensity, intensity_new;
    double a = rect.height / 2.0f;
    double b = rect.width / 2.0f;
    double radius_ellipse = 0.0f;
    double max_radius = sqrt((img_src.rows / 2) * (img_src.rows / 2) + (img_src.cols / 2) * (img_src.cols / 2));
    double dist = 0.0f;
    double coefficient = 0.0f;

    double sin_fi = 0.0f;
    for (int i = 0; i < img_src.rows; i++)
    {
        for (int j = 0; j < img_src.cols; j++)
        {
            intensity = img_src.at<Vec3b>(i, j);
            if ((i - img_src.rows / 2.0f) * (i - img_src.rows / 2.0f) / (a * a) +
                    (j - img_src.cols / 2.0f) * (j - img_src.cols / 2.0f) / (b * b) > 1)
            {
                dist = sqrt((i - img_src.rows / 2.0f) * (i - img_src.rows / 2.0f) +
                            (j - img_src.cols / 2.0f) * (j - img_src.cols / 2.0f));
                sin_fi = (img_src.rows / 2.0f - i) / dist;
                radius_ellipse = (a * b) / sqrt(a * a * (1 - sin_fi * sin_fi) + b * b * sin_fi * sin_fi);
                coefficient = 1 - ((dist - radius_ellipse) / (max_radius - radius_ellipse));

                intensity_new.val[0] = (uchar)(intensity.val[0] * coefficient);
                intensity_new.val[1] = (uchar)(intensity.val[1] * coefficient);
                intensity_new.val[2] = (uchar)(intensity.val[2] * coefficient);
                img_dst.at<Vec3b>(i, j) = intensity_new;
            }
            else
            {
                img_dst.at<Vec3b>(i, j) = intensity;
            }
        }
    }
    img_dst.convertTo(dst, img_src.type());
    return 0;
}
