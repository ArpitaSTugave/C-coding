
#include "opencv.hpp"
#include <iostream>
#include <stdio.h>
#include <cuda.h>
#include <cuda_runtime.h>

using namespace std;
using namespace cv;

extern "C" void gray_parallel(unsigned char* h_in, unsigned char* h_out, int elems, int rows, int cols);

// My serial implementation, works fine
Mat gray_serial(Mat img){
	int rows = img.rows;
	int cols = img.cols;
	Mat gray(rows, cols, CV_8UC1);
	for (int r = 0; r<rows; r++){
		for (int c = 0; c<cols; c++){
			Vec3b bgr = img.at<Vec3b>(r, c);
			double gray_val = 0.144*bgr.val[0] + 0.587*bgr.val[1] + 0.299*bgr.val[2];
			gray.at<unsigned char>(r, c) = (unsigned char)gray_val;
		}
	}
	return gray;
}

//      Main Function

int main(int argc, char** argv)
{
	Mat image;
	image = imread("imageo.jpg");	// Read the file, it is simple 64x64 image. 
	//resize(image, image, Size(64, 64), 0, 0, INTER_CUBIC);

	//           First trying serial code      
	int64 t1 = cv::getTickCount();
	Mat gray(image.rows,image.cols,CV_8UC1);
	for (int i = 0; i < 1000; i++)
		gray = gray_serial(image);
	int64 t2 = cv::getTickCount();
	cout << "serial code" << double(t2 - t1) /1000<< " " << endl;


	//         Now trying GPU code
	int64 t3 = cv::getTickCount();
	const int rows = image.rows;
	const int cols = image.cols;
	int elems = rows*cols * 3;
	unsigned char *h_in = image.data;
	unsigned char *h_out = new unsigned char[rows*cols];
	for (int i = 0; i < 1000; i++)
		gray_parallel(h_in, h_out, elems, rows, cols);

	Mat gray2 = Mat(rows, cols, CV_8UC1, h_out);
	int64 t4 = cv::getTickCount();
	cout << "parallel code" << double(t4 - t3) / 1000 << " " << sizeof(unsigned char) << endl;
	Mat diff(rows, cols, CV_8UC1);
	for (int i = 0; i < gray2.rows; i++)
		for (int j = 0; j < gray2.cols; j++)
			diff.at<uchar>(i, j) = gray.at<uchar>(i, j) - gray2.at<uchar>(i, j);
	imshow("difference", diff);
	waitKey(0);
	// Finally display result of GPU code (CPU code works fine, but not GPU code)
	imshow("image.jpg", gray2);
	waitKey(0);
	return 0;
}