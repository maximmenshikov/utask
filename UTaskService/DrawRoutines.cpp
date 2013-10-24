#include "stdafx.h"

// Drawing image (hbm) on HDC with alpha blending and stretching
VOID DrawImage(HDC hdc, HBITMAP hbm, int x, int y, int width, int height, int origWidth, int origHeight)
{
	HDC imgDC = CreateCompatibleDC(hdc);
	HBITMAP oldHbm = (HBITMAP)SelectObject(imgDC, hbm);

	BLENDFUNCTION bf;
	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.SourceConstantAlpha = 0xFF;
	bf.AlphaFormat = AC_SRC_ALPHA;
	
	AlphaBlend(hdc, x, y, 
				width, height, imgDC, 0, 
				0, origWidth, origHeight, bf);

	SelectObject(imgDC, oldHbm);
	DeleteDC(imgDC);
};


// Drawing image (hbm) on HDC with alpha blending
VOID DrawImage(HDC hdc, HBITMAP hbm, int x, int y, int width, int height)
{
	HDC imgDC = CreateCompatibleDC(hdc);
	HBITMAP oldHbm = (HBITMAP)SelectObject(imgDC, hbm);

	BLENDFUNCTION bf;
	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.SourceConstantAlpha = 0xFF;
	bf.AlphaFormat = AC_SRC_ALPHA;

	AlphaBlend(hdc, x, y, 
		width, height, imgDC, 0, 
		0, width, height, bf);

	SelectObject(imgDC, oldHbm);
	DeleteDC(imgDC);
};

