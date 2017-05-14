#pragma once
#include "afx.h"
#include "atltypes.h"
#include "afxwin.h"
#include "GameObject.h"
class Explode :
	public GameObject
{
public:
	Explode();
	virtual ~Explode();

	static CImageList imagelist;
	bool LoadImage(CDC* pDC);
	static bool Loadimage();
private:
	int index;
};