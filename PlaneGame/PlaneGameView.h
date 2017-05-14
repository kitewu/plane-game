#pragma once
#include "PlaneGameDoc.h"
#include "MyPlane.h"
#include "EnemyPlane.h"
#include "BackGround.h"
#include "Explode.h"
#include "EnemyBullets.h"
#include "Bullet.h"
#include "Skill.h"
#include "Boss.h"
#include "SETLEVEL.h"
#include "Air.h"
#include "Protected.h"
#include "People.h"
#include "Oil.h"
#include "Help.h"

class CPlaneGameView : public CView
{
protected: 
	CPlaneGameView();
	DECLARE_DYNCREATE(CPlaneGameView)
public:
	CPlaneGameDoc* GetDocument() const;
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
public:
	virtual ~CPlaneGameView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual void OnInitialUpdate();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnDestroy();

public:
	void Add();
	void Init();
	static const int win_height = 720; //���ڸ�
	static const int win_width = 1000; //���ڿ�
	static bool begin;//�����Ƿ�ʼ����
	static bool stop;//�����Ƿ���ͣ����
	static bool die;// �����Ƿ���������
	static bool win;//�����Ƿ�ʤ������
	static bool init;//��Ϸ��ʼ����
	static int nflag;//���Ƽ�������
	static int grade; //����
	static int killnum;//ɱ����
	static int score;// ����
	static int energy;//����ֵ
	static int num1;// ��������ѭ������
	static int num2;//���Ʒ�������ʧ
	static int bossenergy;//boss����ֵ
	static int flag;//�����һ��ӵ�������в���
	static int sscore;//���Ʒ�����������
	static int modelparam; //��ͨ���޵�ģʽ

private:
	EnemyBullets enemybullets;
	EnemyPlane enemyplane;
	Explode explode;
	MyPlane myplane;
	Skill skill;
	BackGround background;
	Bullet bullet;
	Boss boss;
	CRect rect;
	CDC MemDC;
	CBitmap MemBitmap;
	Air air;
	Protected prot;
	Oil oil;

	CObList skilllist;
	CObList jnlist;//��������;
	CObList enemybulletslist;
	CObList enemylist;
	CObList explodelist;
	CObList bulletlist;
	CObList peoplelist;
	CObList helplist;
public:
	afx_msg void Pause();
	afx_msg void Continue();
	afx_msg void NewGame();
	afx_msg void SimpleModel();
	afx_msg void SimModel();
	afx_msg void Set();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // PlaneGameView.cpp �еĵ��԰汾
inline CPlaneGameDoc* CPlaneGameView::GetDocument() const
   { return reinterpret_cast<CPlaneGameDoc*>(m_pDocument); }
#endif

