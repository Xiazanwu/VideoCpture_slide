// videocapture.cpp : ���ļ����� "main" ����������ִ�н��ڴ˴���ʼ��������
//

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <fstream>

using namespace std;

//ȫ�ֱ���
int g_slider_position = 0; //����λ��
int g_run = 1, g_dontest = 0; //����ģʽ
cv::VideoCapture g_cap;
void onTrackbarSlide(int pos, void *)  //����λ�ûص�����
{
	g_cap.set(cv::CAP_PROP_POS_FRAMES, pos);
	if (!g_dontest)
		g_run = 1;
	g_dontest = 0;
}
int main(int argc, char** argv)
{
	cv::namedWindow("Example3", cv::WINDOW_AUTOSIZE);
	g_cap.open(string(argv[1])); //����Ƶ�ļ�����������ڴ��й¶��û�ҵ�����취
	int frames = (int)g_cap.get(cv::CAP_PROP_FRAME_COUNT); //������Ƶ֡��
	int tmpw = (int)g_cap.get(cv::CAP_PROP_FRAME_WIDTH);
	int tmph = (int)g_cap.get(cv::CAP_PROP_FRAME_HEIGHT);
	cout << "Video has " << frames << "frames of dimensions(" << tmpw << "," << tmph << ")." << endl;

	cv::createTrackbar("Position", "Example3", &g_slider_position, frames, onTrackbarSlide); //�������� λ��ÿ�θı䶼����ûص�����
	cv::Mat frame;
	for (;;)
	{
		if (g_run != 0) {
			g_cap >> frame;
			if (frame.empty())
				break;
			int current_pos = (int)g_cap.get(cv::CAP_PROP_POS_FRAMES);
			g_dontest = 1;//������ģʽʱ���ûص�����ʱ��������ִ��

			cv::setTrackbarPos("Position", "Example3", current_pos);
			cv::imshow("Example3", frame);

			g_run -= 1;
		}
		char c = (char)cv::waitKey(10);
		if (c == 's')//����ģʽ
		{
			g_run = 1; cout << "Single step, run=" << g_run << endl;
		}
		if (c == 'r') {
			g_run = -1;
			cout << "Run mode, run= " << g_run << endl;
		}
		if (c == 'q') {
			break;
		}
	}
	return 0;
}

// ���г���: Ctrl + F5 ����� >����ʼִ��(������)���˵�
// ���Գ���: F5 ����� >����ʼ���ԡ��˵�

// ������ʾ: 
//   1. ʹ�ý��������Դ�������������/�����ļ�
//   2. ʹ���Ŷ���Դ�������������ӵ�Դ�������
//   3. ʹ��������ڲ鿴���������������Ϣ
//   4. ʹ�ô����б��ڲ鿴����
//   5. ת������Ŀ��>���������Դ����µĴ����ļ�����ת������Ŀ��>�����������Խ����д����ļ���ӵ���Ŀ
//   6. ��������Ҫ�ٴδ򿪴���Ŀ����ת�����ļ���>���򿪡�>����Ŀ����ѡ�� .sln �ļ