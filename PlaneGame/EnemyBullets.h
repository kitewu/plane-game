#pragma once
#include "GameObject.h"
#include "resource.h"
class EnemyBullets :
	public GameObject
{
public:
	EnemyBullets();
	~EnemyBullets();
	bool LoadImage(CDC* pDC);  //º”‘ÿÕº∆¨
	int Dir();
	void Dir(int);
	int Type();
	void Type(int);
private:
	int dir;
	int type;
};

