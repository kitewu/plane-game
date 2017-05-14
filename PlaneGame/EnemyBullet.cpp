#include "stdafx.h"
#include "EnemyBullet.h"


EnemyBullet::EnemyBullet()
{
}


EnemyBullet::~EnemyBullet()
{
}
void EnemyBullet::LoadImage(CDC* pDC)
{
	//¼ÓÔØÍ¼Æ¬
	CBrush b(RGB(255, 255, 0));
	pDC->SelectObject(&b);
	pDC->Ellipse(pos.x + EnemyBullet::wei / 2 - 5, pos.y, pos.x + EnemyBullet::wei / 2 + 5, pos.y + 10);

}

CRect EnemyBullet::getrect()
{
	return CRect(pos.x,pos.y,pos.x+wei,pos.y+hei);
}
