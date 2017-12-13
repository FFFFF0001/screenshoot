#include "screen.h"
SIZE screen_size;

HDC 
screen_caption(){
	HDC desk_dc = CreateDC(L"DISPLAY", 0, 0, 0);	// �����豸���
	HDC mem_dc = CreateCompatibleDC(desk_dc);		// ������desk_dc����ݵ���ʱ����hdc
	screen_size.cx = GetDeviceCaps(desk_dc, HORZRES);	// ˮƽ�ֱ���Ϊ��
	screen_size.cy = GetDeviceCaps(desk_dc, VERTRES);	// ��ֱ�ֱ���Ϊ��
	HBITMAP hBmp = CreateCompatibleBitmap(desk_dc, screen_size.cx, screen_size.cy);	//������desk_dc����ݵĻ���handle

	SelectObject(mem_dc, hBmp);
	BitBlt(mem_dc, 0, 0, screen_size.cx, screen_size.cy, desk_dc, 0, 0, SRCCOPY);
	return mem_dc;
}

void 
create_sreenshoot_window(HINSTANCE hInstance) {
	static char szWndClassName[] = "screenWnd";
	static HWND hwnd;
	static MSG msg;
	static WNDCLASS wndclass;

	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = ScreenProc;
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
		"",					//windows caption	
		WS_POPUP,			//windows style		ȫ���ް�ť�� WS_POPUP
		CW_USEDEFAULT,		//intial x position
		CW_USEDEFAULT,		//intial y position
		CW_USEDEFAULT,			//intial x size
		CW_USEDEFAULT,			//intial y size
		NULL,				//parent wnidow handle
		NULL,				// window menu handle
		hInstance,			//program instance handle
		NULL);				//creation paramenter

	ShowWindow(hwnd, SW_MAXIMIZE); // ȫ������ SW_MAXIMIZE
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

LRESULT CALLBACK 
ScreenProc(HWND hwnd, UINT message,
			WPARAM wparam, LPARAM lparam) {
	HDC hdc, memdc;		//�豸��������
	PAINTSTRUCT ps;
	RECT rect;

	switch (message) {
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		memdc = screen_caption();
		GetClientRect(hwnd, &rect);
		BitBlt(hdc, 0, 0, screen_size.cx, screen_size.cy, memdc, 0, 0, SRCCOPY);
		EndPaint(hwnd, &ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, message, wparam, lparam);
}