/********************************************************************
*                      �  �  �  �  �     �  +  +                   *
*------------------------------------------------------------------*
* Project Type  : Win32 Console Application                        *
* Project Name  :											       *
* File Name     : Source.cpp                                       *
* Programmer(s) : ������ �. �.									   *
* Modifyed By   :                                                  *
* Created       : 17 / 12 / 21                                         *
* Last Revision : 17 / 12 / 21                                         *
* Comment(s)    : ���������� �������. ������������                 *
*                                                                  *
********************************************************************/
#include <iostream>
#include <windows.h>
#include "Classes.h"
extern HDC hdc;      // �������  �������� ����������

//������ ��� ����������� ���� ������� �������
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
using namespace std;

/*------------------------------------------------------------------*/
/*                 � � � � � � � � � �    � � � � � � �             */
/*------------------------------------------------------------------*/

/*----------------------------------------*/
/*        ������ ������ Location          */
/*----------------------------------------*/
Location::Location(int X, int Y)//�����������
{
	this->X = X;
	this->Y = Y;
};//Location()

Location::~Location(void)  //����������
{
	//������ ����
};//~Location()

int Location::GetX(void)//�������� �������� ���� X
{
	return X;
};//GetX
int Location::GetY(void)//�������� �������� ���� Y
{
	return Y;
};//GetY
void Location::SetX(int X)//������ �������� ���� X
{
	this->X = X;
}//SetX
void Location::SetY(int Y) //������ �������� ���� Y
{
	this->Y = Y;
}//SetY

/*----------------------------------------*/
/*        ������ ������ Point             */
/*----------------------------------------*/
Point::Point(int InitX, int InitY) : Location(InitX, InitY)//�����������
{
	Visible = false;
}//Point()

//--------------------------------------------------------------
Point::~Point(void)   //����������
{
	//������ ����
}//~Point()
//-------------------------------------------------------------
void Point::Show(void)//�������� ����� �� ������
{
	Visible = true;//����� �����
	SetPixel(hdc, X, Y, RGB(255, 0, 0));//������ ������������� ������
	SetPixel(hdc, X + 1, Y, RGB(255, 0, 0));
	SetPixel(hdc, X, Y + 1, RGB(255, 0, 0));
	SetPixel(hdc, X + 1, Y + 1, RGB(255, 0, 0));
}//Show()
//--------------------------------------------------------------
void Point::Hide(void)
{
	Visible = false;//����� �� �����

	SetPixel(hdc, X, Y, RGB(0, 0, 255));//������ ������ ����
	SetPixel(hdc, X + 1, Y, RGB(0, 0, 255));
	SetPixel(hdc, X, Y + 1, RGB(0, 0, 255));
	SetPixel(hdc, X + 1, Y + 1, RGB(0, 0, 255));
}//Hide()
//--------------------------------------------------------------
bool Point::IsVisible(void) //������ ��� ���������� ����� 
{
	return Visible;
}; //IsVisible()
//---------------------------------------------------------------
void Point::MoveTo(int NewX, int NewY)//����������� ����� �� ����� �����������
{
	Hide();//������ �����
	X = NewX;//�������� ����������
	Y = NewY;
	Show();//�������� ����� �� ����� �����������
};//MoveTo()
//--------------------------------------------------------------

//---------------------------------------------------------------------------
//��� ������������� �������� ����� ���������� ����������� ������
Bomb::Bomb(int InitX, int InitY, int InScores, int InHomeScores) : Point(InitX, InitY)//����� ������������� ������� � ���������� ���������������� �� ������� ������������� �����������
{
	if (InScores < -15)
		InScores = -15;
	if (InScores > 15)
		InScores = 15;
	if (InHomeScores > 50)
		InHomeScores = 50;
	if (InHomeScores < 0)
		InHomeScores = 0;
	this->scale = 0 + (4 / 100) * InScores;
	this->Scores = InScores;
	this->HomeScores = InHomeScores;
}//Lantern()

//--------------------------------------------------------------
Bomb::~Bomb(void)//��������� ������ ����
{
	//��������� ������ ����
}//~Lantern()

//--------------------------------------------------------------


void Bomb::Circle(void)
{
	//������ ����
	Ellipse(hdc, X - 7 * (4 + scale), Y + 4 * (4 + scale), X + 2 * (4 + scale), Y - 5 * (4 + scale));


}//Circle()
void Bomb::Hide(void)
{
	Visible = false;
	// ������� ���� � ���� ���� - �������
	HPEN Pen = CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
	SelectObject(hdc, Pen);	//������� ���� ��������
	Circle();
	// ��������� ���� ��������� �������  
	DeleteObject(Pen);
}//end Lantern::Hide(void)
//--------------------------------------------------------------

void Bomb::MoveTo(int NewX, int NewY)
{
	Hide();  //������� ����� ���������
	X = NewX; //�������� ����������
	Y = NewY;
	Show();  //�������� ����� �� ����� �����
}//end Lantern::MoveTo


