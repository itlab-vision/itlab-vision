#include "photoeffects.hpp"

using namespace cv;

int antique(InputArray src, InputArray texture, OutputArray dst)
{
    Mat textureImg = texture.getMat();
    resize(texture,textureImg, src.size(),0,0, INTER_LINEAR);
   	Mat m_sepiaKernel = (Mat_<float>(3,3)<<0.272f, 0.534f, 0.131f,  
                                            0.349f, 0.686f, 0.168f, 
                                            0.393f, 0.769f, 0.189f);
    Mat newSrc = src.getMat();
    transform(newSrc,newSrc,m_sepiaKernel);
    float alpha = 0.7f;
    float beta = 1.0f-alpha;
    addWeighted(textureImg, alpha , newSrc, beta, 0.0, dst);
    return 0;
}
