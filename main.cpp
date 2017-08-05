#include <cstdio>
#include <iostream>
#include <vector>

#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/opencv.hpp>

#include "linefinder.h"

#define PI 3.1415926

using namespace cv;
using namespace std;

int main()
{
	int houghVote=200;
	string arg=argv[1];
	bool showSteps=argv[2];

	string window_name="Processed Video";
	namedWindow(window_name,CV_WINDOW_KEEPRATIO); //resizable window;
	VideoCapture capture(arg);

	if (!capture.isOpened()) //if this fails, try to open as a video camera, through the use of an integer param
	{
		capture.open(atoi(arg.c_str()));
	}

	double dWidth=capture.get(CV_CAP_PROP_FRAME_WIDTH); //get the width of frames of the video
	double dHeight=capture.get(CV_CAP_PROP_FRAME_HEIGHT); //get the height of frames of the video

	cout<<"Frame Size = "<<dWidth<<"x"<<dHeight<<endl;

	Size frameSize(static_cast<int>(dWidth),static_cast<int>(dHeight));

	//VideoWriter oVideoWriter("LaneDetection.avi",CV_FOURCC('P','I','M','1'),20,frameSize,true); //initialize the VideoWriter object 

	Mat image;
	image=imread(argv[1]);
	while(1)
	{
		capture>>image;
		if(image.empty())
			break;
		Mat gray;
		cvtColor(image,gray,CV_RGB2GRAY);
		//vector<string> codes;
		//Mat corners;
		//findDataMatrix(gray, codes, corners);
		//drawDataMatrixCodes(image, codes, corners);

		Rect roi(0,image.cols/3,image.cols-1,image.rows-image.cols/3);// set the ROI for the image
		Mat imgROI=image(roi);
		//Display the image
		if(showSteps)
		{
			namedWindow("Original Image");
			imshow("Original Image",imgROI);
		}

		//Canny algorithm
		Mat contours;
		Canny(imgROI,contours,50,250);
		Mat contoursInv;
		threshold(contours,contoursInv,128,255,THRESH_BINARY_INV);

		//Display Canny image
		if(showSteps)
		{
			namedWindow("Contours");
			imshow("Contours1",contoursInv);
		}

		 /*
		  *Hough tranform for line detection with feedback
		  *Increase by 25 for the next frame if we found some lines.
		  *This is so we don't miss other lines that may crop up in the next frame
		  *but at the same time we don't want to start the feed back loop from scratch.
		  */
		vector<Vec2f> lines;
		if(houghVote<1 or lines.size() > 2)
		{ //lost all lines. reset 
			houghVote=200;
		}
		else
		{
			houghVote+=25;
		}
		while(lines.size()<5&&houghVote>0)
		{
			HoughLines(contours,lines,1,PI/180,houghVote);
			houghVote-=5;
		}
		cout<<houghVote<<"\n";
		Mat result(imgROI.size(),CV_8U,Scalar(255));
		imgROI.copyTo(result);

		//Draw the limes
		vector<Vec2f>::const_iterator it=lines.begin();
		Mat hough(imgROI.size(),CV_8U,Scalar(0));
		while(it!=lines.end())
		{
			float rho=(*it)[0];			//first element is distance rho
			float theta=(*it)[1];		//second element is angle theta

			if(theta>0.09 && theta<1.48||theta < 3.14 && theta > 1.66)
			// filter to remove vertical and horizontal lines
			{
				// point of intersection of the line with first row
				Point pt1(rho/cos(theta),0);
				// point of intersection of the line with last row
				Point pt2((rho-result.rows*sin(theta))/cos(theta),result.rows);
				// draw a white line
				line(result,pt1,pt2,Scalar(255),8);
				line(hough,pt1,pt2,Scalar(255),8);
			}

			//cout << "line: (" << rho << "," << theta << ")\n"; 
			++it;
		}

		//Display the detected line image
		if(showSteps)
		{
			namedWindow("Detected Lines with Hough");
			imshow("Detected Lines with Hough",result);
		}

		//Create LineFinder instance
		LineFinder ld;

		//Set probabilistic Hough parameters
		ld.setLineLengthAndGap(60,10);
		ld.setMinVote(4);
		
		//Detect lines
		vector<Vec4i> li=ld.findLines(contours);
		Mat houghP(imgROI.size(),CV_8U,Scalar(0));
		ld.setShift(0);
		ld.drawDetectedLines(houghP);
		cout<<"First Hough"<<"\n";

		if(showSteps)
		{
			namedWindow("Detected Lines with HoughP");
			imshow("Detected Lines with HoughP",houghP);
		}
		
		//bitwise AND of the two hough images
		bitwise_and(houghP,hough,houghP);
		Mat houghPinv(imgROI.size(),CV_8U,Scalar(0));
		Mat dst(imgROI.size(),CV_8U,Scalar(0));
		threshold(houghP,houghPinv,150,255,THRESH_BINARY_INV); // threshold and invert to black lines

		if(showSteps)
		{
			namedWindow("Detected Lines with Bitwise");
			imshow("Detected Lines with Bitwise",houghPinv);
		}

		Canny(houghPinv,contours,100,350);
		li=ld.findLines(contours);

		//Display Canny image
		if(showSteps)
		{
			namedWindow("Contours");
			imshow("Contours2",contours);
		}

		//Set probabilistic Hough parameters
		ld.setLineLengthAndGap(5,2);
		ld.setMinVote(1);
		ld.setShift(image.cols/3);
		ld.drawDetectedLines(image);

		stringstream stream;
		stream<<"Lines Segments: "<<lines.size();

		putText(image,stream.str(),Point(10,image.rows-10),2,0.8,Scalar(0,0,255),0);
		imshow(window_name,image);

		//oVideoWriter.write(image); //writer the frame into the file

		char key=(char)waitKey(10);
		lines.clear();
	}
}
