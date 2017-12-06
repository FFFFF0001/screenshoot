/**********************************************
               Editor:Joezeo			                       
          E-mail:joezeo@outlook.com                  
            Date:2017/12/6/18/31     
**********************************************/
#include <windows.h>
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
int WINAPI WinMain(HINSTANCE hInstance,
				   HINSTANCE hPrevInstance, 
				   LPSTR	 lpCmdLine,
				   int		 nShowCmd)
{
	static char szWndClassName[] = "hellowin";
	HWND hwnd;
	MSG msg;
	WNDCLASS wndclass;

	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szWndClassName;

	if (!RegisterClass(&wndclass)) {
		MessageBox(NULL, "ע��ʧ��", "����", MB_ICONERROR);
		return 0;
	}

	hwnd = CreateWindow(
		szWndClassName,		//windows class name
		"Joezeo",			//windows caption	
		WS_OVERLAPPEDWINDOW,//windows style
		CW_USEDEFAULT,		//intial x position
		CW_USEDEFAULT,		//intial y position
		CW_USEDEFAULT,		//intial x size
		CW_USEDEFAULT,		//intial y size
		NULL,				//parent wnidow handle
		NULL,				//window menu handle
		hInstance,			//program instance handle
		NULL);				//creation paramenter
	ShowWindow(hwnd, nShowCmd);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, 
							WPARAM wparam,LPARAM lparam) {
	HDC hdc;		//�豸���������
	PAINTSTRUCT ps;
	RECT rect;

	switch (message) {
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		GetClientRect(hwnd, &rect);
		EndPaint(hwnd, &ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, message, wparam, lparam);
}