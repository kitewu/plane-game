#include "stdafx.h"
#include "People.h"

CImageList People::imagelist;

People::People()
{
	Pos(0, 0);
	Speed(12);
	Width(21);
	Height(41);
}


People::~People()
{
}

bool People::LoadImage(CDC* pDC)
{
	imagelist.Draw(pDC, 0, Pos(), NULL);
	return false;
}

bool People::Loadimage()
{
	imagelist.Create(21, 41, ILC_COLOR24 | ILC_MASK, 1, 1);
	CBitmap bitmap;
	bitmap.LoadBitmapW(IDB_PEO);
	imagelist.Add(&bitmap, RGB(255, 255, 255));
	return false;
}