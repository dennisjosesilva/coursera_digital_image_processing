#include "block_average_calculator.h"


block_average_calculator::block_average_calculator()
{
}


block_average_calculator::~block_average_calculator()
{
}


uchar block_average_calculator::calculate_avarage(const cv::Mat& src, const cv::Point2i current_index, int block_size)
{
	auto sum = 0;
	auto pixels_used = 0;
	auto factor = block_size * 2;

	for (auto i = 0; i < block_size; ++i)
	{
		for (auto j = 0; j < block_size; ++j)
		{
			auto processing_pixel = cv::Point2i(current_index.x + i, current_index.y + i);
			if (processing_pixel.x < src.cols && processing_pixel.y < src.rows)
			{
				sum += src.at<uchar>(processing_pixel);
				++pixels_used;
			}
		}
	}

	return (uchar)(sum / pixels_used);
}

void block_average_calculator::setup_pixels_block(const cv::Mat& src, cv::Mat& output, uchar average, const cv::Point2i current_index, int block_size)
{
	for (auto i = 0; i < block_size; ++i)
	{
		for (auto j = 0; j < block_size; ++j)
		{
			auto processing_pixel = cv::Point2i(current_index.x + i, current_index.y + i);
			if (processing_pixel.x < src.cols && processing_pixel.y < src.rows)
				output.at<uchar>(processing_pixel) = average;
		}
	}
}

cv::Mat block_average_calculator::process_a_channel(cv::Mat& channel, int block_size)
{
	cv::Mat output;
	output.create(channel.size(), channel.type());

	for (auto i = 0; i < channel.rows; i += block_size)
	{
		for (auto j = 0; j < channel.cols; j += block_size)
		{
			auto current_pixel = cv::Point2i(i, j);
			auto avg = calculate_avarage(channel, current_pixel, block_size);
			setup_pixels_block(channel, output, avg, current_pixel, block_size);
		}
	}

	return output;
}

cv::Mat block_average_calculator::process(const cv::Mat& image, int block_size)
{
	cv::Mat output;
	output.create(image.size(), image.type());

	cv::vector<cv::Mat> channels;
	cv::vector<cv::Mat> out_channels;
	cv::split(image, channels);



	for (auto channel : channels)
	{
		auto p_channel = process_a_channel(channel, block_size);
		out_channels.push_back(p_channel);
	}

	cv::merge(out_channels, output);
	return output;
}