#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

//////////////Basic Functions//////// - to import the image, first load it into our project

void displayImage(string path) {
	Mat img = imread(path);//reading and storing the image in img which is part of the class mat from cv library
	imshow("image-1", img);//displays the image, img
	waitKey(0);//the 0 is for infinity, unit is ms
}

void displayImage_gray(string path) {
	Mat img = imread(path);//reading and storing the image in img which is part of the class mat from cv library
	Mat img_gray;
	cvtColor(img, img_gray, COLOR_BGR2GRAY);
	imshow("image-Color", img);
	imshow("image-Gray", img_gray);//displays the image, img
	waitKey(0);//the 0 is for infinity, unit is ms
}

void displayImage_blur(string path) {
	Mat img = imread(path);//reading and storing the image in img which is part of the class mat from cv library
	Mat img_blur, img_canny, img_dilate, img_erosion;
	GaussianBlur(img, img_blur, Size(33, 33), 6, 0);
	Canny(img_blur, img_canny, 5, 5);

	Mat kernel = getStructuringElement(MORPH_RECT, Size(1, 1));
	dilate(img_canny, img_dilate, kernel);
	erode(img_canny, img_erosion, kernel);

	imshow("image", img);
	imshow("image-Blur", img_blur);//displays the image, img
	imshow("image-Canny", img_canny);
	imshow("image-Dilation", img_dilate);
	imshow("Image Erosion", img_erosion);

	waitKey(0);//the 0 is for infinity, unit is ms
}


void main() {

	string path_img = "Resources/test.png";

	displayImage_blur(path_img);
	
}