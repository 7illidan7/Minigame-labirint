#pragma once
/*******************************************************************************
* �  �  �  �  �     � + +                                                       *
*---------------------------------------------------------------------------- - *
*                                                                               *
*Project Name :                                                                 *
*File Name : Header.h														    *
*Programmer(s) : ������ �. �.								                	*
*Modifyed By :																    *
*Created : 17 / 12 / 21  														*
*Last Revision : 17 / 12 / 21													*
*Comment(s) : ���������� �������.������������									*
**
*******************************************************************************/

class Location
{
protected:     //������������� ����������� �������� (������������ 
			   //������) ����� ������ � ������� ������
	int X;
	int Y;

public:   //��� ������ �������� ����� ���� � ���������

	Location(int InitX, int InitY);  //�����������
	~Location();                     //����������
	int GetX();//������� �������� ���� X
	int GetY();//������� �������� ���� Y
	void SetX(int X);//�������� �������� ���� X
	void SetY(int Y);//�������� �������� ���� Y

};// class Location

class Point : public Location //�� ��������� private
{
	/*
	Point- ����������� ����� �� Location
	������� public � ���������� ������������ ������ ��������
	��� X � Y �������� ����������� (protected) ������ Point
	����������� �� ����������
	*/
protected:         //�������, ����������� �� Point, ����������� ������ public
	bool Visible;   //�������� ����� ��� ���

public:
	Point(int InitX, int InitY);   //����������� ������
	~Point();                       //����������
	bool IsVisible();  //������ ��� ���������� �����
	virtual void Show() = 0;//����� ����������� ������� - ����������� �����
	virtual void Hide() = 0;//����� ����������� ������� - ����������� �����
	void MoveTo(int NewX, int NewY);// ����������� ����� �� ����� �����������
};//class Point


class Bomb : public Point//�����
{
protected:
	double scale;//������
	int Scores;//����������  �����
	int HomeScores;//����������� ����� ��� ��������������
	void MoveTo(int NewX, int NewY);
public:
	Bomb(int InitX, int InitY, int Scores, int HomeScores); //����������� ������
	~Bomb();//����������
	void Hide();//������� ��������������
	void Expand(double Deltascal);//���������� ��������
	void Reduce(double Deltasca); // ������������� ���������� ��������
	void Drag(int Step);//���������� ������ �� �������� ���
	void SetScore(int Scores);//�������� ��������� ������
	int GetScor(void);//������ ���������� ������
	double GetScale(void);//������ �������
	virtual void Circle();//������� ������� �����
};//class Lantern


class BombGood : public Bomb//����� ������ , ��������� ����
{
public:
	BombGood(int InitX, int InitY); //����������� ������
	~BombGood();//����������
	void Show();//�������� �����

};//class LanternGood

class BombNorm : public Bomb//����� ������������ �������, rgb
{
public:
	BombNorm(int InitX, int InitY); //����������� ������
	~BombNorm();//����������
	void Show();//�������� �����

};//class LanternNorm

class Portion : public Point
{
protected:
	bool Exist;//���������� �� ������
	double scale;//������
public:
	Portion(int InitX, int InitY, double InitScale);
	~Portion(void);
	void Hide();//������� ��������������
	bool GetEX(void);//������� ��������� ���������� ������������� �������
	void SetEx(bool exist);//������� ��������� ���������� ������������� �������
	double GetScale(void);//������� ��������� ���������� � ������� ������
	virtual void Rectangle();
};//class Portion


class GoodPortion : public Portion//��������� �������������
{
public:
	GoodPortion(int InfX, int InfY, double InitScale);
	~GoodPortion();
	void Show();//�������� �������������

};//class GoodPortion


class DeathPortion : public Portion
{
public:
	DeathPortion(int InfX, int InfY, double InitScale);
	~DeathPortion();
	void Show();//�������� �������������

};//class DeathPortion

class Tower : public Portion
{
public:
	Tower(int InfX, int InfY, double InitScale);
	~Tower();
	bool GetEX(void);//������� ��������� ���������� ������������� �������
	virtual void Rectangle();
	virtual void Trapezoid();
	virtual void Circle();
	void Show();//�������� �������������
};
class RoofTower : public Tower
{
public:
	RoofTower(int InfX, int InfY, double InitScale);
	~RoofTower();
	virtual void Rectangle();
	void Show();
};
