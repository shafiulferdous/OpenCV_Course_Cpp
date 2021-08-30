#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <string.h>


using namespace std;
using namespace cv;

//////////////Project 1////////

Mat img;
vector<vector<int>> drawPoints;//vector of vector of ints structure - {{x, y, color_idx_1}, {x, y, color_idx_2}}
vector<vector<int>> myColors_hsv{			//vector of colors, which are vector of int for HSV
								{172, 137, 182, 179, 255, 255},//red hsv
								{29, 45, 201, 74, 255, 255} //green hsv
															};

vector<Scalar> myColors_scalar{				//when we detect the object, this is the color we will show, red and green
								{0, 0, 255},//red
								{0, 255, 0}//green
											};

void colorPicker() {//pick color - HSV values from the webcam
		
	VideoCapture cap(0);
	Mat img, img_hsv, img_mask;
	int hue_min = 0, sat_min = 0, val_min = 0;
	int hue_max = 179, sat_max = 255, val_max = 255;
	
	namedWindow("Trackbars", (640, 200));//640x200 window

	createTrackbar("Hue Min", "Trackbars", &hue_min, 179);
	createTrackbar("Hue Max", "Trackbars", &hue_max, 179);
	createTrackbar("Sat Min", "Trackbars", &sat_min, 255);
	createTrackbar("Sat Max", "Trackbars", &sat_min, 255);
	createTrackbar("Val Min", "Trackbars", &val_min, 255);
	createTrackbar("Val Max", "Trackbars", &val_min, 255);

	//hsv_min: 130, 123, 141
	//hsv_max: 179, 255, 255
	
	while (true) {
			
		cap.read(img);
		cvtColor(img, img_hsv, COLOR_BGR2HSV);

		Scalar lower(hue_min, sat_min, val_min);
		Scalar upper(hue_max, sat_max, val_max);
			
		inRange(img_hsv, lower, upper, img_mask);

		imshow("Webcam - original", img);
		imshow("Webcam - mask", img_mask);
		
		cout << "hsv_min: " << hue_min << ", " << sat_min << ", " << val_min << endl;
		cout << "hsv_max: " << hue_max << ", " << sat_max << ", " << val_max << endl;
		waitKey(2);
	}
}
 
Point getContours(Mat img_mask) {
	
	//first we need to blur, canny and dilate the image
	Mat img_gray, img_blur, img_canny, img_dil;
	//cvtColor(img_mask, img_gray, COLOR_HSV2);
	
	GaussianBlur(img_mask, img_blur, Size(3, 3), 3, 3);//blurring the image
	Canny(img_blur, img_canny, 5, 5);
	
	Mat Kernel = getStructuringElement(MORPH_RECT, Size(7, 7));
	dilate(img_canny, img_dil, Kernel);
		
	
	//now to find the contours and corresponding contour points
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;

	findContours(img_dil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

	vector<vector<Point>> contour_points(contours.size());
	vector<Rect> bounding_box(contours.size());
	Point drawPoint(0, 0);//point at which we will draw the lines

	for (int i = 0; i < contours.size(); i++) {//will run once for each contour, that is each color
		int area = contourArea(contours[i]);//need area for filtration
		cout << "Area is:"<<area << endl;
		
		if (area > 1000) {

			float perimeter = arcLength(contours[i], true);

			approxPolyDP(contours[i], contour_points[i], 0.02 * perimeter, true);

			drawContours(img, contour_points, i, Scalar(255, 0, 0), 2);//drawing the contour points

			bounding_box[i] = boundingRect(contour_points[i]);
			//rectangle(img_dil, bounding_box[i].tl(), bounding_box[i].br(), Scalar(0, 255, 0), 2);//draw the rect in the masked image
			rectangle(img, bounding_box[i].tl(), bounding_box[i].br(), Scalar(0, 255, 0), 3);//draw the rect in the original image
			
			drawPoint.x = bounding_box[i].x + bounding_box[i].width / 2;
			drawPoint.y = bounding_box[i].y;

		}
	}
	return drawPoint;//returning the draw point
}

void drawColor() {
	//drawPoints - {{x, y, i}, {x, y, i}} - red (i = 0), green (i = 1)
	for (int i = 0; i < drawPoints.size(); i++) {
		circle(img, Point(drawPoints[i][0], drawPoints[i][1]), 5, myColors_scalar[drawPoints[i][2]], FILLED);
	}

}

void findColor(Mat img) {

	Mat img_hsv, img_mask;	

	cvtColor(img, img_hsv, COLOR_BGR2HSV);//converting to hsv
	Point drawPoint;
	
	//getting hsv values from the myColors_hsv vector (global variable), so will loop through each colors
	for (int i = 0; i < myColors_hsv.size(); i++) {
		Scalar lower(myColors_hsv[i][0], myColors_hsv[i][1], myColors_hsv[i][2]);//hsv min
		Scalar upper(myColors_hsv[i][3], myColors_hsv[i][4], myColors_hsv[i][5]);//hsv max
		
		inRange(img_hsv, lower, upper, img_mask);//each color will have its own mask
		
		//will call getContours function here because we want to find the contours in all the mask images
		drawPoint = getContours(img_mask);
		
		if (drawPoint.x != 0 && drawPoint.y != 0) {//ensuring we are only adding points when it is detecting
			drawPoints.push_back({ drawPoint.x, drawPoint.y, i }); //passing x, y, and color_idx of the drawPoint into drawPoints
		}
		drawColor();//this function will draw the color onto the screen using the drawpoints vector
		string id = "Color number: "+to_string(i);
		imshow("Webcam", img);
		//imshow(id, img_mask);
		waitKey(2);
	}
	
}

int main() {

	//colorPicker();
	VideoCapture cap(0);//o is the index for the webcam
	//Mat img;
	
	while (true) {
		cap.read(img);
		findColor(img);//function to find colour
	}
	return 0;
}