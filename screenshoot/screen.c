#include "screen.h"
SIZE screen_size;

void 
screen_caption(HDC hdc){

	HDC desk_dc = CreateDC("DISPLAY", 0, 0, 0);	// �����豸���

	HDC mem_dc = CreateCompatibleDC(desk_dc);		// ������desk_dc����ݵ���ʱ����hdc


	screen_size.cx = GetDeviceCaps(desk_dc, HORZRES);	// ˮƽ�ֱ���Ϊ��

	screen_size.cy = GetDeviceCaps(desk_dc, VERTRES);	// ��ֱ�ֱ���Ϊ��


	HBITMAP hBmp = CreateCompatibleBitmap(desk_dc, screen_size.cx, screen_size.cy);	//������desk_dc����ݵĻ���handle


	SelectObject(mem_dc, hBmp);

	BitBlt(mem_dc, 0, 0, screen_size.cx, screen_size.cy, desk_dc, 0, 0, SRCCOPY);

	BitBlt(hdc, 0, 0, screen_size.cx, screen_size.cy, mem_dc, 0, 0, SRCCOPY);

}

