/*�Աȶȼ����ȸı������
*/
#include<opencv2/opencv.hpp>
#include<iostream>
#include<math.h>
using namespace cv;//�������ռ�
int main(int argc, char** argv) {
	Mat src, dst;
	src = imread("F:/OutPutResult/Test/Test/123.jpg");//��ȡһ��ͼƬ
	if (!src.data) {
		printf("could not load image...");
		return -1;
	}
	char input_win[] = "input image";
	namedWindow(input_win, CV_WINDOW_AUTOSIZE);//����opencv����
	imshow(input_win, src);//��ʾͼƬ
	cvtColor(src, src, CV_BGR2GRAY);//ɫ�ʿռ��ת����RGBͼ�񵽻Ҷ�ͼ��
	//�Աȶ������ȵĸı�
	int height = src.rows;
	int width = src.cols;
	int nc = src.channels();
	float alpha = 1.5;//�����Աȶ�
	float beta = 50;//��������
	dst = Mat::zeros(src.size(), src.type());//����һ����С��������srcһ�£�����ֵ��ʼ��Ϊ0��ͼ��
	//ʹ��˫��forѭ���õ�����ֵ
	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			if (nc == 3) {//3ͨ������
				float b = src.at<Vec3b>(row, col)[0];//blue
				float g = src.at<Vec3b>(row, col)[1];//green
				float r = src.at<Vec3b>(row, col)[2];//red
				//��ʼ��������
				dst.at<Vec3b>(row, col)[0] = saturate_cast<uchar>(b*alpha + beta);
				dst.at<Vec3b>(row, col)[1] = saturate_cast<uchar>(g*alpha + beta);
				dst.at<Vec3b>(row, col)[2] = saturate_cast<uchar>(r*alpha + beta);
			}
			else if (nc == 1) {//��ͨ������
				float v = src.at<uchar>(row, col);
				dst.at<uchar>(row, col) = saturate_cast<uchar>(v*alpha + beta);
			}
	}
	}
	char output_title[] = "contrast and brightness change demo";
	namedWindow(output_title, CV_WINDOW_AUTOSIZE);
	imshow(output_title, dst);
	waitKey(0);//�ȴ�
	return 0;
}
