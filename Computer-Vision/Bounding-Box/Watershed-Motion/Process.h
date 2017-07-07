#pragma once

#include "libraries.hpp"

using namespace std;
using namespace cv;

class Process
{
private:
	Mat current_frame, prev_frame, next_frame, bw, imgLaplacian, sharp;

	// d1 and d2 for calculating the differences
	// result, the result of and operation, calculated on d1 and d2
	// number_of_changes, the amount of changes in the result matrix.
	// color, the color for drawing the rectangle when something has changed.
	Mat d1, d2, motion, result;
	int number_of_changes, number_of_sequence = 0;
	Scalar mean_;

	// If more than 'there_is_motion' pixels are changed, we say there is motion
	// and store an image on disk
	int there_is_motion = 5;

	// Maximum deviation of the image, the higher the value, the more motion is allowed
	int max_deviation = 20;

	// Erode kernel
	Mat kernel_ero = getStructuringElement(MORPH_RECT, Size(2, 2));

	// Detect motion in window
	int x_start, x_stop, y_start, y_stop;


public:
	Process(Mat current_frame,Mat prev_frame,Mat next_frame) :
		current_frame(current_frame), prev_frame(prev_frame), next_frame(next_frame) {
	};
	void processMotion(bool &motion_detection_flag, int x, int y);
	void watershedAlgorithm(Mat frame, int x, int y, bool &watershed_flag, Mat &croppedImage);
};

