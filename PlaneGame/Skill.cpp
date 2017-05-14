#include "stdafx.h"
#include "Skill.h"
#include "resource.h"

CImageList Skill::imagelist;

Skill::Skill():isuse(false){
	Pos(0,600);
	Speed(0);
	Width(44);
	Height(161);
}

Skill::~Skill(){
}

bool Skill::Isuse(){
	return isuse;
}

void Skill::Isuse(bool is){
	isuse = is;
}

bool Skill::LoadImage(CDC* pDC){
	imagelist.Draw(pDC, 0, Pos(), NULL);
	return false;
}

bool Skill::Loadimage(){
	imagelist.Create(44, 161, ILC_COLOR24 | ILC_MASK, 1, 1);
	CBitmap bitmap;
	bitmap.LoadBitmapW(IDB_SKILLS);
	imagelist.Add(&bitmap, RGB(255, 255,255));
	return false;
}