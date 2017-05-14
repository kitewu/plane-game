#include "stdafx.h"
#include "EnemyBullets.h"

EnemyBullets::EnemyBullets() : type(0){
	Width(8);
	Height(8);
	Pos(0);
	Speed(8);
}

EnemyBullets::~EnemyBullets(){
}

//¼ÓÔØÍ¼Æ¬
bool EnemyBullets::LoadImage(CDC* pDC){
	if (type == 0 || type == 1){
		CDC memDC;
		memDC.CreateCompatibleDC(pDC);
		CBitmap bmpDraw;
		bmpDraw.LoadBitmap(IDB_ENEMYBULLET);
		CBitmap* pbmpOld = memDC.SelectObject(&bmpDraw);
		pDC->TransparentBlt(Posx(), Posy(), Width(), Height(), &memDC, 0, 0, Width(), Height(), RGB(0, 0, 0));
	}
	else if (type == 2){
		CDC memDC;
		memDC.CreateCompatibleDC(pDC);
		CBitmap bmpDraw;
		bmpDraw.LoadBitmap(IDB_ENEMYBULLET2);
		CBitmap* pbmpOld = memDC.SelectObject(&bmpDraw);
		pDC->TransparentBlt(Posx(), Posy(), Width(), Height(), &memDC, 0, 0, Width(), Height(), RGB(0, 0, 0));
	}
	else if (type == 3){
		CDC memDC;
		memDC.CreateCompatibleDC(pDC);
		CBitmap bmpDraw;
		bmpDraw.LoadBitmap(IDB_ENEMYBULLETJG);
		CBitmap* pbmpOld = memDC.SelectObject(&bmpDraw);
		pDC->TransparentBlt(Posx(), Posy(), Width(), Height(), &memDC, 0, 0, Width(), Height(), RGB(0, 0, 0));
	}
	return false;
}
int EnemyBullets::Dir()
{
	return dir;
}
void EnemyBullets::Dir(int d)
{
	dir = d;
}
int EnemyBullets::Type()
{
	return type;
}

void EnemyBullets::Type(int t)
{
	type = t;
}