#include "photoeffects.hpp"

using namespace cv;

int vignette(InputArray src, OutputArray dst, Size rect)
{
    if (src.type() != CV_8UC3 || rect.height == 0 || rect.width == 0)
    {
        return 1;
    }
    Mat img_src(src.size(), CV_8UC3);
    img_src = src.getMat();
    Mat img_dst(img_src.size(), CV_8UC3);
    Vec3b intensity, intensity_new;
    int center_row = img_src.rows / 2;
    int center_col = img_src.cols / 2;
    float a_2 = (rect.height / 2.0f) * (rect.height / 2.0f);
    float b_2 = (rect.width / 2.0f) * (rect.width / 2.0f);
    float ab = (rect.height / 2.0f) * (rect.width / 2.0f);
    float radius_ellipse = 0.0f;
    float max_radius = sqrt((img_src.rows / 2) * (img_src.rows / 2) + (img_src.cols / 2) * (img_src.cols / 2));
    float dist = 0.0f;
    float sin_fi = 0.0f;
    float coefficient = 0.0f;

    for (int i = 0; i < img_src.rows; i++)
    {
        for (int j = 0; j < img_src.cols; j++)
        {
            intensity = img_src.at<Vec3b>(i, j);
            intensity_new = intensity;
            if ((i - center_row) * (i - center_row) / a_2 +
                    (j - center_col) * (j - center_col) / b_2 > 1)
            {
                dist = sqrtf((i - center_row) * (i - center_row) + (j - center_col) * (j - center_col));
                sin_fi = (i - center_row) / dist;
                radius_ellipse = ab / sqrt(a_2 * (1 - sin_fi * sin_fi) + b_2 * sin_fi * sin_fi);
                coefficient = 1.0f - ((dist - radius_ellipse) / (max_radius - radius_ellipse));

                intensity_new.val[0] = (uchar)(intensity.val[0] * coefficient);
                intensity_new.val[1] = (uchar)(intensity.val[1] * coefficient);
                intensity_new.val[2] = (uchar)(intensity.val[2] * coefficient);
            }
            img_dst.at<Vec3b>(i, j) = intensity_new;
        }
    }
    img_dst.convertTo(dst, img_src.type());
    return 0;
}
