#include "stdafx.h"
#include "BackGround.h"
#include "PlaneGameView.h"
#include "Air.h"
BackGround::BackGround(){
	Pos(0,0);
	Speed(0);
	Width(1440);
	Height(900);
}
BackGround::~BackGround(){
}
bool BackGround::LoadImage(CDC* pDC)
{
	CDC memDC;
	memDC.CreateCompatibleDC(pDC);
	CBitmap bmpDraw;

	if (CPlaneGameView::init == true){
		bmpDraw.LoadBitmap(IDB_BEGIN);
		CBitmap* pbmpOld = memDC.SelectObject(&bmpDraw);
		pDC->TransparentBlt(0, 0, s_begin_width, s_begin_height, &memDC, 0, 0, s_begin_width, s_begin_height, RGB(0, 0, 0));
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(255,255,255));
		pDC->TextOutW(320, 320, L"��Enter����ʼ��Ϸ");
	}
	else{
		if (CPlaneGameView::die == true){
			bmpDraw.LoadBitmap(IDB_OVER);
			CBitmap* pbmpOld = memDC.SelectObject(&bmpDraw);
			pDC->TransparentBlt(-70, -50, s_end_width, s_end_height, &memDC, 0, 0, 1280, 720, RGB(255, 255, 255));
		}
		else{
			bmpDraw.LoadBitmap(IDB_BACKG);
			CBitmap* pbmpOld = memDC.SelectObject(&bmpDraw);
			pDC->TransparentBlt(Pos().x, Pos().y, Width(), Height(), &memDC, Pos().x, Pos().y, Width(), Height(), RGB(255, 255, 255));
			Draw(pDC);
			if (CPlaneGameView::stop == true){
				pDC->SetBkMode(TRANSPARENT);
				pDC->SetTextColor(RGB(255, 255, 255));
				pDC->TextOutW(20, 20, L"��ͣ");
			}
		}
	}
	return false;
}
void BackGround::Draw(CDC* pDC){
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(RGB(0, 0, 0));

	int n = CPlaneGameView::grade;
	CString str;
	str.Format(_T("%d"), n);
	pDC->TextOutW(10, 10, L"�ȼ�: ");
	pDC->TextOutW(100, 10, str);

	n = CPlaneGameView::killnum;
	str.Format(_T("%d"), n);
	pDC->TextOutW(10, 30, L"������: ");
	pDC->TextOutW(100, 30, str);

	n = CPlaneGameView::score;
	str.Format(_T("%d"), n);
	pDC->TextOutW(10, 50, L"��ǰ�÷�:");
	pDC->TextOutW(100, 50, str);

	n = CPlaneGameView::energy;
	str.Format(_T("%d"), n);
	pDC->TextOutW(10, 70, L"ʣ������ֵ:");
	pDC->TextOutW(100, 70, str);

	pDC->TextOutW(CPlaneGameView::win_width - 140, 15, L"��ɱ:");

	if (Air::Isuse() == true)
		pDC->TextOutW(300, 100, L"�ͻ�����");
}