#include <cstdlib>
#include <iostream>
#include <vector>

#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>

#define PI 3.1415926

//Uncomment this line at run-time to skip GUI rendering
#define _DEBUG

using namespace cv;
using namespace std;

const string CAM_PATH="/dev/video0";
const string MAIN_WINDOW_NAME="Processed Image";
const string CANNY_WINDOW_NAME="Canny";

const int CANNY_LOWER_BOUND=50;
const int CANNY_UPPER_BOUND=250;
const int HOUGH_THRESHOLD=150;

int main()
{
	VideoCapture capture(CAM_PATH);
	//If this fails, try to open as a video camera, through the use of an integer param
	if (!capture.isOpened())
	{
		capture.open(atoi(CAM_PATH.c_str()));
	}

	double dWidth=capture.get(CV_CAP_PROP_FRAME_WIDTH);			//the width of frames of the video
	double dHeight=capture.get(CV_CAP_PROP_FRAME_HEIGHT);		//the height of frames of the video
	clog<<"Frame Size: "<<dWidth<<"x"<<dHeight<<endl;

	Mat image;
	while(true)
	{
		capture>>image;
		if(image.empty())
			break;

		//Set the ROI for the image
		Rect roi(0,image.rows/3,image.cols,image.rows/3);
		Mat imgROI=image(roi);

		//Canny algorithm
		Mat contours;
		Canny(imgROI,contours,CANNY_LOWER_BOUND,CANNY_UPPER_BOUND);
		#ifdef _DEBUG
		imshow(CANNY_WINDOW_NAME,contours);
		#endif

		vector<Vec2f> lines;
		HoughLines(contours,lines,1,PI/180,HOUGH_THRESHOLD);
		Mat result(imgROI.size(),CV_8U,Scalar(255));
		imgROI.copyTo(result);
		clog<<lines.size()<<endl;
		
		float maxRad=-2*PI;
		float minRad=2*PI;
		//Draw the lines and judge the slope
		for(vector<Vec2f>::const_iterator it=lines.begin();it!=lines.end();++it)
		{
			float rho=(*it)[0];			//First element is distance rho
			float theta=(*it)[1];		//Second element is angle theta

			//Filter to remove vertical and horizontal lines,
			//and atan(0.09) equals about 5 degrees.
			if((theta>0.09&&theta<1.48)||(theta>1.62&&theta<3.05))
			{
				if(theta>maxRad)
					maxRad=theta;
				if(theta<minRad)
					minRad=theta;
				
				#ifdef _DEBUG
				//point of intersection of the line with first row
				Point pt1(rho/cos(theta),0);
				//point of intersection of the line with last row
				Point pt2((rho-result.rows*sin(theta))/cos(theta),result.rows);
				//Draw a line
				line(result,pt1,pt2,Scalar(0,255,255),3,CV_AA);
				#endif
			}

			#ifdef _DEBUG
			clog<<"Line: ("<<rho<<","<<theta<<")\n";
			#endif
		}

		#ifdef _DEBUG
		stringstream overlayedText;
		overlayedText<<"Lines: "<<lines.size();
		putText(result,overlayedText.str(),Point(10,result.rows-10),2,0.8,Scalar(0,0,255),0);
		imshow(MAIN_WINDOW_NAME,result);
		#endif

		lines.clear();
		waitKey(1);
	}
	return 0;
}
