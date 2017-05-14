#include "stdafx.h"
#include "resource.h"
#include "PlaneGameDoc.h"
#include "PlaneGameView.h"
#include "PlaneGame.h"
#include "SETLEVEL.h"
#include <mmsystem.h>
#pragma comment(lib, "WINMM.LIB")//加载声音

#ifndef SHARED_HANDLERS
#endif
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
IMPLEMENT_DYNCREATE(CPlaneGameView, CView)
BEGIN_MESSAGE_MAP(CPlaneGameView, CView)
	ON_WM_KEYDOWN()
	ON_WM_TIMER()
	ON_WM_ERASEBKGND()
	ON_WM_DESTROY()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_32804, &CPlaneGameView::Pause)
	ON_COMMAND(ID_32807, &CPlaneGameView::Continue)
	ON_COMMAND(ID_32808, &CPlaneGameView::NewGame)
	ON_COMMAND(ID_32809, &CPlaneGameView::SimpleModel)
	ON_COMMAND(ID_32810, &CPlaneGameView::SimModel)
	ON_COMMAND(ID_32813, &CPlaneGameView::Set)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

int CPlaneGameView::grade = 1;
int CPlaneGameView::killnum = 0;
int CPlaneGameView::score = 0;
int CPlaneGameView::energy = 5;
bool CPlaneGameView::begin = false;
bool CPlaneGameView::stop = false;
bool CPlaneGameView::die = false;
bool CPlaneGameView::init = true;
bool CPlaneGameView::win = false;
int CPlaneGameView::bossenergy = 500;
int CPlaneGameView::flag = 0;
int CPlaneGameView::sscore = 0;
int CPlaneGameView::modelparam = 1;
int CPlaneGameView::nflag = 3;
int CPlaneGameView::num1 = 0;
int CPlaneGameView::num2 = 0;

CPlaneGameView::CPlaneGameView(){
	MemDC.CreateCompatibleDC(NULL);
	MyPlane::Loadimage();
	Skill::Loadimage();
	Explode::Loadimage();
	Boss::Loadimage();
	Air::Loadimage();
	Protected::Loadimage();
	People::Loadimage();
	Oil::Loadimage();
}

CPlaneGameView::~CPlaneGameView()
{
}

BOOL CPlaneGameView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CView::PreCreateWindow(cs);
}

void CPlaneGameView::OnDraw(CDC* pDC)
{
	CPlaneGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	POSITION it;
	MemDC.FillSolidRect(0, 0, rect.Width(), rect.Height(), RGB(255, 255, 255));	

	//加载背景
	background.LoadImage(&MemDC);
	if (begin == true){

		//加载技能
		if (skill.Isuse() == true){
			Skill *s;
			for (it = jnlist.GetHeadPosition(); it != NULL;){
				s = (Skill*)jnlist.GetNext(it);
				s->LoadImage(&MemDC);
			}
		}

		//加载客机
		POSITION pos1, pos2;
		if (air.Isuse()){
			air.LoadImage(&MemDC);
			oil.LoadImage(&MemDC);
			People *p;
			for (pos1 = peoplelist.GetHeadPosition(); (pos2 = pos1) != NULL;){
				p = (People*)peoplelist.GetNext(pos1);
				p->LoadImage(&MemDC);
			}
		}

		//加载帮助
		Help *hh;
		for (it = helplist.GetHeadPosition(); it != NULL;){
			hh = (Help*)helplist.GetNext(it);
			hh->LoadImage(&MemDC);
		}

		//加载我机
		if (myplane.Isuse())
			myplane.LoadImage(&MemDC);
		
		//加载boss
		if (boss.Isuse() == true)
			boss.LoadImage(&MemDC);

		//加载敌机
		for (it = enemylist.GetHeadPosition(); it != NULL;) {
			EnemyPlane *ep;
			ep = (EnemyPlane*)enemylist.GetNext(it);
			ep->LoadImage(&MemDC);
		}

		//加载我机子弹
		Bullet *bu;
		for (it = bulletlist.GetHeadPosition(); it != NULL;){
			bu = (Bullet*)bulletlist.GetNext(it);
			bu->LoadImage(&MemDC);
		}

		//加载技能图标
		for (it = skilllist.GetHeadPosition(); it != NULL;){
			Bullet *bu;
			bu = (Bullet*)skilllist.GetNext(it);
			bu->LoadImage(&MemDC);
		}

		// 加载敌机子弹
		for (it = enemybulletslist.GetHeadPosition(); it != NULL;){
			EnemyBullets *eb;
			eb = (EnemyBullets*)enemybulletslist.GetNext(it);
			eb->LoadImage(&MemDC);
		}

		//加载爆炸
		for (it = explodelist.GetHeadPosition(); it != NULL;){ 
			Explode *ex;
			ex = (Explode*)explodelist.GetNext(it);
			while (ex->LoadImage(&MemDC));
		}

		//加载防护
		if (prot.Isuse())
			prot.LoadImage(&MemDC);
		explodelist.RemoveAll();
	}
	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &MemDC, 0, 0, SRCCOPY);
}

