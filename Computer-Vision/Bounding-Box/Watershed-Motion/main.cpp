//////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////// Code by Arpita S Tugave  
///////////////////////// Detecting object and bounds it with a box
///////////////////////// Code is run on Visual Studio 13 with Cuda 7.5 on windows platform
///////////////////////// No arguments passed to the main function
///////////////////////// Uses combination of three methods, refer to readme.html or readme.md
//////////////////////////////////////////////////////////////////////////////////////////////

#include "libraries.hpp"
#include "Process.h"

using namespace std;
using namespace cv;


//  Main Function
int main(int argc, char** argv)
{
	/* input your file and video name, can pass it as argument */
	ifstream myfile("video3.txt");
	string filename = "video3.mp4";

	/* initializations */
	VideoCapture capture(filename);
	string line;
	// center(x,y) , height(h), width(w) values of the bounding box
	// if center ofbounding box is detected as (0,0) then no 
	// bounding box is displayed
	size_t x = 0, w = 10, y = 0, h = 10;
	// Take images and convert them to gray
	// we consider curent, previous and next frames to even 
	// consider motion parameters.
	Mat prev_frame, current_frame, next_frame, frame, croppedImage, read_frame;
	capture >> read_frame;

	if (getline(myfile, line)){
		std::istringstream iss(line);
		iss >> x;
		iss >> y;
	}
	else x = 0, y = 0;

	//resize(read_frame, current_frame, Size(600, 450), 0, 0, INTER_CUBIC);
	current_frame = read_frame;
	capture >> read_frame;

	if (getline(myfile, line)){
		std::istringstream iss(line);
		iss >> x;
		iss >> y;
	}
	else x = 0, y = 0;

	//resize(read_frame, next_frame, Size(600, 450), 0, 0, INTER_CUBIC);
	next_frame = read_frame;
	cvtColor(current_frame, current_frame, CV_RGB2GRAY);
	cvtColor(next_frame, next_frame, CV_RGB2GRAY);

	/* read the video frames*/
	if (!capture.isOpened())
		throw "Error when reading video";

	/* window for display */
	namedWindow("display", 1);

	/* process the video frames */
	for (;;)
	{

		// Take a new image
		prev_frame = current_frame;
		current_frame = next_frame;
		capture >> read_frame;
		//resize(read_frame, frame, Size(600,450), 0, 0, INTER_CUBIC);
		frame = read_frame;
		next_frame = frame;
		if (next_frame.empty())
			break;
		cvtColor(next_frame, next_frame, CV_RGB2GRAY);

		if (getline(myfile, line)){
			std::istringstream iss(line);
			iss >> x;
			iss >> y;
		}
		else x = 0, y = 0;
		//cout << "x: " << x << " y: " << y << endl;
		//x = x * 600 / read_frame.cols;
		//y = y * 450 / read_frame.rows;

		bool watershed_flag = true;
		bool motion_detection_flag = true;

		// object of class Process
		// Process class contains menthods for object 
		// recongition and draws bounding box
		Process p(current_frame, prev_frame, next_frame);

		// first priority detection method : watershed, find the object 
		// apply feature extraction and detection on top of this
		p.watershedAlgorithm(frame, x, y, watershed_flag , croppedImage);

		// second priority detection method : motion detection
		if (watershed_flag == 0) {
			p.processMotion(motion_detection_flag , x , y);
		}
		if (watershed_flag == 0 && motion_detection_flag == 0) {
			if (x != 0 && y != 0)
				rectangle(frame, cvPoint(x - w / 2, y - h / 2), cvPoint(x + w / 2, y + h / 2 / 2), CV_RGB(0, 0, 0), 1, 8);
			imshow("display", frame);
			waitKey(20); // waits to display frame
		}

		cout << watershed_flag << ", " << motion_detection_flag << endl;
	}
	// key press to close window
	waitKey(0);
	myfile.close();

	return 0;
}
