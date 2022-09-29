
//Include Libraries

#include <opencv2/opencv.hpp>
#include <iostream>

// Namespace nullifies the use of cv::function();
using namespace std;
using namespace cv;

int main() {	 

	// Read an image
	Mat img_baby_yoda = imread("baby_yoda.jpg");
    
	// Display the image.
	imshow("Baby Yoda", img_baby_yoda); 

    waitKey(0);
}