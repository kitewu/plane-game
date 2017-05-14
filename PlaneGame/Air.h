#pragma once
#include "GameObject.h"
#include "resource.h"
class Air :
	public GameObject
{
public:
	Air();
	~Air();
	static CImageList imagelist;
	bool LoadImage(CDC* pDC);
	static bool Loadimage();
	static bool Isuse();
	static void Isuse(bool);
private:
	static bool isuse;  // «∑Ò π”√
};
