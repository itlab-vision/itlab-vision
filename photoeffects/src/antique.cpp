#include "photoeffects.hpp"

using namespace cv;

int antique(InputArray src, InputArray texture, OutputArray dst)
{
    resize(texture, texture, src.size());
    merge(src, dst);
    merge(texture, dst);  
    return 0;
}
