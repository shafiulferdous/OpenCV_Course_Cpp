#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

//////////////Warping an image////////


void main() {
	string path = "Resources/cards.jpg";
	Mat img_warp, matrix;
	
	float w = 250.0, h = 350.0;

	Mat img = imread(path);
	//we need coordinates of the 4 points of the card of interest - this can be obbtained using paint
	Point2f src[4] = { {529.0, 142.0}, {771.0, 190.0}, {405.0, 395.0}, {674.0, 457.0} };//source coordinates obtained via paint
	Point2f dst[4] = { {0.0, 0.0}, {w, 0.0}, {0.0, h}, {w, h} };//destination coordinates

	//to warp or to map, we need a mapping matrix
	matrix = getPerspectiveTransform(src, dst);//getPerspectiveTransform only takes arrays as type float
	warpPerspective(img, img_warp, matrix, Point(w, h));//Point(w, h) provides the size

	for (int i = 0; i < 4; i++) {
		circle(img, src[i], 10, Scalar(0, 0, 255), FILLED);//creating a circle at the 
	}


	imshow("Image", img);
	imshow("Image_Warped", img_warp);
	waitKey(0);

}