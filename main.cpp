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
	namedWindow(window_name);
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
	image=imread(arg);
	while(true)
	{
		capture>>image;
		if(image.empty())
			break;

		//Set the ROI for the image
		Rect roi((image.cols-image.rows)/2,0,image.rows,image.rows);
		Mat imgROI=image(roi);

		//Canny algorithm
		Mat contours;
		Canny(imgROI,contours,50,250);

		 /*
		  *Hough tranform for line detection with feedback
		  *Increase by 25 for the next frame if we found some lines.
		  *This is so we don't miss other lines that may crop up in the next frame
		  *but at the same time we don't want to start the feed back loop from scratch.
		  */
		vector<Vec2f> lines;
		if(houghVote<1||lines.size()>10)
		//All lines lost. Reset
			houghVote=200;
		else
			houghVote+=25;
		
		while(lines.size()<2&&houghVote>0)
		{
			HoughLines(contours,lines,1,PI/180,houghVote);
			houghVote-=5;
		}
		clog<<"houghVote="<<houghVote<<endl;
		Mat result(imgROI.size(),CV_8U,Scalar(255));
		imgROI.copyTo(result);

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

		putText(result,overlayedText.str(),Point(10,image.rows-10),2,0.8,Scalar(0,0,255),0);
		imshow(window_name,result);

		lines.clear();
		char key=(char)waitKey(1);
	}
}
