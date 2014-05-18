#include "photoeffects.hpp"
#include <iostream>
using namespace std;
using namespace cv;

int antique(InputArray src, OutputArray dst, InputArray texture, float alpha)
{
    CV_Assert((src.type() == CV_8UC3) || (src.type() == CV_32FC3));
    CV_Assert((texture.type() == CV_8UC3) || (texture.type() == CV_32FC3));
    CV_Assert((alpha > 0.0f) && (alpha < 1.0f));
    Mat textureImg = texture.getMat();
    Mat srcImg = src.getMat();
    CV_Assert((textureImg.rows >= srcImg.rows) && (textureImg.cols >= srcImg.cols));
    resize(textureImg, textureImg, srcImg.size());
    Mat m_sepiaKernel = (Mat_<float>(3,3)<<0.272f, 0.534f, 0.131f,
                                           0.349f, 0.686f, 0.168f,
                                           0.393f, 0.769f, 0.189f);
    transform(srcImg,srcImg,m_sepiaKernel);
    float beta = 1.0f-alpha;
    dst.getMat() = srcImg*alpha + textureImg*beta;
    return 0;
}
