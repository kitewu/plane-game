#pragma once
#include "GameObject.h"
#include "resource.h"
class People :
	public GameObject
{
public:
	People();
	~People();
	static CImageList imagelist;
	bool LoadImage(CDC* pDC);
	static bool Loadimage();
};

