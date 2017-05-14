#pragma once
#include "afx.h"
#include "atltypes.h"
#include "afxwin.h"
#include "GameObject.h"
class Protected :
	public GameObject
{
public:
	Protected();
	virtual ~Protected();

	static CImageList imagelist;
	bool LoadImage(CDC* pDC);
	static bool Loadimage();

	bool Isuse();
	void Isuse(bool);
	int index;
private:
	bool isuse;
	
};
