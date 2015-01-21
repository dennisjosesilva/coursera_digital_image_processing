#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>

#ifndef ROTATION_H_INCLUDED
#define ROTATION_H_INCLUDED

class rotation
{
public:
	cv::Mat rotate(const cv::Mat& image, double degree);

	rotation();
	~rotation();
};


#endif