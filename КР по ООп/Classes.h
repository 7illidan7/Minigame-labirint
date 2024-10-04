#pragma once
/*******************************************************************************
* К  У  Р  С  Ы     С + +                                                       *
*---------------------------------------------------------------------------- - *
*                                                                               *
*Project Name :                                                                 *
*File Name : Header.h														    *
*Programmer(s) : Швецов И. А.								                	*
*Modifyed By :																    *
*Created : 17 / 12 / 21  														*
*Last Revision : 17 / 12 / 21													*
*Comment(s) : ОБЪЯВЛЕНИЕ КЛАССОВ.НАСЛЕДОВАНИЕ									*
**
*******************************************************************************/

class Location
{
protected:     //предоставляет возможность потомкам (производному 
			   //классу) иметь доступ к частным данным
	int X;
	int Y;

public:   //эти методы доступны извне всем в программе

	Location(int InitX, int InitY);  //конструктор
	~Location();                     //деструктор
	int GetX();//получит значение поля X
	int GetY();//получит значение поля Y
	void SetX(int X);//изменить значение поля X
	void SetY(int Y);//изменить значение поля Y

};// class Location

class Point : public Location //по умолчанию private
{
	/*
	Point- производный класс от Location
	фтрибут public в объявлении производного класса означает
	что X и Y являются защищенными (protected) внутри Point
	полученными по наследству
	*/
protected:         //классам, производным от Point, потребуется доступ public
	bool Visible;   //светится точка или нет

public:
	Point(int InitX, int InitY);   //конструктор класса
	~Point();                       //деструктор
	bool IsVisible();  //узнать про светимость точки
	virtual void Show() = 0;//чисто виртуальная функция - абстрактный метод
	virtual void Hide() = 0;//чисто виртуальная функция - абстрактный метод
	void MoveTo(int NewX, int NewY);// переместить точку по новым координатам
};//class Point


class Bomb : public Point//Бомба
{
protected:
	double scale;//Размер
	int Scores;//количество  балов
	int HomeScores;//колличество очков для восстановления
	void MoveTo(int NewX, int NewY);
public:
	Bomb(int InitX, int InitY, int Scores, int HomeScores); //конструктор класса
	~Bomb();//деструктор
	void Hide();//Скрытие прямоугольника
	void Expand(double Deltascal);//приращения масштаба
	void Reduce(double Deltasca); // отрицательное приращения масштаба
	void Drag(int Step);//буксировка фигуры на заданный шаг
	void SetScore(int Scores);//изменяем количесво баллов
	int GetScor(void);//чтение количества баллов
	double GetScale(void);//ЧТЕНИЕ РАЗМЕРА
	virtual void Circle();//Функция рисовки круга
};//class Lantern


class BombGood : public Bomb//Бомба больше , оранжевый цвет
{
public:
	BombGood(int InitX, int InitY); //конструктор класса
	~BombGood();//деструктор
	void Show();//показать бомбу

};//class LanternGood

class BombNorm : public Bomb//бомба стандартного размера, rgb
{
public:
	BombNorm(int InitX, int InitY); //конструктор класса
	~BombNorm();//деструктор
	void Show();//показать бомбу

};//class LanternNorm

class Portion : public Point
{
protected:
	bool Exist;//существует ли объект
	double scale;//Размер
public:
	Portion(int InitX, int InitY, double InitScale);
	~Portion(void);
	void Hide();//Скрытие прямоугольника
	bool GetEX(void);//функция получения показателя существования объекта
	void SetEx(bool exist);//функция изменения показателя существования обьекта
	double GetScale(void);//функция получения информации о размере фигуры
	virtual void Rectangle();
};//class Portion


class GoodPortion : public Portion//оранжевый прямоугольник
{
public:
	GoodPortion(int InfX, int InfY, double InitScale);
	~GoodPortion();
	void Show();//показать прямоугольник

};//class GoodPortion


class DeathPortion : public Portion
{
public:
	DeathPortion(int InfX, int InfY, double InitScale);
	~DeathPortion();
	void Show();//показать прямоугольник

};//class DeathPortion

class Tower : public Portion
{
public:
	Tower(int InfX, int InfY, double InitScale);
	~Tower();
	bool GetEX(void);//функция получения показателя существования объекта
	virtual void Rectangle();
	virtual void Trapezoid();
	virtual void Circle();
	void Show();//показать прямоугольник
};
class RoofTower : public Tower
{
public:
	RoofTower(int InfX, int InfY, double InitScale);
	~RoofTower();
	virtual void Rectangle();
	void Show();
};
