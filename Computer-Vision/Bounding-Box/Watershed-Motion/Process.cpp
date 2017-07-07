#include "Process.h"
#include "libraries.hpp"

using namespace std;
using namespace cv;

void Process::processMotion(bool &motion_detection_flag, int x, int y){

	int min_x = current_frame.cols, max_x = 0;
	int min_y = current_frame.rows, max_y = 0;

	// Calc differences between the images and do AND-operation
	// threshold image, low differences are ignored (ex. contrast change due to sunlight)
	absdiff(prev_frame, next_frame, d1);
	absdiff(next_frame, current_frame, d2);
	bitwise_and(d1, d2, motion);
	threshold(motion, motion, 35, 255, CV_THRESH_BINARY);
	erode(motion, motion, kernel_ero);

	// Detect motion in window
	int x_start = 10, x_stop = current_frame.cols - 11;
	int y_start = 10, y_stop = current_frame.rows - 11;
	result = current_frame;

	// calculate the standard deviation
	Scalar mean, stddev;
	meanStdDev(motion, mean, stddev);
	// if not to much changes then the motion is real (neglect agressive snow, temporary sunlight)
	if (stddev[0] < max_deviation)
	{
		int number_of_changes = 0;
		// loop over image and detect changes
		for (int j = y_start; j < y_stop; j += 2){ // height
			for (int i = x_start; i < x_stop; i += 2){ // width
				// check if at pixel (j,i) intensity is equal to 255
				// this means that the pixel is different in the sequence
				// of images (prev_frame, current_frame, next_frame)
				if (static_cast<int>(motion.at<uchar>(j, i)) == 255)
				{
					number_of_changes++;
					if (min_x>i) min_x = i;
					if (max_x<i) max_x = i;
					if (min_y>j) min_y = j;
					if (max_y<j) max_y = j;
				}
			}
		}
		if (number_of_changes){
			//check if not out of bounds
			if (min_x - 10 > 0) min_x -= 10;
			if (min_y - 10 > 0) min_y -= 10;
			if (max_x + 10 < result.cols - 1) max_x += 10;
			if (max_y + 10 < result.rows - 1) max_y += 10;
		}

		// draw rectangle round the changed pixel
		// if the point is within the bounding rectangle
		// if area of the rectangle is less than 10% if the image
		if (x!=0 && y!=0 && min_x < x && max_x > x && min_y < y && max_y > y &&
			abs((max_x-min_x)*(max_y-min_y)) < ((current_frame.cols*current_frame.rows)/10)){
			Point x(min_x, min_y);
			Point y(max_x, max_y);
			Rect rect(x, y);
			rectangle(current_frame, rect, Scalar(0, 0, 0), 1);
			imshow("display", current_frame);
			// waits to display frame
			waitKey(20); // waits to display frame
		}
		else
			motion_detection_flag = false;
	}
	else motion_detection_flag = false;
}

void Process::watershedAlgorithm(Mat frame, int x, int y, bool &watershed_flag, Mat &croppedImage){
	
	// Create a kernel that we will use for accuting/sharpening our image
	Mat kernel = (Mat_<float>(3, 3) <<
		1, 1, 1,
		1, -8, 1,
		1, 1, 1); // an approximation of second derivative, a quite strong kernel
	// do the laplacian filtering as it is
	// well, we need to convert everything in something more deeper then CV_8U
	// because the kernel has some negative values,
	// and we can expect in general to have a Laplacian image with negative values
	// BUT a 8bits unsigned int (the one we are working with) can contain values from 0 to 255
	// so the possible negative number will be truncated
	sharp = frame; // copy source image to another temporary one
	filter2D(sharp, imgLaplacian, CV_32F, kernel);
	frame.convertTo(sharp, CV_32F);
	Mat imgResult = sharp - imgLaplacian;
	// convert back to 8bits gray scale
	imgResult.convertTo(imgResult, CV_8UC3);

	cvtColor(imgResult, bw, CV_BGR2GRAY);
	threshold(bw, bw, 40, 255, CV_THRESH_BINARY | CV_THRESH_OTSU);


	Mat dist = Mat(frame.rows, frame.cols, CV_8UC1, cv::Scalar(0));
	dist.at<uchar>(y, x) = 255;
	// Dilate a bit the dist image
	Mat kernel1 = Mat::ones(3, 3, CV_8UC1);
	dilate(dist, dist, kernel1);

	// Create the CV_8U version of the distance image
	// It is needed for findContours()
	Mat dist_8u;
	dist.convertTo(dist_8u, CV_8U);
	// Find total markers
	vector<vector<Point> > contours;
	findContours(dist_8u, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
	// Create the marker image for the watershed algorithm
	Mat markers = Mat::zeros(dist.size(), CV_32SC1);
	// Draw the foreground markers
	for (size_t i = 0; i < contours.size(); i++)
		drawContours(markers, contours, static_cast<int>(i), Scalar::all(static_cast<int>(i)+1), -1);
	// Draw the background marker
	circle(markers, Point(5, 5), 3, CV_RGB(255, 255, 255), -1);
	// Perform the watershed algorithm
	watershed(frame, markers);
	Mat mark = Mat::zeros(markers.size(), CV_8UC1);
	markers.convertTo(mark, CV_8UC1);
	bitwise_not(mark, mark);
	//    imshow("Markers_v2", mark); // uncomment this if you want to see how the mark
	// image looks like at that point
	// Generate random colors
	vector<Vec3b> colors;
	for (size_t i = 0; i < contours.size(); i++)
	{
		int b = theRNG().uniform(0, 255);
		int g = theRNG().uniform(0, 255);
		int r = theRNG().uniform(0, 255);
		colors.push_back(Vec3b((uchar)b, (uchar)g, (uchar)r));
	}
	// Create the result image
	Mat dst = Mat::zeros(markers.size(), CV_8UC3);
	// Fill labeled objects with random colors
	for (int i = 0; i < markers.rows; i++)
	{
		for (int j = 0; j < markers.cols; j++)
		{
			int index = markers.at<int>(i, j);
			if (index > 0 && index <= static_cast<int>(contours.size()))
				dst.at<Vec3b>(i, j) = colors[index - 1];
			else
				dst.at<Vec3b>(i, j) = Vec3b(0, 0, 0);
		}
	}

	std::vector<cv::Point> points;
	cvtColor(dst, dst, CV_RGB2GRAY);
	dst.convertTo(dst, CV_8UC1);
	Mat kernel2 = Mat::ones(11, 11, CV_8UC1);
	dilate(dst, dst, kernel2);
	findContours(dst, contours, CV_RETR_LIST, CV_CHAIN_APPROX_NONE);

	if (contours[0].size() < 100) {
		for (size_t i = 0; i < contours.size(); i++) {
			for (size_t j = 0; j < contours[i].size(); j++) {
				cv::Point p = contours[i][j];
				points.push_back(p);
			}
		}


	//cout << contours.size() << "," << contours[0].size() << " flag: " << watershed_flag << endl;

	// And process the points or contours to pick up specified object.
	// for example: draws rectangle on original image.
	if (points.size() > 0){
		Rect brect = cv::boundingRect(cv::Mat(points).reshape(2));
		rectangle(frame, brect.tl(), brect.br(), Scalar(0, 0, 0), 1);
		croppedImage = frame(brect);
	}

	imshow("display", frame);
	waitKey(20); // waits to display frame
	}
	else
		watershed_flag = false;
}


