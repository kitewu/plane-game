#include "stdafx.h"
#include "MyPlane.h"
CImageList MyPlane::imagelist;
MyPlane::MyPlane() : bullettype(0) , isuse(false) {
	Pos(450,550);
	Speed(12);
	Width(50);
	Height(60);
}

MyPlane::~MyPlane()
{
}
bool MyPlane::LoadImage(CDC* pDC)
{
	imagelist.Draw(pDC, 0, Pos(), NULL);
	return false;
}

bool MyPlane::Loadimage()
{
	imagelist.Create(50, 60, ILC_COLOR24 | ILC_MASK, 1, 1);
	CBitmap bitmap;
	bitmap.LoadBitmapW(IDB_ME);
	imagelist.Add(&bitmap, RGB(0, 0, 0));
	return false;
}
//是否出现接口
bool MyPlane::Isuse(){
	return isuse;
}
void MyPlane::Isuse(bool is){
	isuse = is;
}