#ifdef _DEBUG
void CPlaneGameView::AssertValid() const
{
	CView::AssertValid();
}

void CPlaneGameView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPlaneGameDoc* CPlaneGameView::GetDocument() const
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPlaneGameDoc)));
	return (CPlaneGameDoc*)m_pDocument;
}
#endif //_DEBUG

void CPlaneGameView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags){
	this->Invalidate();

	//进入游戏
	if (nChar == 0xD){
		if (begin == false){
			begin = true;
			stop = false;
			die = false;
			win = false;
			init = false;
			Init();
		}
	}
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CPlaneGameView::OnTimer(UINT_PTR nIDEvent)
{
	if (begin == true){   
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////刷新
		POSITION pos1, pos2,pos3,pos4;
		EnemyPlane *ep;
		Bullet *bu;
		Explode *expl;
		Skill *ss;
		EnemyBullets *eb;
		CRect crect, cr1, cr2;

		if (nIDEvent == 1) {
			//刷新我机子弹
			for (pos1 = bulletlist.GetHeadPosition(); (pos2 = pos1) != NULL;) {
				bu = (Bullet*)bulletlist.GetNext(pos1);
				if (bu->Pos().y <= -(bu->Height())){
					bulletlist.RemoveAt(pos2);
					delete bu;
				}
				else{
					if (bu->Type() == 0 || bu->Type() == 1){
						int x = (int)(sin(flag * 3.14159 / 180) * 1000);
						bu->Pos(x / 250 + bu->Posx(), bu->Pos().y - bu->Speed());
						flag++;
						if (flag == 180)
							flag = -180;
					}
					else
						bu->Pos(bu->Posx(), bu->Pos().y - bu->Speed());
				}
			}

			//刷新防护
			if (prot.Isuse()){
				prot.Pos(myplane.Posx()-65, myplane.Posy()-20);
				if (prot.index >= 15)
					prot.index = 0;
			}

			//刷新小人
			if (air.Isuse()){
				People *p;
				for (pos1 = peoplelist.GetHeadPosition(); (pos2 = pos1) != NULL;){
					p = (People*)peoplelist.GetNext(pos1);
					if (p->Posy() >= win_height){
						peoplelist.RemoveAt(pos2);
						delete p;
						score += 2;
					}
					else
						p->Posy(p->Posy() + p->Speed());
				}
			}

			//刷新敌机子弹
			for (pos1 = enemybulletslist.GetHeadPosition(); (pos2 = pos1) != NULL;) {
				eb= (EnemyBullets*)enemybulletslist.GetNext(pos1);
				if (eb->Pos().y + eb->Height() >= win_height){
					enemybulletslist.RemoveAt(pos2);
					delete eb;
				}
				else{
					if (eb->Dir() == 0){
						eb->Pos(eb->Pos().x, eb->Pos().y + eb->Speed());
					}
					if (eb->Dir() == 1){
						eb->Pos(eb->Pos().x - 3, eb->Pos().y + eb->Speed());
						if (eb->Posx() <= myplane.Posx())
							eb->Dir(2);
					}
					else if (eb->Dir() == 2){
						eb->Pos(eb->Pos().x + 3, eb->Pos().y + eb->Speed());
						if (eb->Posx() >= myplane.Posx())
							eb->Dir(1);
					}
				}
			}

			//刷新敌机
			for (pos1 = enemylist.GetHeadPosition(); (pos2 = pos1) != NULL;) {
				ep = (EnemyPlane*)enemylist.GetNext(pos1);
				if (ep->Pos().y >= win_height + ep->Height()){
					enemylist.RemoveAt(pos2);
					delete ep;
				}
				else{
					if (ep->Dir() == 0)
						ep->Pos(ep->Pos().x, ep->Pos().y + ep->Speed());
					else if (ep->Dir() == 1){
						ep->Pos(ep->Pos().x - 1, ep->Pos().y + ep->Speed());
						if (ep->Posx() < 0)
							ep->Dir(2);
					}
					else if (ep->Dir() == 2){
						ep->Pos(ep->Pos().x + 1, ep->Pos().y + ep->Speed());
						if (ep->Posx() + ep->Width() +16 > win_width)
							ep->Dir(1);
					}
				}
			}

			//刷新客机
			if (air.Isuse() == true){
				air.Posx(air.Posx() + air.Speed());
				oil.Posx(oil.Posx() + oil.Speed());
				if (air.Posx() > win_width){
					air.Isuse(false);
				}
			}

			//是否刷新技能
			if (skill.Isuse() == true) {
				Skill *ss;
				for (pos1 = jnlist.GetHeadPosition(); (pos2 = pos1) != NULL;){
					ss = (Skill*)jnlist.GetNext(pos1);
					if (ss->Posy() <= -ss->Height()){
						jnlist.RemoveAt(pos2);
						delete ss;
					}
					else{
						for (pos3 = jnlist.GetHeadPosition(); pos3 != NULL;){
							ss = (Skill*)jnlist.GetNext(pos3);
							ss->Posy(ss->Posy() - ss->Speed());
						}
					}
					if (jnlist.GetCount() == 0)
						skill.Isuse(false);
				}
			}

			//刷新boss
			if (boss.Isuse()){
				if (boss.Dir() == 1){
					boss.Pos(boss.Posx() - boss.Speed() - 5, boss.Posy() + boss.Speed() - 5);
					if (boss.Posx() <= 100)
						boss.Dir(2);
				}
				if (boss.Dir() == 2){
					boss.Pos(boss.Posx() + boss.Speed(), boss.Posy() + boss.Speed());
					if (boss.Posy() >= 300)
						boss.Dir(3);
				}
				if (boss.Dir() == 3){
					boss.Pos(boss.Posx() + boss.Speed(), boss.Posy() - boss.Speed());
					if (boss.Posx() >= 600)
						boss.Dir(4);
				}
				if (boss.Dir() == 4){
					boss.Pos(boss.Posx() - boss.Speed(), boss.Posy() - boss.Speed());
					if (boss.Posy() <= 100)
						boss.Dir(1);
				}
			}

			//刷新help
			Help *h;
			for (pos1 = helplist.GetHeadPosition(); (pos2 = pos1) != NULL;){
				h = (Help*)helplist.GetNext(pos1);
				if (h->Posy() >= win_height){
					helplist.RemoveAt(pos2);
					delete h;
				}
				else{
					h->Posy(h->Posy() + h->Speed());
				}
			}

			////////////////////////////////////////////////////////////////////////////////碰撞检测
			//有技能
			if (skill.Isuse() == true){
				for (pos3 = jnlist.GetHeadPosition(); (pos4 = pos3) != NULL;){
					ss = (Skill*)jnlist.GetNext(pos3);
					cr1 = ss->getRect();
					for (pos1 = enemylist.GetHeadPosition(); (pos2 = pos1) != NULL;) {
						ep = (EnemyPlane*)enemylist.GetNext(pos1);  //删除敌机
						cr2 = ep->getRect();
						if (crect.IntersectRect(cr1, cr2)){
							expl = new Explode();
							expl->Pos(ep->Pos());
							explodelist.AddTail(expl);
							enemylist.RemoveAt(pos2);
							delete ep;
							score += 3;
							sscore += 3;
						}
					}
				}
				bulletlist.RemoveAll();//移除我的子弹
				enemybulletslist.RemoveAll();   //移除敌机子弹
				if (boss.Isuse() == true){
					bossenergy -= 5;
					score += 3;
				}	
			}
			//没有技能
			else {
				//我机子弹与敌机
				for (pos1 = enemylist.GetHeadPosition(); (pos2 = pos1) != NULL;) {
					ep = (EnemyPlane*)enemylist.GetNext(pos1);
					cr1 = ep->getRect();
					for (pos3 = bulletlist.GetHeadPosition(); (pos4 = pos3) != NULL;) {
						bu = (Bullet*)bulletlist.GetNext(pos3);
						cr2 = bu->getRect();
						if (crect.IntersectRect(cr1, cr2)){
							if (bu->Type() == 1 || bu->Type() == 0){
								expl = new Explode();
								expl->Pos(ep->Pos());
								explodelist.AddTail(expl);
								enemylist.RemoveAt(pos2);
								bulletlist.RemoveAt(pos4);
								delete ep;
								delete bu;
								killnum++;
								score += 1;
								sscore += 1;
								break;
							}
						}
					}
				}

				//我机子弹与客机
				if (air.Isuse()){
					cr1 = air.getRect();
					for (pos1 = bulletlist.GetHeadPosition(); (pos2 = pos1) != NULL;) {
						bu = (Bullet*)bulletlist.GetNext(pos1);
						cr2 = bu->getRect();
						if (crect.IntersectRect(cr1, cr2)){
							if (bu->Type() == 0 || bu->Type() == 1){
								bulletlist.RemoveAt(pos2);
								delete bu;
								energy -= modelparam;
							}
						}
					}
				}

				//我机子弹与人
				People *p;
				for (pos1 = bulletlist.GetHeadPosition(); (pos2 = pos1) != NULL;) {
					bu = (Bullet*)bulletlist.GetNext(pos1);
					cr1 = bu->getRect();
					for (pos3 = peoplelist.GetHeadPosition(); (pos4 = pos3) != NULL;) {
						p = (People*)peoplelist.GetNext(pos3);
						cr2 = p->getRect();
						if (crect.IntersectRect(cr1, cr2)){
							if (bu->Type() == 0 || bu->Type() == 1){
								bulletlist.RemoveAt(pos2);
								delete bu;
								peoplelist.RemoveAt(pos4);
								delete p;
								energy -= modelparam;
							}
						}
					}
				}
			
				//我机子弹与boss
				if (boss.Isuse()){
					cr1 = boss.getRect();
					for (pos1 = bulletlist.GetHeadPosition(); (pos2 = pos1) != NULL;) {
						bu = (Bullet*)bulletlist.GetNext(pos1);
						cr2 = bu->getRect();
						if (crect.IntersectRect(cr1, cr2)){
							if (bu->Type() == 0 || bu->Type() == 1){
								expl = new Explode();
								expl->Pos(bu->Pos());
								explodelist.AddTail(expl);
								bulletlist.RemoveAt(pos2);
								delete bu;
								score += 3;
								bossenergy -= 3;
							}
						}
					}
				}

				//我机子弹与oil
				if (air.Isuse()){
					cr1 = air.getRect();
					for (pos1 = bulletlist.GetHeadPosition(); (pos2 = pos1) != NULL;) {
						bu = (Bullet*)bulletlist.GetNext(pos1);
						cr2 = bu->getRect();
						if (crect.IntersectRect(cr1, cr2)){
							if (bu->Type() == 0 || bu->Type() == 1){
								energy = -1;
								break;
							}
						}
					}
				}

				//我机与help
				Help *hh;
				for (pos1 = helplist.GetHeadPosition(); (pos2 = pos1) != NULL;){
					hh = (Help*)helplist.GetNext(pos1);
					if (crect.IntersectRect(hh->getRect(), myplane.getRect())){
						if (hh->Type() == 0){
							Bullet::Uss(true);
							prot.Isuse(true);
							helplist.RemoveAt(pos2);
							delete hh;
						}
						else if (hh->Type() == 1){
							energy += 2;
							if (energy >= 50)
								energy = 50;
							helplist.RemoveAt(pos2);
							delete hh;
						}
					}
				}
				//敌机与我机
				if (prot.Isuse() == false){
					for (pos1 = enemylist.GetHeadPosition(); (pos2 = pos1) != NULL;) {
						ep = (EnemyPlane*)enemylist.GetNext(pos1);
						cr1 = ep->getRect();
						cr2 = myplane.getRect();
						if (crect.IntersectRect(cr1, cr2)){
							expl = new Explode();
							expl->Pos(ep->Pos());
							explodelist.AddTail(expl);
							enemylist.RemoveAt(pos2);
							delete ep;
							killnum++;
							score += 3;
							sscore += 3;
							energy -= modelparam;
						}
					}
				}
				else{
					for (pos1 = enemylist.GetHeadPosition(); (pos2 = pos1) != NULL;) {
						ep = (EnemyPlane*)enemylist.GetNext(pos1);
						cr1 = ep->getRect();
						cr2 = prot.getRect();
						if (crect.IntersectRect(cr1, cr2)){
							if (ep->Type() == 3)
								Bullet::Uss(false);
							expl = new Explode();
							expl->Pos(myplane.Pos());
							explodelist.AddTail(expl);
							enemylist.RemoveAt(pos2);
							delete ep;
							killnum++;
							score += 3;
							sscore += 3;
						}
					}
				}

				//我机与boss
				if (boss.Isuse()){
					cr1 = boss.getRect();
					cr2 = myplane.getRect();
					if (crect.IntersectRect(cr1, cr2)){
						expl = new Explode();
						expl->Pos(myplane.Pos());
						explodelist.AddTail(expl);
						energy -= modelparam;
						prot.Isuse(false);
						Bullet::Uss(false);
						prot.Isuse(false);
					}
				}

				//敌机子弹与我机
				if (prot.Isuse() == false){
					for (pos1 = enemybulletslist.GetHeadPosition(); (pos2 = pos1) != NULL;) {
						eb = (EnemyBullets*)enemybulletslist.GetNext(pos1);
						cr1 = eb->getRect();
						cr2 = myplane.getRect();
						if (crect.IntersectRect(cr1, cr2)){
							expl = new Explode();
							expl->Pos(myplane.Pos());
							explodelist.AddTail(expl);
							enemybulletslist.RemoveAt(pos2);
							delete eb;
							energy -= modelparam;
						}
					}
				}
				else{
					for (pos1 = enemybulletslist.GetHeadPosition(); (pos2 = pos1) != NULL;) {
						eb = (EnemyBullets*)enemybulletslist.GetNext(pos1);
						cr1 = eb->getRect();
						cr2 = prot.getRect();
						if (crect.IntersectRect(cr1, cr2)&&eb->Type() != 2){
							expl = new Explode();
							expl->Pos(myplane.Pos());
							explodelist.AddTail(expl);
							enemybulletslist.RemoveAt(pos2);
							delete eb;
							if (eb->Type() == 2)
								prot.Isuse(false);
						}
					}
				}
			}

			//我机子弹与敌机子弹
			for (pos1 = enemybulletslist.GetHeadPosition(); (pos2 = pos1) != NULL;) {
				eb = (EnemyBullets*)enemybulletslist.GetNext(pos1);
				cr1 = eb->getRect();
				for (pos3 = bulletlist.GetHeadPosition(); (pos4 = pos3) != NULL;) {
					bu = (Bullet*)bulletlist.GetNext(pos3);
					cr2 = bu->getRect();
					if (crect.IntersectRect(cr1, cr2)){
						if (bu->Type() == 2){
							expl = new Explode();
							expl->Pos(eb->Pos());
							explodelist.AddTail(expl);
							enemybulletslist.RemoveAt(pos2);
							bulletlist.RemoveAt(pos4);
							delete eb;
							delete bu;
							break;
						}
					}
				}
			}

			//刷新坐标
			if ((GetKeyState(VK_UP) < 0)){//上方向键{
				if (myplane.Posy() - myplane.Speed() >= 0){
					CPoint point(myplane.Pos().x, myplane.Pos().y - myplane.Speed());
					myplane.Pos(point);
				}
			}
			if ((GetKeyState(VK_DOWN) < 0)){//下方向键{
				if (myplane.Pos().y + myplane.Height() + 90 <= win_height){
					CPoint point(myplane.Pos().x, myplane.Pos().y + myplane.Speed());
					myplane.Pos(point);
				}
			}
			if ((GetKeyState(VK_LEFT) < 0)){//左方向键{
				if (myplane.Pos().x - myplane.Speed() >= 0){
					CPoint point(myplane.Pos().x - myplane.Speed(), myplane.Pos().y);
					myplane.Pos(point);
				}
			}
			if ((GetKeyState(VK_RIGHT) < 0 )){//右方向键{
				if (myplane.Pos().x +  myplane.Width() + 20 <= win_width){
					CPoint point(myplane.Pos().x + myplane.Speed(), myplane.Pos().y);
					myplane.Pos(point);
				}
			}
			
			//大招
			if ((GetKeyState('S')<0)) {
				if (nflag > 0){
					if (skill.Isuse() == false){
						skill.Isuse(true);
						nflag--;
						for (int i = 0; i < (int)win_width / skill.Width() + 1; i++){
							Skill *s;
							s = new Skill();
							s->Pos(i * 44, win_height);
							s->Speed(1);
							jnlist.AddTail(s);
						}
						skilllist.RemoveTail();
					}
				}
			}

			//我机死亡,游戏结束
			if (energy <= 0){  
				begin = false;
				stop = false;
				win = false;
				init = false;
				die = true;
			}

			//boss死亡,升级
			if (bossenergy <= 0){
				if (grade < 150){
					grade++;
					sscore = 0;
					this->KillTimer(2);
					SetTimer(2, 1500 - 10 * grade, 0);
					boss.Isuse(false);
					bossenergy = 200 + 30 * grade;
				}
				else{
					begin = false;
					stop = false;
					win = true;
					init = false;
					die = false;
				}
			}

			//分数达到，加载boss
			if (sscore <= 90 + 20 * grade + 3 && sscore >= 80 + 20 * grade - 3){
				boss.Isuse(true);
			}
		}

		//产生敌机
		if (nIDEvent == 2){  
			EnemyPlane *t = new EnemyPlane();
			t->Pos(rand() % (win_width - t->Width()), 0);//位置
			t->Speed(rand() % 4+4);//速度
			t->Dir(rand() % 3);
			t->Type(rand() % 4);

			if (t->Type() == 2){
				t->Width(50);
				t->Height(50);
				EnemyBullets *b = new EnemyBullets();
				b->Type(t->Type());
				b->Width(10);
				b->Height(20);
				b->Dir(rand() % 2 + 1);
				b->Pos(t->Pos().x + t->Width() / 2, 20);
				b->Speed(t->Speed() + rand() % 3 + 1);
				enemybulletslist.AddTail(b);
			}
			else if (t->Type() == 3){
				t->Width(100);
				t->Height(31);
				EnemyBullets *b = new EnemyBullets();
				b->Type(t->Type());
				b->Width(19);
				b->Height(112);
				b->Dir(0);
				b->Pos(t->Pos().x + t->Width() / 2, 20);
				b->Speed(t->Speed() + rand() % 3 + 1);
				enemybulletslist.AddTail(b);
			}
			else{   //随机产生是否发子弹
				if (rand() % 2 == 0){
					EnemyBullets *b;
					for (int i = 0; i < rand() % 2; i++){
						b = new EnemyBullets();
						b->Type(t->Type());
						b->Dir(rand() % 3);
						b->Pos(t->Pos().x + t->Width() / 2, 20);
						b->Speed(t->Speed() + rand() % 3 + 1);
						enemybulletslist.AddTail(b);
					}
				}
			}
			enemylist.AddTail(t);
		}

		//战机发射子弹
		if (nIDEvent == 3){
			if ((GetKeyState(VK_SPACE) < 0)){
				if (Bullet::Uss() == false){
					Bullet *bu = new Bullet();
					bu->Type(0);
					bu->Pos(myplane.Pos().x + 20, myplane.Pos().y);
					bulletlist.AddTail(bu);

					bu = new Bullet();
					bu->Type(0);
					bu->Pos(myplane.Pos().x + myplane.Width() - 20, myplane.Pos().y);
					bulletlist.AddTail(bu);
				}
				else{
					Bullet *bu = new Bullet();
					bu->Type(1);
					bu->Speed(15);
					bu->Width(40);
					bu->Height(60);
					bu->Pos(myplane.Pos().x + 20, myplane.Pos().y);
					bulletlist.AddTail(bu);
				}
			}
		}

		//产生help
		if (nIDEvent == 4){ 
			Help *he = new Help();//子弹
			he->Type(rand() % 2);
			if (he->Type() == 0){
				he->Width(35);
				he->Height(53);
				he->Pos(rand() % (win_width - 20), 0);
				he->Speed(6 + rand() % 3);
				helplist.AddTail(he);
			}
			else if (he->Type() == 1){//血量
				he->Width(16);
				he->Height(25);
				he->Pos(rand() % (win_width - 20), 0);
				he->Speed(6 + rand() % 3);
				helplist.AddTail(he);
			}
		}

		//boss发子弹，随机产生九个
		if (nIDEvent == 5){
			if (boss.Isuse() == true) {
				EnemyBullets *ba;
				for (int i = 0; i < 3; i++){
					ba = new EnemyBullets();
					ba->Dir(1);
					ba->Speed(rand() % 5 + 2);
					ba->Pos(boss.Posx() + boss.Width() / 2, boss.Posy() + boss.Height());
					enemybulletslist.AddTail(ba);
				}
				for (int i = 0; i < 3; i++){
					ba = new EnemyBullets();
					ba->Dir(0);
					ba->Speed(rand() % 5 + 2);
					ba->Pos(boss.Posx() + boss.Width() / 2, boss.Posy() + boss.Height());
					enemybulletslist.AddTail(ba);
				}
				for (int i = 0; i < 3; i++){
					ba = new EnemyBullets();
					ba->Dir(2);
					ba->Speed(rand() % 5 + 2);
					ba->Pos(boss.Posx() + boss.Width() / 2, boss.Posy() + boss.Height());
					enemybulletslist.AddTail(ba);
				}
			}
		}

		//刷新出现客机
		if (nIDEvent == 6){ 
			if (air.Isuse() == false){
				air.Isuse(true);
				air.Pos(0,100);
				oil.Pos(-30,180);
			}	
		}

		//产生小人
		if (nIDEvent == 7){ 
			if (air.Isuse()){
				People *peo = new People();
				peo->Speed(10);
				peo->Pos(air.Posx() + 80,air.Posy() + 80);
				peoplelist.AddTail(peo);
			}
		}
		
		//产生子弹2
		if (nIDEvent == 9){
			Bullet *bu = new Bullet();
			bu->Type(2);
			bu->Speed(12);
			bu->Width(15);
			bu->Height(104);
			bu->Pos(myplane.Pos().x + 65, myplane.Pos().y + 5);
			bulletlist.AddTail(bu);

			bu = new Bullet();
			bu->Type(2);
			bu->Speed(12);
			bu->Width(15);
			bu->Height(104);
			bu->Pos(myplane.Pos().x - 25, myplane.Pos().y + 5);
			bulletlist.AddTail(bu);

			bu = new Bullet();
			bu->Type(2);
			bu->Speed(12);
			bu->Width(15);
			bu->Height(104);
			bu->Pos(myplane.Pos().x + 20, myplane.Pos().y - 10);
			bulletlist.AddTail(bu);
		}
		//循环播放音乐和控制保护罩
		if (nIDEvent == 8){
			num1++;
			if (num1 == 50){
				num1 = 0;
				PlaySound((LPCTSTR)IDR_WAVE6, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC);
			}
			
			if (prot.Isuse()){
				num2++;
				if (num2 == 50){
					num2 = 0;
					prot.Isuse(false);
				}
			}
		}
		this->Invalidate();
		CView::OnTimer(nIDEvent);
	}
}

void CPlaneGameView::OnInitialUpdate(){
	CView::OnInitialUpdate();    //双缓冲
	CDC* pDC = this->GetWindowDC();
	this->GetClientRect(&rect);
	MemBitmap.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
	CBitmap *pOldBit = MemDC.SelectObject(&MemBitmap);

	SetTimer(1, 40, 0);   //刷坐标，碰撞检测
	SetTimer(2, 1500, 0);  //产生敌机
	SetTimer(3, 150, 0);   //发子弹
	SetTimer(4, 1000, 0);   //help
	SetTimer(5, 8000, 0);   //boss发子弹
	SetTimer(6, 30000, 0);   //客机出现
	SetTimer(7, 2000, 0);   //产生小人
	SetTimer(8, 1000, 0);   //产生音乐
	SetTimer(9, 800, 0);   //产生子弹2
	this->Invalidate();
}

BOOL CPlaneGameView::OnEraseBkgnd(CDC* pDC){
	return TRUE;
}

void CPlaneGameView::OnDestroy(){
	CView::OnDestroy();
	this->KillTimer(1);
	this->KillTimer(2);
	this->KillTimer(3);
	this->KillTimer(4);
	this->KillTimer(5);
	this->KillTimer(6);
	this->KillTimer(7);
	this->KillTimer(8);
	this->KillTimer(9);
}

//添加技能图标函数
void CPlaneGameView::Add(){
	Bullet *bu;
	for (int i = 0; i < 3; i++){
		bu = new Bullet();
		bu->Pos(win_width - 90 + i * 20, 14);
		skilllist.AddTail(bu);
	}
}

//自定义初始化函数
void CPlaneGameView::Init(){
	skilllist.RemoveAll(); //清空链表，值初始化，timer初始化
	enemybulletslist.RemoveAll();
	enemylist.RemoveAll();
	explodelist.RemoveAll();
	bulletlist.RemoveAll();
	Add();
	grade = 1;
	killnum = 0;
	score = 0; 
	sscore = 0;
	num1 = 0;
	num2 = 0;
	SETLEVEL::level = 1;
	energy = 50;
	bossenergy = 200;
	flag = 1;
	modelparam = 1;
	myplane.Pos(450, 570);
	myplane.Isuse(true);
	air.Isuse(false);
	prot.Isuse(false);
	this->KillTimer(1);
	this->KillTimer(2);
	this->KillTimer(3);
	this->KillTimer(4);
	this->KillTimer(5);
	this->KillTimer(6);
	this->KillTimer(7);
	this->KillTimer(8);
	this->KillTimer(9);
	SetTimer(1, 40, 0);   //刷坐标，碰撞检测
	SetTimer(2, 1500, 0);  //产生敌机
	SetTimer(3, 150, 0);   //发子弹
	SetTimer(4, 10000, 0);   //出现help
	SetTimer(5, 8000, 0);   //boss发子弹
	SetTimer(6, 25000, 0);   //客机出现
	SetTimer(7, 1500, 0);   //产生小人
	SetTimer(8, 1000, 0);   //产生音乐
	SetTimer(9, 800, 0);   //产生子弹2
	PlaySound((LPCTSTR)IDR_WAVE6, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC);
}

//暂停
void CPlaneGameView::Pause(){ 
	if (begin == true){
		begin = false;
		stop = true;
	}
	PlaySound(NULL, NULL, SND_FILENAME);
}

//继续
void CPlaneGameView::Continue(){ 
	if (begin == false && init == false){
		begin = true;
	}
	PlaySound((LPCTSTR)IDR_WAVE6, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC);
}

//重新开始
void CPlaneGameView::NewGame(){
	PlaySound(NULL, NULL, SND_FILENAME);
	begin = false;
	stop = false;
	die = false;
	win = false;
	init = true;
	Init();
}

//无敌模式
void CPlaneGameView::SimpleModel() {
	modelparam = 0;
}

//普通模式
void CPlaneGameView::SimModel(){
	modelparam = 1;
}

void CPlaneGameView::Set(){
	if (begin == true){
		SETLEVEL set;
		if (set.DoModal() == IDOK){
			grade = SETLEVEL::level;
			this->KillTimer(2);
			SetTimer(2, 1500 - grade * 10, 0);
			boss.Isuse(false);
			bossenergy = 200 + 30 * grade;
		}
	}
}


void CPlaneGameView::OnLButtonDown(UINT nFlags, CPoint point)
{
}
