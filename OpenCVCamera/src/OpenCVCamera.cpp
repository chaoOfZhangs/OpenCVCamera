//============================================================================
// Name        : OpenCVCamera.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <ctime>
#include <stdio.h>

#include "opencv2/opencv.hpp"
#include "opencv2/imgproc/imgproc.hpp"

int main(int argc, char** argv) {
	int camera = 0;
	std::string ext (".png");
	std::string path ("image_");

	const char* instructions =
			"Usage: ./OpenCVCamera <camera number> [<path>] [<file extension>] \n"
				"\tPress space bar to save frame (saves in .png by default).\n"
				"\tPress esc to quit.\n\n"
				"\tExample Usage: \n"
				"\t$./OpenCVCamera 0 .png /usr/home/\n\n"
				"\tValid extensions: .png, .tiff, .jpeg.\n";

	switch(argc) {
	case 0:;
	/* no break use branch below*/
	case 1:
		printf("%s\n",instructions);
		return 0;
		break;
	case 4: ext = argv[3];
	/* no break, use all branches below*/
	case 3: path = argv[2] + path;
	/* no break, use all branches below*/
	case 2: camera = atoi(argv[1]);
	/* no break, use branch below */
	default: break;
	}

	CvCapture* cap = cvCaptureFromCAM(camera);

	if (!cap) {
		printf("Error: Could not create camera capture.");
		return -1;
	}

	cv::Mat frame = cvQueryFrame(cap);
	bool exit = false;

	while(!exit) {
		if (frame.empty()) {
			printf("Frame is NULL.");
			break;
		}

		cv::imshow("Raw Image", frame);

		int key = cvWaitKey(33);

		switch (key) {
		case 27: {
			exit = true;
			break;
		}
		case 32: {
			char strSec[40];
			sprintf(strSec, "%li", time(NULL));

			std::string file;
			file.append(path).append(strSec).append(ext);

			cv::imwrite(file, frame);
			std::cout << "Created image: " + file + "\n" << std::endl;

			break;
		}
		default:
			break;
		}

		frame = cvQueryFrame(cap);
	}

	cvReleaseCapture(&cap);
	return 0;
}
