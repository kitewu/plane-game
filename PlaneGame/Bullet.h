#pragma once
#include "GameObject.h"
#include "resource.h"
class Bullet :
	public GameObject
{
public:
	Bullet();
	~Bullet();
	bool LoadImage(CDC* pDC);
	int Type();
	void Type(int);
	int Dir();
	void Dir(int);
	static bool Uss();
	static void Uss(bool);
private:
	int type;
	int dir;
	static bool uss; //使用第二种子弹
};

