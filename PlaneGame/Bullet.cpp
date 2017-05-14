#include "stdafx.h"
#include "Bullet.h"

bool Bullet::uss = false;

Bullet::Bullet():dir(0),type(0){
	Pos(0, 0);
	Speed(12);
	Width(10);
	Height(20);
}

Bullet::~Bullet(){
}

bool Bullet::LoadImage(CDC* pDC)
{
	if (type == 0){
		CDC memDC;
		memDC.CreateCompatibleDC(pDC);
		CBitmap bmpDraw;
		bmpDraw.LoadBitmap(IDB_BULLET);
		CBitmap* pbmpOld = memDC.SelectObject(&bmpDraw);
		pDC->TransparentBlt(Posx(), Posy(), Width(), Height(), &memDC, 0, 0, Width(), Height(), RGB(0, 0, 0));
	}
	else if (type == 1){
		CDC memDC;
		memDC.CreateCompatibleDC(pDC);
		CBitmap bmpDraw;
		bmpDraw.LoadBitmap(IDB_BULLETS);
		CBitmap* pbmpOld = memDC.SelectObject(&bmpDraw);
		pDC->TransparentBlt(Posx(), Posy(), Width(), Height(), &memDC, 0, 0, Width(), Height(), RGB(255, 255, 255));
	}
	else if (type == 2){
		CDC memDC;
		memDC.CreateCompatibleDC(pDC);
		CBitmap bmpDraw;
		bmpDraw.LoadBitmap(IDB_BULLET2);
		CBitmap* pbmpOld = memDC.SelectObject(&bmpDraw);
		pDC->TransparentBlt(Posx(), Posy(), Width(), Height()-50, &memDC, 0, 0, Width(), Height(), RGB(255, 255, 255));
	}
	return false;
}

int Bullet::Dir()
{
	return dir;
}
void Bullet::Dir(int d)
{
	dir = d;
}
int Bullet::Type()
{
	return type;
}

void Bullet::Type(int t)
{
	type = t;
}
bool Bullet::Uss()
{
	return uss;
}
void Bullet::Uss(bool u)
{
	uss = u;
}