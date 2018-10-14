#include <cstdlib>
#include <iostream>
#include <vector>
#include <cmath>
#include "GPIOlib.h"

#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>

#define PI 3.1415926
#define DELTA 500

//Uncomment this line at run-time to skip GUI rendering
#define _DEBUG

using namespace cv;
using namespace std;
using namespace GPIO;

const string CAM_PATH = "/devideo0";
const string MAIN_WINDOW_NAME = "Processed Image";
const string CANNY_WINDOW_NAME = "Canny";

const int CANNY_LOWER_BOUND = 50;
const int CANNY_UPPER_BOUND = 250;
const int HOUGH_THRESHOLD = 150;

const int REC_WIDTH = 500;
const int REC_HEIGHT = 500;

int main()

{
                init();
	VideoCapture capture(CAM_PATH);
	//If this fails, try to open as a video camera, through the use of an integer param
	if (!capture.isOpened())
	{
		capture.open(atoi(CAM_PATH.c_str()));
	}


	//init初始化
	

	double dWidth = capture.get(CV_CAP_PROP_FRAME_WIDTH);			//the width of frames of the video
	double dHeight = capture.get(CV_CAP_PROP_FRAME_HEIGHT);		//the height of frames of the video
	//采集摄像头
	cout << "摄像头 ";
	cout << dWidth + ' ' + dHeight;

	Mat image;
	Mat grayiamge;
	Mat result;
	while (true)
	{
		capture >> image;
		if (image.empty())
			break;


		cvtColor(image,grayiamge , CV_BGR2GRAY);
		result = grayiamge.clone();
		threshold(grayiamge, result, 127, 255, CV_THRESH_BINARY);//0 black  1  white
		int width = result.rows;
		int height = result.cols;
		int left = 0;
		int right = 0;
		for (int i = 0; i < width / 2; i++){
			for (int j = 0; j < height; j++){
				if (result.at<unsigned char>(i, j) == 255)
					left++;

			}
		}

		for (int i = width / 2; i < width ; i++){
			for (int j = 0; j < height; j++){
				if (result.at<unsigned char>(i, j) == 255)
					right++;

			}
		}

		

		if (left - right>DELTA){
			turnTo(-10);
			delay(100);
			turnTo(0);
		}
		else if (right - left > DELTA){
			turnTo(10);
			delay(100);
			turnTo(0);
		}

	}
	return 0;
}
