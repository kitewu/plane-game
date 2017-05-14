#pragma once
#include "resource.h"
#include "GameObject.h"

class EnemyPlane :
	public GameObject
{
public:
	EnemyPlane();
	~EnemyPlane();

	bool LoadImage(CDC* pDC);

	int Dir();
	void Dir(int);
	int Type();
	void Type(int);
private:
	int dir;
	int type;
};

