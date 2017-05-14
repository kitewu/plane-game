#pragma once
#include "afx.h"
class GameObject :
	public CObject
{
public:
	GameObject();
	~GameObject();
	virtual bool LoadImage(CDC* pDC) = 0;
	//获取位置点
	CPoint Pos();  
	int Posx();
	int Posy();
	//修改位置
	void Posx(int); 
	void Posy(int);
	void Pos(int, int);
	void Pos(CPoint); 

	//获取矩形区域
	CRect getRect();

	//修改大小
	void Width(int);
	void Height(int);
	//获取大小
	int Width();
	int Height();

	//获取速度
	int Speed();
	//修改速度
	void Speed(int);
private:
	CPoint pos; //位置
	int width;  //宽度
	int height; //高度
	int speed;  //速度
};

