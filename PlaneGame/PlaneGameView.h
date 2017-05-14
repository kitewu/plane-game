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
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
public:
	virtual ~CPlaneGameView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
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
	static const int win_height = 720; //窗口高
	static const int win_width = 1000; //窗口宽
	static bool begin;//控制是否开始开关
	static bool stop;//控制是否暂停开关
	static bool die;// 控制是否死亡开关
	static bool win;//控制是否胜利开关
	static bool init;//游戏开始开关
	static int nflag;//控制技能数量
	static int grade; //级别
	static int killnum;//杀敌数
	static int score;// 分数
	static int energy;//生命值
	static int num1;// 控制音乐循环播放
	static int num2;//控制防护罩消失
	static int bossenergy;//boss生命值
	static int flag;//控制我机子弹拐弯飞行参数
	static int sscore;//控制分数升级参数
	static int modelparam; //普通和无敌模式

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
	CObList jnlist;//技能链表;
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

#ifndef _DEBUG  // PlaneGameView.cpp 中的调试版本
inline CPlaneGameDoc* CPlaneGameView::GetDocument() const
   { return reinterpret_cast<CPlaneGameDoc*>(m_pDocument); }
#endif

