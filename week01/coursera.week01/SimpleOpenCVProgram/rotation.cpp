#include "rotation.h"


rotation::rotation()
{
}


rotation::~rotation()
{
}

cv::Mat rotation::rotate(const cv::Mat& image, double degree)
{
	cv::Mat output;
	output.create(image.size(), image.type());

	cv::Point2f center(image.cols / 2.0f, image.rows / 2.0f);

	auto rotation_matrix = cv::getRotationMatrix2D(center, degree, 1.0);

	cv::warpAffine(image, output, rotation_matrix, image.size());

	return output;
}