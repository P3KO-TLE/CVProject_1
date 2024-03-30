#include<iostream>
#include<opencv2/imgproc.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/videoio.hpp>

using namespace std;
using namespace cv;

const int KSIZE_MAX = 200;
const int ALPHA_MAX = 100;

int alpha_slider, ksize1_slider, ksize2_slider;
int ksize1, ksize2;
double alpha, beta;
Mat img_human, img_animal, gaus_human, gaus_animal, high_animal, res;

void read() {
	img_human = imread("D:/CV/Resources/human.jpg");
	img_animal = imread("D:/CV/Resources/animal.jpeg");
	resize(img_human, img_human, Size(350, 410));
	resize(img_animal, img_animal, Size(350, 410));
}

static void solve(int, void*) {
	if (ksize1_slider % 2 == 0)ksize1 = ksize1_slider + 1;
	if (ksize2_slider % 2 == 0)ksize2 = ksize2_slider + 1;
	GaussianBlur(img_human, gaus_human, Size(ksize1, ksize1), 0, 0);
	GaussianBlur(img_animal, gaus_animal, Size(ksize2, ksize2), 0, 0);
	high_animal = img_animal - gaus_animal;
	imshow("¸ßÆµ", high_animal);
	imshow("µÍÆµ", gaus_human);

	alpha = (double)alpha_slider / ALPHA_MAX;
	beta = 1.0 - alpha;
	addWeighted(high_animal, alpha, gaus_human, beta, 0.0, res);
	imshow("res", res);
}

void sliders() {
	namedWindow("res", WINDOW_AUTOSIZE);
	char alphaTrackbar[50], ksize1Trackbar[50], ksize2Trackbar[50];
	sprintf_s(alphaTrackbar, "Alpha: %d", ALPHA_MAX);
	sprintf_s(ksize1Trackbar, "ksize1: %d", KSIZE_MAX);
	sprintf_s(ksize2Trackbar, "ksize2: %d", KSIZE_MAX);
	createTrackbar(alphaTrackbar, "res", &alpha_slider, ALPHA_MAX, solve);
	createTrackbar(ksize1Trackbar, "res", &ksize1_slider, KSIZE_MAX, solve);
	createTrackbar(ksize2Trackbar, "res", &ksize2_slider, KSIZE_MAX, solve);

	solve(alpha_slider, 0);
	solve(ksize1_slider, 0);
	solve(ksize2_slider, 0);
}

int main() {
	read();
	sliders();
	waitKey(0);
	destroyAllWindows();
	return 0;
}
