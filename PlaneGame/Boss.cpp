#include "stdafx.h"
#include "Boss.h"
CImageList Boss::imagelist;
Boss::Boss() : isuse(false),dir(1){
	Pos(250,0);
	Speed(12);
	Width(190);
	Height(122);
}
Boss::~Boss()
{
}
//是否出现接口
bool Boss::Isuse(){
	return isuse;
}
void Boss::Isuse(bool is){
	isuse = is;
}

bool Boss::LoadImage(CDC* pDC)
{
	imagelist.Draw(pDC, 0, Pos(), NULL);
	return false;
}

bool Boss::Loadimage()
{
	imagelist.Create(190, 122, ILC_COLOR24 | ILC_MASK, 1, 1);
	CBitmap bitmap;
	bitmap.LoadBitmapW(IDB_BOSS);
	imagelist.Add(&bitmap, RGB(0, 0, 0));
	return false;
}
int Boss::Dir()
{
	return dir;
}
void Boss::Dir(int d)
{
	dir = d;
}