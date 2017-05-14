#pragma once
#include "resource.h"
#include "GameObject.h"

class BackGround : public GameObject
{
public:
	BackGround();
	~BackGround();
	bool LoadImage(CDC* pDC);
	void Draw(CDC*);
private:
	const int s_begin_width = 1024;
	const int s_begin_height = 768;
	const int s_end_width = 1280;
	const int s_end_height = 720;
};