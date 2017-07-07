////////////////////////////////////////////////////
//////////////////////////
//////////////////////////
/////////////////////////
///////////////////////////
//////////////////////////
/////////////////////////////////////////////////////

#include "opencv.hpp"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <cuda.h>
#include <cuda_runtime.h>
#include <time.h>
#include <sstream>
#include <sys/types.h>
#include <sys/stat.h>

using namespace std;
using namespace cv;


//  Main Function
int main(int argc, char** argv)
{

	ifstream myfile("video1.txt"); //input your file and video name
	string filename = "video1.mp4";

	/* initializations */
	VideoCapture capture(filename);
	Mat frame, imgLaplacian, sharp, imgResult, bw, ccLabels;
	string line;
	size_t x = 0, w = 40, y = 0, h = 40; // center(x,y) , height(h), width(w) values of the bounding box
	int r = 0, b = 0, g = 0; // color of bounding box
	int count = 0; //count number of frames

	/* read the video frames*/
	if (!capture.isOpened())
		throw "Error when reading video";

	namedWindow("display", 1);
	for (;;)
	{
		capture >> frame;
		if (frame.empty())
			break;

		
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
		

		if (getline(myfile, line)){
			std::istringstream iss(line);
			iss >> x;
			iss >> y;
		}
		else x = 0, y = 0; //if center is found to be 0, means object not detected
		count += 1;

		Mat dist = Mat(frame.rows, frame.cols, CV_8UC1, cv::Scalar(0));
		dist.at<uchar>(y, x) = 255;
		// Dilate a bit the dist image
		Mat kernel1 = Mat::ones(3, 3, CV_8UC1);
		dilate(dist, dist, kernel1);

		// Perform the watershed algorithm
		//watershed(frame, [x,y]);
		cout << "x: " << x << " ,y: " << y << " number of: " << count << '\n';

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
		findContours(dst, contours, CV_RETR_LIST, CV_CHAIN_APPROX_NONE);

		for (size_t i = 0; i<contours.size(); i++) {
			for (size_t j = 0; j < contours[i].size(); j++) {
				cv::Point p = contours[i][j];
				points.push_back(p);
			}
		}
		// And process the points or contours to pick up specified object.

		// for example: draws rectangle on original image.
		if (points.size() > 0){
			cv::Rect brect = cv::boundingRect(cv::Mat(points).reshape(2));
			cv::rectangle(frame, brect.tl(), brect.br(), cv::Scalar(100, 100, 200), 2, CV_AA);
		}

		//if (x != 0 && y != 0)
			//rectangle(drawing, cvPoint(x - w / 2, y - h / 2), cvPoint(x + w / 2, y + h / 2 / 2), CV_RGB(r, g, b), 1, 8);
		imshow("display", frame);
		waitKey(20); // waits to display frame
	}
	waitKey(0); // key press to close window
	myfile.close();
	return 0;
}
