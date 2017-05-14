#include "stdafx.h"
#include "Help.h"

Help::Help() :type(0)
{
	Width(35);
	Height(53);
	Pos(0);
	Speed(0);
}


Help::~Help()
{
}

bool Help::LoadImage(CDC* pDC)
{
	if (type == 0){
		CDC memDC;
		memDC.CreateCompatibleDC(pDC);
		CBitmap bmpDraw;
		bmpDraw.LoadBitmap(IDB_BOM);
		CBitmap* pbmpOld = memDC.SelectObject(&bmpDraw);
		pDC->TransparentBlt(Posx(), Posy(), Width(), Height(), &memDC, 0, 0, Width(), Height(), RGB(0, 0, 0));
	}
	else if (type == 1){
		CDC memDC;
		memDC.CreateCompatibleDC(pDC);
		CBitmap bmpDraw;
		bmpDraw.LoadBitmap(IDB_BLOOD);
		CBitmap* pbmpOld = memDC.SelectObject(&bmpDraw);
		pDC->TransparentBlt(Posx(), Posy(), Width(), Height(), &memDC, 0, 0, Width(), Height(), RGB(0, 0, 0));
	}
	else if (type == 2){
		CDC memDC;
		memDC.CreateCompatibleDC(pDC);
		CBitmap bmpDraw;
		bmpDraw.LoadBitmap(IDB_PROH);
		CBitmap* pbmpOld = memDC.SelectObject(&bmpDraw);
		pDC->TransparentBlt(Posx(), Posy(), Width(), Height() - 50, &memDC, 0, 0, Width(), Height(), RGB(0, 0, 0));
	}
	else if (type == 3){
		CDC memDC;
		memDC.CreateCompatibleDC(pDC);
		CBitmap bmpDraw;
		bmpDraw.LoadBitmap(IDB_CLEAR);
		CBitmap* pbmpOld = memDC.SelectObject(&bmpDraw);
		pDC->TransparentBlt(Posx(), Posy(), Width(), Height() - 50, &memDC, 0, 0, Width(), Height(), RGB(0, 0, 0));
	}
	return false;
}

int Help::Type()
{
	return type;
}

void Help::Type(int t)
{
	type = t;
}