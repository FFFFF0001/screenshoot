#include "screen.h"

HDC					mem_dc;
SIZE				screen_size;

void 
screen_caption(){

	HDC desk_dc = CreateDC(L"DISPLAY", 0, 0, 0);		// �����豸���

	mem_dc = CreateCompatibleDC(desk_dc);				// ������desk_dc����ݵ���ʱ����hdc

	screen_size.cx = GetDeviceCaps(desk_dc, HORZRES);	// ˮƽ�ֱ���Ϊ��

	screen_size.cy = GetDeviceCaps(desk_dc, VERTRES);	// ��ֱ�ֱ���Ϊ��

	HBITMAP hBmp = CreateCompatibleBitmap(desk_dc, screen_size.cx, screen_size.cy);	//��������

	SelectObject(mem_dc, hBmp);							//��������mem_dc��

	BitBlt(mem_dc, 0, 0, screen_size.cx, screen_size.cy, desk_dc, 0, 0, SRCCOPY);

}

