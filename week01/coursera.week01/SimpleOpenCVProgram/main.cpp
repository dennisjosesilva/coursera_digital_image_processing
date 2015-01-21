#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <iostream>
#include <string>

#include "colour_reducer.h"
#include "spatial_average_image_calculator.h"
#include "rotation.h"
#include "block_average_calculator.h"

void average_block_transform(int argc, char* argv[]);
void colour_reduce(int argc, char* argv[]);
void average_transform(int argc, char* argv[]);
void rotate(int argc, char* argv[]);


int main(int argc, char* argv[])
{	
	if (argc > 3)
	{
		std::string operation(argv[1]);

		if (operation == "-colour_reduce")
			colour_reduce(argc, argv);
		else if (operation == "-average_transformation")
			average_transform(argc, argv);
		else if (operation == "-rotation")
			rotate(argc, argv);
		else if (operation == "-average_transformation_block")
			average_block_transform(argc, argv);
	}
	else
	{
		std::cerr << "Error on input.";
		exit(1);
	}


	return 0;
}

void colour_reduce(int argc, char* argv[])
{
	colour_reducer colour_reduce;

	std::string image_file(argv[2]);
	std::string intensity_str(argv[3]);
	uchar intensity = (uchar)std::stoi(intensity_str);

	auto image = cv::imread(image_file);

	auto result = colour_reduce.reduce_colour(image, intensity);

	cv::namedWindow("result");
	cv::imshow("result", result);

	cv::waitKey();
}

void average_transform(int argc, char* argv[])
{
	spatial_average_image_calculator calculator;

	std::string image_file(argv[2]);
	std::string mask_value_str(argv[3]);
	uchar mask_value = (uchar)std::stoi(mask_value_str);

	auto image = cv::imread(image_file);

	auto result = calculator.process(image, mask_value);

	cv::namedWindow("result");
	cv::imshow("result", result);

	cv::waitKey();
}

void rotate(int argc, char* argv[])
{
	rotation rotation;

	std::string image_file(argv[2]);
	std::string block_size_str(argv[3]);
	double block_size = std::stoi(block_size_str);

	auto image = cv::imread(image_file);

	auto result = rotation.rotate(image, block_size);

	cv::namedWindow("result");
	cv::imshow("result", result);

	cv::waitKey();
}

void average_block_transform(int argc, char* argv[])
{
	block_average_calculator calculator;

	std::string image_file(argv[2]);
	std::string angle_str(argv[3]);
	double angle = std::stod(angle_str);

	auto image = cv::imread(image_file);

	auto result = calculator.process(image, angle);

	cv::namedWindow("result");
	cv::imshow("result", result);

	cv::waitKey();
}