void Bomb::Expand(double Deltascal)
{
	Hide();             //�������� ����� �� ������ ���������
	scale += Deltascal / 100; //�������� ������� 
	if (scale <= -1)     //��� �������������� ���������� ���������
		scale = -95 / 100;
	Show();             //�������� ����� � ����� ���������
}//end Rectangl::Expand ()
//---------------------------------------------------------------

void Bomb::Reduce(double Deltasca)
{
	Expand(-Deltasca); //������������� ���������� ��������
};//end Rectangl::Reduce ()
//--------------------------------------------------------------

void Bomb::Drag(int Step)    //���������� ������
{
	int FigX, FigY;   //����� ���������� ������
	int i = 0;

	FigX = X;    //�������� ��������� ��������� ������
	FigY = Y;
	while (1)	//����������� ���� ���������� ������
	{
		i++;

		if (i == 100)
			break;

		//����������� �������� �������

		if ((KEY_DOWN(VK_LEFT)) or (KEY_DOWN(65))) //������� �����  37
		{
			FigX -= Step;
			if (FigX < 0)
				FigX = 0;
			MoveTo(FigX, FigY);
			Sleep(50);
			break;
			///
		}//end if

		if ((KEY_DOWN(VK_RIGHT)) or (KEY_DOWN(68))) //������� ������  39
		{
			FigX += Step;
			if (FigX > 1000)
				FigX = 1000;
			MoveTo(FigX, FigY);
			Sleep(50);
			break;

		}//end if

		if ((KEY_DOWN(VK_DOWN)) or (KEY_DOWN(83))) //������� ����  40
		{
			FigY += Step;
			if (FigY > 400)
				FigY = 400;
			MoveTo(FigX, FigY);
			Sleep(50);
			break;

		}//end if

		if ((KEY_DOWN(VK_UP)) or (KEY_DOWN(87))) //������� �����  38
		{
			FigY -= Step;
			if (FigY < 0)
				FigY = 0;
			MoveTo(FigX, FigY);
			Sleep(50);
			break;

		}//end if
	}   //while
}//end Drag()
//--------------------------------------------------------------


void Bomb::SetScore(int IntScores)//�������� �����
{
	if (IntScores < -15)
		IntScores = -15;

	if (IntScores > 15)
		IntScores = 15;
	this->Scores = IntScores;
	this->scale = 0.0 + (4.0 / 100.0) * IntScores;

};//SetScore
//--------------------------------------------------------------


int Bomb::GetScor(void)//������ ���������� ������
{
	return Scores;
};//GetScor
//--------------------------------------------------------------

double Bomb::GetScale(void)//������ ������
{
	return scale;

};//GetScale


////////////////////////////////////////////////////////////////////////////////
BombGood::BombGood(int InitX, int InitY) : Bomb(InitX, InitY, 1, 0)
{
}
//--------------------------------------------------------------

BombGood::~BombGood(void)
{
};
//--------------------------------------------------------------

void BombGood::Show(void)
{

	Visible = true;
	// ������� ���� � ���� ���� - �������
	HPEN Pen = CreatePen(PS_SOLID, 2, RGB(255, 153, 0));
	SelectObject(hdc, Pen);	//������� ���� ��������
	Circle();
	// ��������� ���� ��������� �������  
	DeleteObject(Pen);
}//Show()

///////////////////////////////////////////////////////////////////////////

BombNorm::BombNorm(int InitX, int InitY) : Bomb(InitX, InitY, 0, 0)
{
}
//--------------------------------------------------------------

BombNorm::~BombNorm(void)
{
};
//--------------------------------------------------------------

void BombNorm::Show(void)
{

	Visible = true;
	// ������� ���� � ���� ���� - �����
	HPEN Pen = CreatePen(PS_SOLID, 2, RGB(rand()%255, rand()%255, rand()%255));//110, 118, 117
	SelectObject(hdc, Pen);	//������� ���� ��������
	Circle();
	// ��������� ���� ��������� �������  
	DeleteObject(Pen);
}//Show()

//////////////////////////////////////////////////////////////////////////////////
Portion::Portion(int InfX, int InfY, double InitScale) :Point(InfX, InfY)
{
	this->Exist = true;
	this->scale = InitScale - 1;
}
//--------------------------------------------------------------
Portion::~Portion(void)
{
}
//--------------------------------------------------------------
void Portion::SetEx(bool exist)
{
	this->Exist = exist;
};

//--------------------------------------------------------------
bool Portion::GetEX(void) { return Exist; };
//--------------------------------------------------------------
double  Portion::GetScale(void) { return scale; };
//--------------------------------------------------------------

