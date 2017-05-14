#pragma once
#include "afx.h"
#include "atltypes.h"
#include "GameObject.h"
#include "resource.h"

class Boss : public GameObject
{
public:
	Boss();
	~Boss();
	static CImageList imagelist;
	bool LoadImage(CDC* pDC);
	static bool Loadimage();
	bool Isuse();
	void Isuse(bool);
	int Dir();
	void Dir(int);
private:
	bool isuse;  // «∑Ò π”√
	int dir;
};

