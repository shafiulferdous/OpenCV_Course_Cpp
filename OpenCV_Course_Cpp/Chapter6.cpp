#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

//////////////Color Detection////////

void main() {
	string path = "Resources/lambo.png";
	
	Mat img = imread(path);
	Mat img_HSV, img_mask;

	//these values are difficult to find and track so we will be tracking them using the function createTrackbar
	int hue_min = 0, hue_max = 29, sat_min = 88, sat_max = 68, val_min = 127, val_max = 134;//we have to initialize them
	
	//To detect colors, it is better if we covert the image into HSV
	cvtColor(img, img_HSV, COLOR_BGR2HSV);

	//creating new window
	namedWindow("Trackbars", (640, 200));//syntax: namedWindow("Window Name", size);

	//creating the track bars to track hue, sat, and val. For Hue max = 180, sat max = 255, val max = 255
	//using this to find values for the lower and upper in the function inRange
	createTrackbar("Hue Min", "Trackbars", &hue_min, 179);//syntax createTrackbar("Track name", "Window name", address of parameter, max val of parameter)
	createTrackbar("Hue Max", "Trackbars", &hue_max, 179);
	createTrackbar("Sat Min", "Trackbars", &sat_min, 255);
	createTrackbar("Sat Max", "Trackbars", &sat_min, 255);
	createTrackbar("Val Min", "Trackbars", &val_min, 255);
	createTrackbar("Val Max", "Trackbars", &val_min, 255);

	while (true) {//whenever we use the trackbar, we will have to use the while loop
		
		Scalar lower(hue_min, sat_min, val_min);//these values will be tracked in the trackbar
		Scalar upper(hue_max, sat_max, val_max);
		
		//Now we will use the in range function to collect the desired color
		inRange(img_HSV, lower, upper, img_mask);//syntax: inRange(image, lower, upper, masked_image);

		imshow("Image", img);
		imshow("Image HSV", img_HSV);
		imshow("Image Mask", img_mask);

		waitKey(1);		
	}

	

}