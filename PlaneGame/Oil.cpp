#include "stdafx.h"
#include "Oil.h"

CImageList Oil::imagelist;

Oil::Oil()
{
	Pos(0, 0);
	Speed(8);
	Width(50);
	Height(37);
}

Oil::~Oil()
{
}

bool Oil::LoadImage(CDC* pDC){
	imagelist.Draw(pDC, 0, Pos(), NULL);
	return false;
}

bool Oil::Loadimage(){
	imagelist.Create(50, 37, ILC_COLOR24 | ILC_MASK, 1, 1);
	CBitmap bitmap;
	bitmap.LoadBitmapW(IDB_OIL);
	imagelist.Add(&bitmap, RGB(0,0, 0));
	return false;
}
