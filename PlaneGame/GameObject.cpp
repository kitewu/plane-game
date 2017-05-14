#include "stdafx.h"
#include "GameObject.h"

GameObject::GameObject() : pos(0)
{
	width = 0; //���
	height = 0; //�߶�
	speed = 0;  //�ٶ�
}

GameObject::~GameObject()
{
}

//��ȡλ�õ�
CPoint GameObject::Pos()  
{
	return pos;
}
//��ȡx
int GameObject::Posx()   
{
	return pos.x;
}
// ��ȡy
int GameObject::Posy()   
{
	return pos.y;
}


//�޸�x
void GameObject::Posx(int xx) 
{
	pos.x = xx;
}
//�޸�y
void GameObject::Posy(int yy) 
{
	pos.y = yy;
}
//�޸�xy����
void GameObject::Pos(int xx, int yy) 
{
	pos.x = xx;
	pos.y = yy;
}
//�޸�xy����
void GameObject::Pos(CPoint point) 
{
	pos = point;
}

//��ȡ��������
CRect GameObject::getRect()
{
	return CRect(Pos().x, Pos().y, Pos().x + Width(), Pos().y + Height());
}
//�޸Ĵ�С
int GameObject::Width()
{
	return width;
}
int GameObject::Height()
{
	return height;
}
void GameObject::Height(int hh)
{
	height = hh;
}
void GameObject::Width(int ww)
{
	width = ww;
}
//�޸��ٶ�
void GameObject::Speed(int ss)
{
	speed = ss;
}
int GameObject::Speed()
{
	return speed;
}