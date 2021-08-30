#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

//////////////Basic Functions//////// - to import the image, first load it into our project


void main() {

	string path_img = "Resources/test.png";

	Mat img = imread(path_img);
	Mat img_resize, img_crop;

	//cout << img.size() << endl; image size is W x L = 768x559
	resize(img, img_resize, Size(640, 480));//resize to exact pixels
	resize(img, img_resize, Size(), 0.5, 0.5);//resize by a scaling factor, 0.5, 0.5

	Rect roi(100, 100, 50, 50);//roi = region of interest, 100, 100 is the starting point and 50, 50, is the directions in x and y respectively

	img_crop = img(roi);

	imshow("Image", img);
	imshow("Resized image", img_resize);
	imshow("Cropped Image", img_crop);

	waitKey(0);

}