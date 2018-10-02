// videocapture.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <fstream>

using namespace std;

//全局变量
int g_slider_position = 0; //滑块位置
int g_run = 1, g_dontest = 0; //单步模式
cv::VideoCapture g_cap;
void onTrackbarSlide(int pos, void *)  //滑块位置回调函数
{
	g_cap.set(cv::CAP_PROP_POS_FRAMES, pos);
	if (!g_dontest)
		g_run = 1;
	g_dontest = 0;
}
int main(int argc, char** argv)
{
	cv::namedWindow("Example3", cv::WINDOW_AUTOSIZE);
	g_cap.open(string(argv[1])); //打开视频文件，这里好像内存会泄露还没找到解决办法
	int frames = (int)g_cap.get(cv::CAP_PROP_FRAME_COUNT); //计算视频帧数
	int tmpw = (int)g_cap.get(cv::CAP_PROP_FRAME_WIDTH);
	int tmph = (int)g_cap.get(cv::CAP_PROP_FRAME_HEIGHT);
	cout << "Video has " << frames << "frames of dimensions(" << tmpw << "," << tmph << ")." << endl;

	cv::createTrackbar("Position", "Example3", &g_slider_position, frames, onTrackbarSlide); //创建滑条 位置每次改变都会调用回调函数
	cv::Mat frame;
	for (;;)
	{
		if (g_run != 0) {
			g_cap >> frame;
			if (frame.empty())
				break;
			int current_pos = (int)g_cap.get(cv::CAP_PROP_POS_FRAMES);
			g_dontest = 1;//在连续模式时调用回调函数时跳过单步执行

			cv::setTrackbarPos("Position", "Example3", current_pos);
			cv::imshow("Example3", frame);

			g_run -= 1;
		}
		char c = (char)cv::waitKey(10);
		if (c == 's')//单步模式
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

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件