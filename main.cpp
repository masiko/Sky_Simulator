#include <iostream>

#define _USE_MATH_DEFINES

#include <cmath>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "skysim.h"



int main() {
	double ks=0;
	int w=0;
	int l=100;
	int p;
	int color[3];
	double ang1, ang2;
	const int width = 640;
	const int height = 480;
	int num_s = 2;
	int num_l = 2;
	bool sw[2];

	cv::Mat skyline[2];
	cv::Mat light[2];
	cv::Mat out;
	char wname[] = "dst";
	out.create(height, width, CV_8UC3);
	cv::namedWindow(wname);

	skyline[0] = cv::imread("skyline1.png");		//‹ßŒi
	skyline[1] = cv::imread("skyline2.png");		//‰“Œi
	light[0]   = cv::imread("light1.png");
	light[1] = cv::imread("light2.png");			//í–é“”
	if (skyline[0].empty())	return 1;
	if (skyline[1].empty())	return 1;
	if (light[0].empty())	return 1;
	if (light[1].empty())	return 1;

	for (ang1=.0; ang1<M_PI/2; ang1+=0.01) {
		(ang1 > M_PI / 3) ? sw[0] = true : sw[0] = false;
		(ang1 > M_PI / 4) ? sw[1] = true : sw[1] = false;
		for (int i=0; i<480; i++) {
			ang2 = (M_PI/1920*i);

			sunset(ang1, ang2, color);

			for (int j=0; j<640; j++) {
				p = 3*(j+640*i);
				out.data[p] = color[0];
				out.data[p+1] = color[1];
				out.data[p+2] = color[2];
			}
		}
		merge_skyline(out, skyline, num_s);
		merge_light(out, light, num_l, sw);
		cv::imshow(wname, out);
		cv::waitKey(100);
	}

	for (ang1=M_PI/2; ang1<3*M_PI/2; ang1+=0.01) {
		(7*M_PI / 6 < ang1) ? sw[0] = false : sw[0] = true;
		 sw[1] = true;
		for (int i=0; i<480; i++) {
			ang2 = (M_PI/1920*i);

			sundown(ang1, ang2, color);

			for (int j=0; j<640; j++) {
				p = 3*(j+640*i);
				out.data[p + 2] = color[2];
			}
		}
		merge_skyline(out, skyline, num_s);
		merge_light(out, light, num_l, sw);
		cv::imshow(wname, out);
		cv::waitKey(100);
	}

	for (ang1=M_PI/2; ang1>0; ang1-=0.01) {
		sw[0] = false;
		(ang1 > M_PI / 4) ? sw[1] = true : sw[1] = false;

		for (int i=0; i<480; i++) {
			ang2 = (M_PI/1920*i);

			sunset(ang1, ang2, color);

			for (int j=0; j<640; j++) {
				p = 3*(j+640*i);
				out.data[p] = color[0];
				out.data[p+1] = color[1];
				out.data[p+2] = color[2];
			}
		}
		merge_skyline(out, skyline, num_s);
		merge_light(out, light, num_l, sw);
		cv::imshow(wname, out);
		cv::waitKey(100);
	}
	
	
	out.release();
	return 0;
}

