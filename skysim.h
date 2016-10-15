#pragma once
#include <iostream>
#include <algorithm>



int sunset(double ang1, double ang2, int color[3]) {
	int b, g;
	for (int i = 0; i<480; i++) {
		//B 
		b = std::abs(255 * cos(ang1)*cos(ang1 / 1.5));
		color[0] = std::max(b, 30);
		//G
		g = std::abs(180 * cos(ang1)*cos(ang1 / 1.5)+ 40*cos(ang1/4)*sin(ang2*4));
		color[1] = std::max(g, 20);
		//		img.data[p + 1] = (100*cos(ang1/2)*cos(ang1/1.5)+100)*sin(a/2);
		//R
		color[2] = std::abs(255 * sin(ang1)*cos(ang1 / 2)*sin(ang2));
		//		img.data[p + 2] = 255*sin(ang1)*cos(ang1/1.5)*sin(ang2);
	}
	return 0;
}

int sundown(double ang1, double ang2, int color[3]) {
	for (int j = 0; j<640; j++) {
		color[2] = std::abs(255 * sin(ang1)*cos(ang1 / 2)*sin(ang2));
	}
	return 0;
};

int merge_skyline(cv::Mat sky, cv::Mat skyline[], int num) {
	int size = sky.rows * sky.cols;
	unsigned char skyline_color[3];
	unsigned char c;
	unsigned char *p, *q;


	for (int i = num - 1; i >= 0; i--) {
		p = sky.data;

		if (*p < 125 + i * 80) {
			c = (*p / 4);
			skyline_color[0] = c + i * 15;
			skyline_color[1] = c + i * 10;
			skyline_color[2] = (c >= 20 * i) ? c - i * 20 : 0;
		}
		else {
			c = (125 + i * 80) / 4;
			skyline_color[0] = c + i * 15;
			skyline_color[1] = c + i * 10;
			skyline_color[2] = (c >= 20 * i) ? c - i * 20 : 0;
		}
		q = skyline[i].data;
		for (int j = 0; j < size; j++) {
			if (*(q + 3 * j) < 100) {
				*p++ = skyline_color[0];
				*p++ = skyline_color[1];
				*p++ = skyline_color[2];
			}
			else p += 3;
		}
	}
	return 0;
}

int merge_light(cv::Mat sky, cv::Mat light[], int num, bool sw[]) {
	int size = sky.rows * sky.cols;
	unsigned char light_color[3];
	unsigned char c = 0;
	unsigned char *p, *q;


	for (int i = num - 1; i >= 0; i--) {
		p = sky.data;
		c = 0;

		if (!sw[i]) {
			c = 60;
			light_color[0] = c;
			light_color[1] = c;
			light_color[2] = c;
		}
		q = light[i].data;
		for (int j = 0; j < size; j++) {
			if (*(q + 3 * j) < 100) {
				if (c) {
					*p++ = light_color[0];
					*p++ = light_color[1];
					*p++ = light_color[2];
				}
				else {
					*p++ = *(q + 3 * j);
					*p++ = *(q + 3 * j + 1);
					*p++ = *(q + 3 * j + 2);
				}

			}
			else p += 3;
		}
	}
	return 0;
}

