#include <opencv2\core\core.hpp>
#include <vector>

#ifndef COLOUR_REDUCER_H_INCLUDED
#define COLOUR_REDUCER_H_INCLUDED


struct range 
{
	uchar begin;
	uchar end;
	
	uchar get_reduced_value(uchar value) const;
	bool is_int_the_range(uchar value) const;
};

class colour_reducer
{
public:
	colour_reducer();
	~colour_reducer();

	cv::Mat reduce_colour(const cv::Mat& image, uchar intensity);

private:
	std::vector<range> calculate_range(uchar intensity);
	uchar find_reduced_pixel_value(const std::vector<range>& ranges, uchar value);

	const uchar TOTAL_PIXEL_VALUE = 255;
};

#endif