void Portion::Rectangle(void)
{
	//������ ������������� 
	MoveToEx(hdc, X - (int)(5 * (1 + scale)), Y - (int)(5 * (1 + scale)), NULL);
	LineTo(hdc, X + (int)(5 * (1 + scale)), Y - (int)(5 * (1 + scale)));
	LineTo(hdc, X + (int)(5 * (1 + scale)), Y + (int)(5 * (1 + scale)));
	LineTo(hdc, X - (int)(5 * (1 + scale)), Y + (int)(5 * (1 + scale)));
	LineTo(hdc, X - (int)(5 * (1 + scale)), Y - (int)(5 * (1 + scale)) - 1);
}

void Portion::Hide()//������� ��������������
{
	Visible = false;
	// ������� ���� � ���� ����
	HPEN Pen = CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
	SelectObject(hdc, Pen);	//������� ���� ��������
	Rectangle();
	DeleteObject(Pen);
};//Hide()


GoodPortion::GoodPortion(int InfX, int InfY, double InitScale) :Portion(InfX, InfY, InitScale)
{
}
GoodPortion::~GoodPortion(void)
{
}

void GoodPortion::Show()//����� �������������
{
	Visible = true;
	// ������� ���� � ���� ���� - ���������
	HPEN Pen = CreatePen(PS_SOLID, 2, RGB(255, 153, 0));
	SelectObject(hdc, Pen);	//������� ���� ��������
	Rectangle();
	DeleteObject(Pen);

}//Show()
DeathPortion::DeathPortion(int InfX, int InfY, double InitScale) : Portion(InfX, InfY, InitScale)
{

}
DeathPortion::~DeathPortion()
{

}
void DeathPortion::Show()
{
	Visible = true;
	// ������� ���� � ���� ���� - �������
	HPEN Pen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	SelectObject(hdc, Pen);	//������� ���� ��������
	Rectangle();
	DeleteObject(Pen);
}
Tower::Tower(int InfX, int InfY, double InitScale) :Portion(InfX, InfY, InitScale)
{
}
Tower::~Tower(void)
{
}

void Tower::Rectangle()
{
	//������ ������������� 
	MoveToEx(hdc, X - (int)(10 * (1 + scale)), Y - (int)(10 * (1 + scale)), NULL);
	LineTo(hdc, X + (int)(10 * (1 + scale)), Y - (int)(10 * (1 + scale)));
	LineTo(hdc, X + (int)(10 * (1 + scale)), Y + (int)(40 * (1 + scale)));
	LineTo(hdc, X - (int)(10 * (1 + scale)), Y + (int)(40 * (1 + scale)));
	LineTo(hdc, X - (int)(10 * (1 + scale)), Y - (int)(10 * (1 + scale)) - 1);
}
void Tower::Trapezoid()
{
	//������ ��������
	MoveToEx(hdc, X - 26 * (1 + scale) + (int)(10 * (1 + scale)), Y - (int)(10 * (1 + scale)), NULL);
	LineTo(hdc, X  + (int)(15 * (1 + scale)), Y - (int)(10 * (1 + scale)) );//+ 50 * (1 + scale)
	LineTo(hdc, X + (int)(10 * (1 + scale)), Y - (int)(10 * (1 + scale)) * 2);//+ 50 * (1 + scale)
	LineTo(hdc, X  - (int)(10 * (1 + scale)), Y - (int)(20 * (1 + scale)));
	LineTo(hdc, X  - (int)(16 * (1 + scale)), Y - (int)(10 * (1 + scale)) - 1);
}
void Tower::Circle()
{
	//������ ����
	Ellipse(hdc, X - 3 * (4 + scale), Y + 3 * (4 + scale), X + 3 * (4 + scale), Y - 3 * (4 + scale));


}//Circle()
void Tower::Show()//����� �������������
{
	Visible = true;
	// ������� ���� � ���� ���� - ���������
	HPEN Pen = CreatePen(PS_SOLID, 2, RGB(243, 218, 11));
	SelectObject(hdc, Pen);	//������� ���� ��������
	Rectangle();
	Trapezoid();
	Circle();
	DeleteObject(Pen);

}//Show()
bool Tower::GetEX(void) { return Exist; };

RoofTower::RoofTower(int InfX, int InfY, double InitScale) :Tower(InfX, InfY, InitScale)
{
}
RoofTower::~RoofTower(void)
{
}
void RoofTower::Rectangle()
{
	//������ �������������
	MoveToEx(hdc, X - (int)(5 * (1 + scale)), Y - (int)(35 * (1 + scale)), NULL);
	LineTo(hdc, X + (int)(5 * (1 + scale)), Y - (int)(35 * (1 + scale)));
	LineTo(hdc, X + (int)(5 * (1 + scale)), Y + (int)(-20 * (1 + scale)));
	LineTo(hdc, X - (int)(5 * (1 + scale)), Y + (int)(-20 * (1 + scale)));
	LineTo(hdc, X - (int)(5 * (1 + scale)), Y - (int)(35 * (1 + scale)) - 1);
}
void RoofTower::Show()
{
	Visible = true;
	// ������� ���� � ���� ���� - �������
	HPEN Pen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
	SelectObject(hdc, Pen);	//������� ���� ��������
	Rectangle();
	DeleteObject(Pen);
}