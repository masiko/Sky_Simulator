#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "Rayleigh_Sca.h"

int sunset(double ang1, double ang2, int color[3]) {
	for (int i=0; i<480; i++) {
		//B 
		color[0] = 255*cos(ang1)*cos(ang1/1.5);
		//G
		color[1] = (200*cos(ang1)*cos(ang1/1.5));
//		img.data[p + 1] = (100*cos(ang1/2)*cos(ang1/1.5)+100)*sin(a/2);
		//R
		color[2] = 255*sin(ang1)*cos(ang1/2)*sin(ang2);
//		img.data[p + 2] = 255*sin(ang1)*cos(ang1/1.5)*sin(ang2);
	}
	return 0;
}

int sundown(double ang1, double ang2, int color[3]) {
	for (int j=0; j<640; j++) {
		color[2] = 255*sin(ang1)*cos(ang1/2)*sin(ang2);
	}
	return 0;
};


int main() {
	double ks=0;
	int w=0;
	int l=100;
	int p;
	int color[3];
	double ang1, ang2;
	
	cv::Mat out;
	out.create(480, 640, CV_8UC3);
	cv::namedWindow("out");

	for (ang1=.0; ang1<M_PI/2; ang1+=0.01) {
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
		cv::imshow("out", out);
		cv::waitKey(100);
	}

	for (ang1=M_PI/2; ang1<3*M_PI/2; ang1+=0.01) {
		for (int i=0; i<480; i++) {
			ang2 = (M_PI/1920*i);

			sundown(ang1, ang2, color);

			for (int j=0; j<640; j++) {
				p = 3*(j+640*i);
				out.data[p + 2] = color[2];
			}
		}
		cv::imshow("out", out);
		cv::waitKey(100);
	}

	for (ang1=M_PI/2; ang1>0; ang1-=0.01) {
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
		cv::imshow("out", out);
		cv::waitKey(100);
	}
	out.release();
	return 0;
}

