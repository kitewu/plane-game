#include "stdafx.h"
#include "Air.h"
CImageList Air::imagelist;
bool Air::isuse = true;
Air::Air(){
	Pos(0, 100);
	Speed(8);
	Width(189);
	Height(189);
}

Air::~Air()
{
}
bool Air::LoadImage(CDC* pDC)
{
	imagelist.Draw(pDC, 0, Pos(), NULL);
	return false;
}

bool Air::Loadimage()
{
	imagelist.Create(189, 189, ILC_COLOR24 | ILC_MASK, 1, 1);
	CBitmap bitmap;
	bitmap.LoadBitmapW(IDB_AIR);
	imagelist.Add(&bitmap, RGB(0, 0, 0));
	return false;
}
//是否出现接口
bool Air::Isuse(){
	return isuse;
}
void Air::Isuse(bool is){
	isuse = is;
}

//bool Bomb::LoadImage(CDC* pDC)
//{
//	CDC memDC;
//	memDC.CreateCompatibleDC(pDC);
//	CBitmap bmpDraw;
//	bmpDraw.LoadBitmap(IDB_BOMB);
//	CBitmap* pbmpOld = memDC.SelectObject(&bmpDraw);
//	pDC->TransparentBlt(0, 0, Width(), Height(), &memDC, 0, 0, Width(), Height(), RGB(0, 0, 0));
//	return false;
//}