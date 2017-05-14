#pragma once
#include "GameObject.h"
#include "resource.h"
class Oil :
	public GameObject
{
public:
	Oil();
	~Oil();
	static CImageList imagelist;
	bool LoadImage(CDC* pDC);
	static bool Loadimage();
};

