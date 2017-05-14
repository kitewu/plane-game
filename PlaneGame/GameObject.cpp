#include "stdafx.h"
#include "GameObject.h"

GameObject::GameObject() : pos(0)
{
	width = 0; //宽度
	height = 0; //高度
	speed = 0;  //速度
}

GameObject::~GameObject()
{
}

//获取位置点
CPoint GameObject::Pos()  
{
	return pos;
}
//获取x
int GameObject::Posx()   
{
	return pos.x;
}
// 获取y
int GameObject::Posy()   
{
	return pos.y;
}


//修改x
void GameObject::Posx(int xx) 
{
	pos.x = xx;
}
//修改y
void GameObject::Posy(int yy) 
{
	pos.y = yy;
}
//修改xy坐标
void GameObject::Pos(int xx, int yy) 
{
	pos.x = xx;
	pos.y = yy;
}
//修改xy坐标
void GameObject::Pos(CPoint point) 
{
	pos = point;
}

//获取矩形区域
CRect GameObject::getRect()
{
	return CRect(Pos().x, Pos().y, Pos().x + Width(), Pos().y + Height());
}
//修改大小
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
//修改速度
void GameObject::Speed(int ss)
{
	speed = ss;
}
int GameObject::Speed()
{
	return speed;
}