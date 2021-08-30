#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

//////////////Importing Images//////// - to import the image, first load it into our project

void displayImage(string path){
	Mat img = imread(path);//reading and storing the image in img which is part of the class mat from cv library
	imshow("image-1", img);//displays the image, img
	waitKey(0);//the 0 is for infinity, unit is ms
}


//////////////Importing Videos////////
void displayVideo(string path) {
	VideoCapture cap(path);
	Mat img;
	while (true) {
		cap.read(img);//reading and storing the video in img which is part of the class mat from cv library
		imshow("Video-1", img);//displays the series of images, img captured from the video
		waitKey(10);//the 0 is for infinity, unit is ms
	}
}

void displayWebcam(int cam_id) {
	VideoCapture cap(cam_id);
	Mat img;
	while (true) {
		cap.read(img);
		imshow("Webcam", img);
		waitKey(10);
	}
}


//////////////Importing Videos//////// - to import the image, first load it into our project
void main() {

	string path_vid = "Resources/test_video.mp4";
	string path_img = "Resources/test.png";
		
	//displayImage(path_img);
	//displayVideo(path_vid);
	displayWebcam(0);//0 if only one webcam
}