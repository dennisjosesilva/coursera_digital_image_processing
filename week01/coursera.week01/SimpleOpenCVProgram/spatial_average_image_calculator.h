#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>

#include <vector>

#ifndef SPARTIAL_AVERAGE_IMAGE_CALCULATOR_H_INCLUDED
#define SPARTIAL_AVERAGE_IMAGE_CALCULATOR_H_INCLUDED

class spatial_average_image_calculator
{
private:


public:
	spatial_average_image_calculator();
	~spatial_average_image_calculator();

	cv::Mat process(const cv::Mat& image, int mask_value);

private:
	std::vector<cv::Point2i> mask_indices(const cv::Mat& image, int mask_value, cv::Point2i current_indice);
	uchar calculate_average(const cv::Mat& image, const std::vector<cv::Point2i>& indices);

	bool is_gray_scale_image(const cv::Mat& image);

	cv::Mat process_gray_scale_image(const cv::Mat& image, int mask_value);
	cv::Mat process_coloured_scale_image(const cv::Mat& image, int mask_value);
};

#endif