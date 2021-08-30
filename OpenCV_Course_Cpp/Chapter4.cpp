#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

//////////////Draw Shapes and Texts//////// - to import the image, first load it into our project


void main() {
//Creating a blank image of a particular color
Mat img(512, 512, CV_8UC3, Scalar(255, 255, 255));//scalar is to set the color

//Creating a circle
circle(img, Point(256, 256), 155, Scalar(0, 69, 255), FILLED);//creating a circle on the image created
rectangle(img, Point(130, 226), Point(382, 286), Scalar(255, 255, 255), FILLED);
line(img, Point(130, 296), Point(382, 296), Scalar(255, 255, 255), 2);

putText(img, "Shaf", Point(137, 262), FONT_HERSHEY_COMPLEX, 0.75, Scalar(0, 69, 255), 2);//0.75 is the font scale

imshow("Image", img);
waitKey(0);


}