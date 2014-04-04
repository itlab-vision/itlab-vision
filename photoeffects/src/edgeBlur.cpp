#include "photoeffects.hpp"

using namespace cv;

int edgeBlur(InputArray src, OutputArray dst, int halfWidth, int halfHeight)
{
	Mat image = src.getMat(), outputImage(image.size(), CV_8UC3);

	outputImage.convertTo(dst, CV_8UC3);
	return 0;
}
