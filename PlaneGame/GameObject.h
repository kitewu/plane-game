#pragma once
#include "afx.h"
class GameObject :
	public CObject
{
public:
	GameObject();
	~GameObject();
	virtual bool LoadImage(CDC* pDC) = 0;
	//��ȡλ�õ�
	CPoint Pos();  
	int Posx();
	int Posy();
	//�޸�λ��
	void Posx(int); 
	void Posy(int);
	void Pos(int, int);
	void Pos(CPoint); 

	//��ȡ��������
	CRect getRect();

	//�޸Ĵ�С
	void Width(int);
	void Height(int);
	//��ȡ��С
	int Width();
	int Height();

	//��ȡ�ٶ�
	int Speed();
	//�޸��ٶ�
	void Speed(int);
private:
	CPoint pos; //λ��
	int width;  //���
	int height; //�߶�
	int speed;  //�ٶ�
};

