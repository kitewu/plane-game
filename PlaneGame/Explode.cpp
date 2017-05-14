
#include "stdafx.h"
#include "Explode.h"
#include "Resource.h"
CImageList Explode::imagelist;
Explode::Explode()
	:index(0)
	{ Pos(0,0);
}

Explode::~Explode()
{
}


// ªÊ÷∆±¨’®
bool Explode::LoadImage(CDC* pDC)
{
	imagelist.Draw(pDC, index++, Pos(), NULL);
	if (index <= 8){
		return true;
	}
	return false;
}
bool Explode::Loadimage(void)
{
	imagelist.Create(66, 66, ILC_COLOR24 | ILC_MASK, 1, 1);
	CBitmap bitmap;
	bitmap.LoadBitmapW(IDB_BOOM);
	imagelist.Add(&bitmap, RGB(0, 0, 0));//∞—Õº∆¨∞¥≥ﬂ¥Á≤ø™
	return false;
}