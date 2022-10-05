
//Include Libraries

#include <opencv2/opencv.hpp>
#include <iostream>

// Namespace nullifies the use of cv::function();
using namespace std;
using namespace cv;

#define WINDOW_DIM 3

Mat convert_to_grayscale(const Mat &color_image);
Mat sobel_filter(const Mat &uf_image);

int main() {	 

	// Read an image
	Mat img_frame = imread("baby_yoda.jpg");

	// Display the image.
	//imshow("Baby Yoda", img_frame); 

	Mat s_ch_image;
	Mat sobel_image;
	s_ch_image = convert_to_grayscale(img_frame);
	sobel_image = sobel_filter(s_ch_image);

	cout << "rows: " << sobel_image.rows;
	cout << "\ncols: " << sobel_image.cols;
	imshow("Baby Yoda", sobel_image); 
	waitKey(0);
}


Mat sobel_filter(const Mat &uf_image)
{
	Mat s_ch_image(uf_image.rows - 2, uf_image.cols - 2, CV_8UC1);
	
	int gx[WINDOW_DIM][WINDOW_DIM] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
	int gy[WINDOW_DIM][WINDOW_DIM] = {{1, 2, 1}, {0, 0, 0}, {-1, -2, -1}};
	int g_sobel = 0;

	for (int rows = 1; rows < uf_image.rows - 1; rows++)
	{
		int cols = 1;
		while (cols < uf_image.cols - 1) // increment through each column and row position
		// calculating the sobel values for each
		{
			float gx_pix = 0;
			float gy_pix = 0;
		// loop through both the sobel matrix and 3x3 windows surrounding the pixel
		// add to gx and gy the product of the 3x3 window entries with their corresponding 
		// sobel matrix entries

			int rows_offset_sobel = rows - 1;
			int cols_offset_sobel = cols - 1;

			for (int sobel_row = rows_offset_sobel; sobel_row <= rows + 1; sobel_row++)
			{	
				for (int sobel_col = cols_offset_sobel; sobel_col <= cols + 1; sobel_col++)
				{
					gx_pix += 
						gx[sobel_row - rows_offset_sobel][sobel_col - cols_offset_sobel]
							*float(uf_image.at<uchar>(sobel_row, sobel_col));
					gy_pix += 
						gy[sobel_row - rows_offset_sobel][sobel_col - cols_offset_sobel]
							*float(uf_image.at<uchar>(sobel_row, sobel_col));
				}
			}
			
			g_sobel = int(abs(gx_pix) + abs(gy_pix));

			if (g_sobel > 255)
				g_sobel = 255;

			s_ch_image.at<uchar>(rows, cols) = uchar(g_sobel);

			cols++;
		}
	}
	return s_ch_image;
}


Mat convert_to_grayscale(const Mat &color_image)
{
	Mat s_ch_image(color_image.rows, color_image.cols, CV_8UC1);

	for (int rows = 0; rows < color_image.rows; rows++)
	{
		int cols = 0;
		int gray_cols = 0;

		while (cols < color_image.cols*3)
		{
			// first pixel is blue
			float blue_pixel = float(color_image.at<uchar>(rows, cols));
			// second pixel is green
			float green_pixel = float(color_image.at<uchar>(rows, cols + 1));
			// red pixel is red
			float red_pixel = float(color_image.at<uchar>(rows, cols + 2));
			
			float new_pixel = (0.2126*red_pixel + 0.7152*green_pixel + 0.0722*blue_pixel);

			s_ch_image.at<uchar>(rows, gray_cols) = uchar(new_pixel);

			cols = cols + 3;
			gray_cols++;
		}
	}
	return s_ch_image;
}
