#include "colour_reducer.h"


colour_reducer::colour_reducer()
{
}


colour_reducer::~colour_reducer()
{
}


cv::Mat colour_reducer::reduce_colour(const cv::Mat& image, uchar intensity)
{
	cv::Mat result;
	result.create(image.size(), image.type());
	auto output_image_ptr = result.ptr<uchar>();

	auto input_image_ptr = image.ptr<uchar>();
	auto end_image = image.cols * image.rows * image.channels();
	auto ranges = calculate_range(intensity);

	for (auto i = 0; i < end_image; ++i)
	{
		auto value = input_image_ptr[i];
		auto reduced_intensity = find_reduced_pixel_value(ranges, value);
		output_image_ptr[i] = reduced_intensity;
	}

	return result;
}


uchar colour_reducer::find_reduced_pixel_value(const std::vector<range>& ranges, uchar value)
{
	for (auto& range : ranges)
	{
		if (range.is_int_the_range(value))
			return range.get_reduced_value(value);
	}

	return 0;
}

std::vector<range> colour_reducer::calculate_range(uchar intensity)
{
	auto total_ranges = intensity - 1;
	std::vector<range> ranges(total_ranges);
	auto interval = TOTAL_PIXEL_VALUE / total_ranges;

	for (auto i = 1; i <= total_ranges; ++i)
	{
		range _range;
		_range.begin = (i - 1) * interval;
		_range.end = i * interval;
		ranges[i - 1] = _range;
	}

	return ranges;
}

uchar range::get_reduced_value(uchar value) const
{
	auto mean = (begin + end) / 2;
	if (value < mean)
		return begin;
	else
		return end;
}

bool range::is_int_the_range(uchar value) const 
{
	return begin <= value && value <= end;
}