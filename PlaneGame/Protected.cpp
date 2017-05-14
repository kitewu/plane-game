#include "stdafx.h"
#include "Protected.h"
#include "Resource.h"
CImageList Protected::imagelist;
Protected::Protected()
	:isuse(false), index(0)
{
	Pos(10, 10);
	Width(128);
	Height(128);
	Speed(14);
}

Protected::~Protected()
{
}


bool Protected::LoadImage(CDC* pDC){
	imagelist.Draw(pDC, index++, Pos(), NULL);
	if (index <= 15){
		return true;
	}
	return false;
}

bool Protected::Loadimage(void){
	imagelist.Create(190, 118, ILC_COLOR24 | ILC_MASK, 1, 1);
	CBitmap bitmap;
	bitmap.LoadBitmapW(IDB_PROT);
	imagelist.Add(&bitmap, RGB(0, 0, 0));
	return false;
}

bool Protected::Isuse(){
	return isuse;
}

void Protected::Isuse(bool is){
	isuse = is;
}
