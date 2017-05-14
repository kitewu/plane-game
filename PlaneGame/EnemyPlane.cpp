#include "stdafx.h"
#include "EnemyPlane.h"
EnemyPlane::EnemyPlane():dir(0),type(0){
	Pos(0, 0);
	Speed(0);
	Width(35);
	Height(35);
}

EnemyPlane::~EnemyPlane()
{
}
bool EnemyPlane::LoadImage(CDC* pDC)
{
	CDC memDC;
	memDC.CreateCompatibleDC(pDC);
	CBitmap bmpDraw;
	if (type == 0){
		bmpDraw.LoadBitmap(IDB_ENEMYPLANE1);
		CBitmap* pbmpOld = memDC.SelectObject(&bmpDraw);
		pDC->TransparentBlt(Posx(), Posy(), Width(), Height(), &memDC, 0,0, Width(), Height(), RGB(0, 0, 0));
	}
	else if (type == 1){
		bmpDraw.LoadBitmap(IDB_ENEMYPLANE2);
		CBitmap* pbmpOld = memDC.SelectObject(&bmpDraw);
		pDC->TransparentBlt(Posx(), Posy(), Width(), Height(), &memDC, 0,0, Width(), Height(), RGB(0, 0, 0));
	}
	else if (type == 2){
		bmpDraw.LoadBitmap(IDB_ENEMYPLANE3);
		CBitmap* pbmpOld = memDC.SelectObject(&bmpDraw);
		pDC->TransparentBlt(Posx(), Posy(), Width(), Height(), &memDC, 0, 0, Width(), Height(), RGB(255, 0, 0));
	}
	else if (type == 3){
		bmpDraw.LoadBitmap(IDB_UFO);
		CBitmap* pbmpOld = memDC.SelectObject(&bmpDraw);
		pDC->TransparentBlt(Posx(), Posy(), Width(), Height(), &memDC, 0, 0, Width(), Height(), RGB(255, 255, 255));
	}
	return false;
}
int EnemyPlane::Dir()
{
	return dir;
}
void EnemyPlane::Dir(int d)
{
	dir = d;
}

int EnemyPlane::Type()
{
	return type;
}

void EnemyPlane::Type(int t)
{
	type = t;
}