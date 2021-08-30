#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

//////////////Shape Detection////////

void getContours(Mat img_dil, Mat img_draw){//custom function

	//contours is essentially a vector of vector of points, so
	//{ {Point(20, 30), Point(1, 3)},
	//	{Point(5, 3), Point(1, 3)},
	//	{Point(80, 20), Point(31, 4)}
	//}
	vector<vector<Point>> contours;//a vector which contains a vector of points -> a list of all the coordinates

	//hierarchy is essentially a vector consisting of another vector of 4 integers - C++ has a separate datatype for this: Vec4i which means vector of 4 integers
	vector<Vec4i>hierarchy;//Vec4i is built in data structure which contains a vector of 4 integers -> a list of 4 coordinates

	findContours(img_dil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);//RETR_EXTERNAL only returns the extreme outer contours
	//function in opencv to draw contours
	
	//now, the vector contours has all the contours in the img_dil

	for (int i = 0; i < contours.size(); i++)//this will loop through each contour, and record the number of points and draw the bounding rectangle
	{	
		int area = contourArea(contours[i]);//finding area of each of the contours
		cout << "Area of contour: " << i <<"="<< area << endl;

		vector<vector<Point>> contour_points(contours.size());//contour_poly is vector of coordinates, size of contour_poly is the <= than the number of contours
		vector<Rect> bounding_rect(contours.size());//bounding_rect is a vector of rectangle

		string obj_type;

		if (area > 1000)//to eliminate the noise
		{
			float perimeter = arcLength(contours[i], true);//the boolean is basically to say if the curve is closed or not, true is for closed
			approxPolyDP(contours[i], contour_points[i], 0.02*perimeter, true);//approximates polygonal curve with points and sends them to the contour_points vector
			drawContours(img_draw, contour_points, i, Scalar(255, 0, 255), 2);//contour_poly is basically the number of points drawn on the image
			
			cout <<"Number of Contour points: "<< contour_points[i].size() << endl;
			
			bounding_rect[i] = boundingRect(contour_points[i]);//this returns the points of the rectangle which bounds the shape using the # contour points
			rectangle(img_draw, bounding_rect[i].tl(), bounding_rect[i].br(), Scalar(0, 255, 0), 2);//creates a rectangle based on the points from bounding_rect

			//now we want to detect the shape type by using the number of contour points
			int obj_pts = (int) contour_points[i].size();
			if (obj_pts == 3) { obj_type = "Triangle"; }
			if (obj_pts == 4){ 
				float asp_ratio = (float) (bounding_rect[i].width) / (float) (bounding_rect[i].height);
				if (asp_ratio > 0.99 && asp_ratio < 1.01) { obj_type = "Square"; }
				else { obj_type = "Rectangle"; }			
			}
					
			if (obj_pts > 4) { obj_type = "Circle"; }

			//now we want to annotate the image with this text
			putText(img_draw, obj_type, { bounding_rect[i].x, bounding_rect[i].y - 5 }, FONT_HERSHEY_COMPLEX_SMALL, 1, Scalar(255, 0, 255), 1);

		}
	}

}

void main() {
	string path = "Resources/shapes.png";

	Mat img = imread(path);
	Mat img_gray, img_blur, img_canny, img_dil;
	
	//Preprocessing the image
	cvtColor(img, img_gray, COLOR_BGR2GRAY);//changing it from RBG to gray
	GaussianBlur(img_gray, img_blur, Size(3, 3), 3, 3);//blurring it
	Canny(img_blur, img_canny, 5, 5);//canny
	Mat kernel = getStructuringElement(MORPH_RECT, Size(5, 5));//Kernel to dilate the canny image
	dilate(img_canny, img_dil, kernel);

	getContours(img_dil, img);//using img_dil, draw on img which is our original image

	//imshow("Image", img);
	//imshow("Image Blur", img_blur);
	//imshow("Image Canny", img_canny);
	//imshow("Image Canny", img_dil); 
	imshow("Image Draw", img);

	waitKey(0);
	

}