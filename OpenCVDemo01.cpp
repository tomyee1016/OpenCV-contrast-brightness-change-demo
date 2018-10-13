/*对比度及亮度改变的例子
*/
#include<opencv2/opencv.hpp>
#include<iostream>
#include<math.h>
using namespace cv;//创建名空间
int main(int argc, char** argv) {
	Mat src, dst;
	src = imread("F:/OutPutResult/Test/Test/123.jpg");//读取一张图片
	if (!src.data) {
		printf("could not load image...");
		return -1;
	}
	char input_win[] = "input image";
	namedWindow(input_win, CV_WINDOW_AUTOSIZE);//创建opencv窗口
	imshow(input_win, src);//显示图片
	cvtColor(src, src, CV_BGR2GRAY);//色彩空间的转换，RGB图像到灰度图像
	//对比度与亮度的改变
	int height = src.rows;
	int width = src.cols;
	int nc = src.channels();
	float alpha = 1.5;//调整对比度
	float beta = 50;//调整亮度
	dst = Mat::zeros(src.size(), src.type());//创建一个大小、类型与src一致，像素值初始化为0的图像
	//使用双重for循环得到像素值
	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			if (nc == 3) {//3通道运算
				float b = src.at<Vec3b>(row, col)[0];//blue
				float g = src.at<Vec3b>(row, col)[1];//green
				float r = src.at<Vec3b>(row, col)[2];//red
				//开始操作像素
				dst.at<Vec3b>(row, col)[0] = saturate_cast<uchar>(b*alpha + beta);
				dst.at<Vec3b>(row, col)[1] = saturate_cast<uchar>(g*alpha + beta);
				dst.at<Vec3b>(row, col)[2] = saturate_cast<uchar>(r*alpha + beta);
			}
			else if (nc == 1) {//单通道运算
				float v = src.at<uchar>(row, col);
				dst.at<uchar>(row, col) = saturate_cast<uchar>(v*alpha + beta);
			}
	}
	}
	char output_title[] = "contrast and brightness change demo";
	namedWindow(output_title, CV_WINDOW_AUTOSIZE);
	imshow(output_title, dst);
	waitKey(0);//等待
	return 0;
}
