#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#ifdef _WIN64
#ifdef _DEBUG
#pragma comment(lib ,"x64\\opencv_world310d")
#else
#pragma comment(lib ,"x64\\opencv_world310")
#endif
#else
#ifdef _DEBUG
#pragma comment(lib ,"x86\\opencv_core310d")
#pragma comment(lib ,"x86\\opencv_highgui310d")
#else
#pragma comment(lib ,"x86\\opencv_core310")
#pragma comment(lib ,"x86\\opencv_highgui310")
#endif
#endif

#include <windows.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

TCHAR szClassName[] = TEXT("Window");

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static HWND hButton;
	switch (msg)
	{
	case WM_CREATE:
		hButton = CreateWindow(TEXT("BUTTON"), TEXT("OpenCVのウィンドウを作成"), WS_VISIBLE | WS_CHILD, 0, 0, 0, 0, hWnd, (HMENU)IDOK, ((LPCREATESTRUCT)lParam)->hInstance, 0);
		break;
	case WM_SIZE:
		MoveWindow(hButton, 10, 10, 256, 32, TRUE);
		break;
	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{
			// 1幅320px、高さ240pxで赤色の画像データを生成
			cv::Mat redImg(cv::Size(320, 240), CV_8UC3, cv::Scalar(0, 0, 255));

			// 2画像表示用のウィンドウを生成
			cv::namedWindow("red", cv::WINDOW_AUTOSIZE);

			// 3ウィンドウに画像を表示
			cv::imshow("red", redImg);

			// 4キー入力を待機
			cv::waitKey(0);

			// 5作成したウィンドウを全て破棄
			cv::destroyAllWindows();
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInst, LPSTR pCmdLine, int nCmdShow)
{
	MSG msg;
	WNDCLASS wndclass = {
		CS_HREDRAW | CS_VREDRAW,
		WndProc,
		0,
		0,
		hInstance,
		0,
		LoadCursor(0,IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		0,
		szClassName
	};
	RegisterClass(&wndclass);
	HWND hWnd = CreateWindow(
		szClassName,
		TEXT("OpenCV For Visual Studio 2015 サンプル"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		0,
		CW_USEDEFAULT,
		0,
		0,
		0,
		hInstance,
		0
	);
	ShowWindow(hWnd, SW_SHOWDEFAULT);
	UpdateWindow(hWnd);
	while (GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (int)msg.wParam;
}
