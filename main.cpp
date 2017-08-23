#include <cstdio>
#include <iostream>
#include <vector>

#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>

#include "linefinder.h"

#define PI 3.1415926

using namespace cv;
using namespace std;

int main()
{
	int houghVote=200;
	string arg="/dev/video0";
	bool showSteps=true;

	string window_name="Processed Image";
	VideoCapture capture(arg);

	if (!capture.isOpened())
	//If this fails, try to open as a video camera, through the use of an integer param
	{
		capture.open(atoi(arg.c_str()));
	}

	double dWidth=capture.get(CV_CAP_PROP_FRAME_WIDTH);			//get the width of frames of the video
	double dHeight=capture.get(CV_CAP_PROP_FRAME_HEIGHT);		//get the height of frames of the video
	cout<<"Frame Size: "<<dWidth<<"x"<<dHeight<<endl;

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
		Canny(imgROI,contours,50,250);
		imshow("Canny",contours);

		vector<Vec2f> lines;
		HoughLines(contours,lines,1,PI/180,130);
		Mat result(imgROI.size(),CV_8U,Scalar(255));
		imgROI.copyTo(result);
		clog<<lines.size()<<endl;

		//Draw the lines
		for(vector<Vec2f>::const_iterator it=lines.begin();it!=lines.end();++it)
		{
			float rho=(*it)[0];			//first element is distance rho
			float theta=(*it)[1];		//second element is angle theta

			//if((theta>0.09&&theta<1.48)||(theta<3.14&&theta>1.66))
			//filter to remove vertical and horizontal lines
			{
				//point of intersection of the line with first row
				Point pt1(rho/cos(theta),0);
				//point of intersection of the line with last row
				Point pt2((rho-result.rows*sin(theta))/cos(theta),result.rows);
				//Draw a line
				line(result,pt1,pt2,Scalar(0,255,255),3,CV_AA);
			}

			clog<<"Line: ("<<rho<<","<<theta<<")\n";
		}

		stringstream overlayedText;
		overlayedText<<"Lines Segments: "<<lines.size();

		putText(result,overlayedText.str(),Point(10,image.rows/3-10),2,0.8,Scalar(0,0,255),0);
		imshow(window_name,result);

		lines.clear();
		char key=(char)waitKey(1);
	}
}
