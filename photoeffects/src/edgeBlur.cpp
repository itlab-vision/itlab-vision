#include "photoeffects.hpp"

using namespace cv;

int edgeBlur(InputArray src, OutputArray dst, int indentTop, int indentRight, float round)
{
	Mat image = src.getMat(), outputImage(image.size(), CV_8UC3);

	outputImage.convertTo(dst, CV_8UC3);
	return 0;
}
