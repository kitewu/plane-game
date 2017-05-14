#pragma once
#include "GameObject.h"
#include "resource.h"
class Help :
	public GameObject
{
public:
	Help();
	~Help();
	int Type();
	void Type(int);
	bool LoadImage(CDC* pDC);
private:
	int type;
};

