#include "spatial_average_image_calculator.h"
#include <iostream>

spatial_average_image_calculator::spatial_average_image_calculator()
{
}


spatial_average_image_calculator::~spatial_average_image_calculator()
{
}


std::vector<cv::Point2i> spatial_average_image_calculator::mask_indices(const cv::Mat& image, int mask_value, cv::Point2i current_index)
{
	std::vector<cv::Point2i> indices;

	auto pixels_to_move = mask_value / 2;
	cv::Point2i it(current_index);
	
	for (auto i = 0; i <= pixels_to_move; ++i)
	{
		if (it.x + i < image.cols && it.y + i < image.rows)
			indices.push_back(cv::Point2i(it.x + i, it.y + i));

		if (it.x - i > 0 && it.y - i > 0)
			indices.push_back(cv::Point2i(it.x - i, it.y - i));
	}

	return indices;
}

uchar spatial_average_image_calculator::calculate_average(const cv::Mat& image, const std::vector<cv::Point2i>& indices)
{
	auto num_of_points = indices.size();
	int pixels_sum = 0;

	for (auto i : indices)
		pixels_sum += image.at<uchar>(i);

	return pixels_sum / num_of_points;
}

bool spatial_average_image_calculator::is_gray_scale_image(const cv::Mat& image)
{
	return image.channels() == 1;
}

cv::Mat spatial_average_image_calculator::process(const cv::Mat& image, int mask_value)
{
	if (is_gray_scale_image(image))
		return process_gray_scale_image(image, mask_value);
	else
		return process_coloured_scale_image(image, mask_value);
}

cv::Mat spatial_average_image_calculator::process_gray_scale_image(const cv::Mat& image, int mask_value)
{
	cv::Mat output;
	output.create(image.size(), image.type());	

	for (auto i = 0; i < image.rows; ++i)
	{
		for (auto j = 0; j < image.cols; ++j)
		{
			auto current_index = cv::Point2i(i, j);
			auto current_indices = mask_indices(image, mask_value, current_index);
			output.at<uchar>(current_index) = calculate_average(image, current_indices);
		}
	}

	return output;
}

cv::Mat spatial_average_image_calculator::process_coloured_scale_image(const cv::Mat& image, int mask_value)
{
	cv::Mat output;
	output.create(image.size(), image.type());

	cv::vector<cv::Mat> channels;
	cv::split(image, channels);


	for (auto c = 0; c < channels.size(); ++c)
	{
		for (auto i = 0; i < channels[c].rows; ++i)
		{
			for (auto j = 0; j < channels[c].cols; ++j)
			{
				auto current_index = cv::Point2i(i, j);
				auto current_indices = mask_indices(channels[c], mask_value, current_index);
				channels[c].at<uchar>(current_index) = calculate_average(channels[c], current_indices);
			}
		}
	}

	
	cv::merge(channels, output);	
	return output;
}