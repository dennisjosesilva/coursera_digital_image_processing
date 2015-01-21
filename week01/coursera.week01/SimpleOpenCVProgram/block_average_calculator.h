#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>

#ifndef BLOCK_AVERAGE_CALCULATOR_H_INCLUDED
#define BLOCK_AVERAGE_CALCULATOR_H_INCLUDED

class block_average_calculator
{
public:
	block_average_calculator();
	~block_average_calculator();

	cv::Mat process(const cv::Mat& image, int block_size);

private:
	uchar calculate_avarage(const cv::Mat& src, const cv::Point2i current_index, int block_size);
	void setup_pixels_block(const cv::Mat& src, cv::Mat& output, uchar average, const cv::Point2i current_index, int block_size);

	cv::Mat process_a_channel(cv::Mat& channel, int block_size);
};

#endif