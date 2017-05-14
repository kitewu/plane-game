#pragma once
#include "GameObject.h"
class Skill : 
	public GameObject
{
public:
	Skill();
	~Skill();

	bool Isuse();
	void Isuse(bool);

	static CImageList imagelist;
	bool LoadImage(CDC* pDC);
	static bool Loadimage();
private:
	bool isuse;//øÿ÷∆¥Û’–
};

