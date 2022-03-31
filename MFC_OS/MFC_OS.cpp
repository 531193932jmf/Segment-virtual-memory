// MFC_OS.cpp : 定义应用程序的入口点。
//

#include "framework.h"
#include "MFC_OS.h"

#define MAX_LOADSTRING 100

// 全局变量:
HINSTANCE hInst;                                // 当前实例
WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名

// 此代码模块中包含的函数的前向声明:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 在此处放置代码。

    // 初始化全局字符串
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MFCOS, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 执行应用程序初始化:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MFCOS));

    MSG msg;

    // 主消息循环:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  函数: MyRegisterClass()
//
//  目标: 注册窗口类。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MFCOS));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MFCOS);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);


}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目标: 保存实例句柄并创建主窗口
//
//   注释:
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 将实例句柄存储在全局变量中

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目标: 处理主窗口的消息。
//
//  WM_COMMAND  - 处理应用程序菜单
//  WM_PAINT    - 绘制主窗口
//  WM_DESTROY  - 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 分析菜单选择:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hwnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hwnd);
                break;
            default:
                return DefWindowProc(hwnd, message, wParam, lParam);
            }
        }
        break;
	case WM_CLOSE:
		//所有xxxWindow为结尾的方法，都不会进入到消息队列中，而是直接执行(OS->窗口过程)。
		DestroyWindow(hwnd);// 发送另一个消息 WM_DESTROY
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
    case WM_PAINT:
        {
		PAINTSTRUCT ps;//绘图结构体
		HDC hdc = BeginPaint(hwnd, &ps);
		TextOut(hdc, 100, 100, TEXT("hello"), strlen("hello"));
		EndPaint(hwnd, &ps);
        }
        break;
	case WM_LBUTTONDOWN://鼠标左键按下。
	{
		int xPos = LOWORD(lParam);
		int yPos = HIWORD(lParam);
		char buf[1024];
		wsprintf((LPWSTR)buf, TEXT("x = %d,y = %d"), xPos, yPos);
		MessageBox(hwnd, (LPWSTR)buf, TEXT("鼠标左键按下"), MB_OK);
		break;
	}
	case WM_KEYDOWN://键盘
	{
		MessageBox(hwnd, TEXT("键盘按下"), TEXT("键盘按下"), MB_OK);
		break;
	}
	
    default:
        return DefWindowProc(hwnd, message, wParam, lParam);
    }
    return 0;
}

// “关于”框的消息处理程序。
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;


    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
/*
#include <iostream>
using namespace std;
#include<stdio.h>
#include<Windows.h>
#include<stdlib.h>

LRESULT CALLBACK WindowProc(
	HWND hwnd,//消息所属的窗口句柄
	UINT uMsg,//具体消息名称
	WPARAM wParam,// 键盘附加消息
	LPARAM lParam) //鼠标附加消息
{
	/*
	CALLBACK _stdcall
	
switch (uMsg)
{
case WM_CLOSE:
	DestroyWindow(hwnd);// 发送另一个消息 WM_DESTROY
	break;
case WM_DESTROY:
	PostQuitMessage(0);
	break;
case WM_LBUTTONDOWN://鼠标左键按下。
{
	int xPos = LOWORD(lParam);
	int yPos = HIWORD(lParam);
	char buf[1024];

	wsprintf((LPWSTR)buf, TEXT("x = %d,y = %d"), xPos, yPos);

	MessageBox(hwnd, (LPWSTR)buf, TEXT("鼠标左键按下"), MB_OK);

	break;
}
case WM_KEYDOWN://键盘
{
	MessageBox(hwnd, TEXT("键盘按下"), TEXT("键盘按下"), MB_OK);

	break;
}
case WM_PAINT://绘图
{
	PAINTSTRUCT ps;//绘图结构体
	HDC hdc = BeginPaint(hwnd, &ps);

	TextOut(hdc, 100, 100, TEXT("hello"), strlen("hello"));
	EndPaint(hwnd, &ps);


}
default:
	break;

}
//返回值用默认处理方式
return DefWindowProc(hwnd, uMsg, wParam, lParam);

}//WINAPI代表 _stdcall 参数的传递顺序，从右到左  以此入栈 ，并且在函数返回前 清空堆栈

int WINAPI main(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nShowCmd) {
	WNDCLASS wc;
	wc.cbClsExtra = 0;//类的额外的内存
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);//设置背景。
	wc.hCursor = LoadCursor(NULL, IDC_HAND);//设置光标,第一个参数为NULL，使用默认光标
	wc.hIcon = LoadIcon(NULL, IDI_ERROR);//图标
	wc.hInstance = hInstance;
	wc.lpfnWndProc = WindowProc;//回调函数,函数名，是自己定义并实现的。
	wc.lpszClassName = TEXT("WIN");
	wc.lpszMenuName = NULL;//菜单名称
	wc.style = 0;//默认风格

	RegisterClass(&wc);

	HWND hwnd = CreateWindow(wc.lpszClassName, TEXT("WINDOWS"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);
	ShowWindow(hwnd, SW_SHOWNORMAL);
	UpdateWindow(hwnd);
	//通过循环获取消息
	/*
	 HWND 主窗口句柄
	 UINT message 具体消息名称
	 WPARAN wParam 附加消息；
	 LPARAN LParam
	 DWORD time
	 POINT	pt
	
	MSG msg;
	while (true)
	{	/*
			lpmsg,
			hwnd, null代表捕获所有窗口。
			wMsgFilterMin,0代表捕获所有消息。
			wMsgFilterMax
		
		if (GetMessage(&msg, NULL, 0, 0) == FALSE) {
			break;
		}

		//翻译消息
		TranslateMessage(&msg);

		DispatchMessage(&msg);

	}
	return 0;

}

*/