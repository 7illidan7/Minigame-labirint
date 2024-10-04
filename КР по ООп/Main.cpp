#include <Windows.h>
#include <iostream>
#include<stdio.h>
#include"GetColWind.h"
#include"Classes.h"


//������ ��� ����������� ���� ������� �������
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)

using namespace std;
HWND   hwnd;     //  ������� ���������� (���������) ����
HDC    hdc;      // �������  �������� ����������

//--------------------------------------------------------------------------

//---------------------------------------------------------------------------
bool Overlap(Bomb* pSt, Portion* NL)//������� �������� ����������� ����� �� �������� ��������� 
{
	if ((((pSt->GetX()) + 10 * (1 + pSt->GetScale())) > (NL->GetX() - 7 * (1 + NL->GetScale()))) and (((pSt->GetX()) - 10 * (1 + pSt->GetScale())) < (NL->GetX() + 7 * (1 + NL->GetScale()))) and (((pSt->GetY()) - 10 * (1 + pSt->GetScale())) < ((NL->GetY()) + 7 * (1 + NL->GetScale()))) and (((pSt->GetY()) + 10 * (1 + pSt->GetScale())) > ((NL->GetY()) - 7 * (1 + NL->GetScale()))) and ((NL->GetEX()) == true))
	{
		return true;
	}
	else
	{
		return false;
	}
}//Overlap
bool Overlap(Bomb* pSt,Tower* Tw)//������� �������� ����������� ����� � ������ 
{
	if ((((pSt->GetX()) + 10 * (1 + pSt->GetScale())) > (Tw->GetX() - 7 * (1 + Tw->GetScale()))) and (((pSt->GetX()) - 10 * (1 + pSt->GetScale())) < (Tw->GetX() + 7 * (1 + Tw->GetScale()))) and (((pSt->GetY()) - 10 * (1 + pSt->GetScale())) < ((Tw->GetY()) + 7 * (1 + Tw->GetScale()))) and (((pSt->GetY()) + 10 * (1 + pSt->GetScale())) > ((Tw->GetY()) - 7 * (1 + Tw->GetScale()))) and ((Tw->GetEX()) == true))
	{
		return true;
	}
	else
	{
		return false;
	}
}//Overlap
//-----------------------------------------------------------------------------------
const int KolGoodPort = 3;//���������� ��������
//-------------------------------------------------------------
const int KolDeathPort1 = 14;//���������� ��������� � ���������	
const int KolDeathPort2 = 7;
const int KolDeathPort3 = 2;
const int KolDeathPort4 = 7;
const int KolDeathPort5 = 10;
//---------------------------
int main()
{
	system("color F0");
	int Score = 0; //����������� �����

	//������� ���������� ����������� ����
	HWND hwnd = GetConcolWindow();

	//���� ���������� ����������
	if (hwnd != NULL)
	{

		//������� �������� ���������� ��� ����������� ����
		hdc = GetWindowDC(hwnd);

		//���� �������� ���������� - ����� ��������
		if (hdc != 0)
		{
			Bomb* pSt;//������ ����� ����� ���������
			Tower* Tw;
			RoofTower* RT;
			GoodPortion* GoodP[KolGoodPort];//�������
			DeathPortion* dP1[KolDeathPort1];//������ ���������
			DeathPortion* dP2[KolDeathPort2];
			DeathPortion* dP3[KolDeathPort3];
			DeathPortion* dP4[KolDeathPort4];
			DeathPortion* dP5[KolDeathPort5];

			/*��������� ���������*/
			//-----------------------------��������� ������� ���������
			int k = 0;
			int DPX = 200;
			int DPY = 400;
			for (k = 0; k < KolDeathPort1; k++)
			{
				DPY -= 70;
				for (int i = 0; i < 2; i++)
				{
					dP1[k] = new DeathPortion(DPX, DPY, 2);
					DPY += 70;
					k++;
					dP1[k] = new DeathPortion(DPX, DPY, 2);
					i++;
				}
				DPX += 40;
			}
			DPY -= 70;
			//------------------------------------------------
			//-----------------------------------������ ��������� ����� ������ �����
			for (k = 0; k < KolDeathPort2; k++)
			{
				if (k == 0)
				{
					dP2[k] = new DeathPortion(DPX, DPY + 70, 2);
					k++;
				}
				dP2[k] = new DeathPortion(DPX, DPY, 2);
				DPY -= 40;
			}
			//------------------------------------------
			//---------------------------------------------����������� �������� ���������
			DPX += 40;
			DPY += 40;
			for (k = 0; k < KolDeathPort3; k++)
			{
				DPY += 270;
				for (int i = 0; i < 2; i++)
				{
					dP3[k] = new DeathPortion(DPX, DPY, 2);
					DPY -= 270;
					k++;
					dP3[k] = new DeathPortion(DPX, DPY, 2);
					i++;
				}
				DPX += 40;
			}
			//-----------------------------------------------------------------
			//--------------------------------------------------������ ��������� ������ �����
			for (k = 0; k < KolDeathPort4; k++)
			{
				if (k == 0)
				{
					dP4[k] = new DeathPortion(DPX, DPY, 2);
					k++;
					DPY += 70;
				}
				dP4[k] = new DeathPortion(DPX, DPY, 2);
				DPY += 40;
			}
			//-------------------------------------------------------------------
			//-----------------------------------------��������� �������
			DPX += 40;
			DPY -= 240;
			for (k = 0; k < KolDeathPort5; k++)
			{
				DPY -= 70;
				for (int i = 0; i < 2; i++)
				{
					dP5[k] = new DeathPortion(DPX, DPY, 2);
					DPY += 70;
					k++;
					dP5[k] = new DeathPortion(DPX, DPY, 2);
					i++;
				}
				DPX += 40;
			}
			//--------------------------------------------------
			//-------------------------------------------������
			for (int i = 0; i < KolGoodPort; i++)
			{
				GoodP[i] = new GoodPortion(250, 365, 1);
				i++;
				GoodP[i] = new GoodPortion(515, 250, 1);
				i++;
				GoodP[i] = new GoodPortion(640, 165, 1);
			}
			//----------------------------------------------
			BombNorm NormBomb(200, 200);
			BombGood GoodLantern(200, 200);
			pSt = new BombNorm(50, 300);//������������� �����
			Tower NormTower(1000, 150, 3);
			Tw = new Tower(1000, 150, 3);
			RoofTower NormRoofTower(1000, 150, 3);
			RT = new RoofTower(1000, 150, 3);

			while (1)
			{
				//��� ������� ���������� ��� GetEX== true ������ ������������
				
				for (int i = 0; i < KolGoodPort; i++)//����������� ��������� ���������
				{
					if ((GoodP[i]->GetEX()) == true)
						GoodP[i]->Show();
				}//for

				for (int k = 0; k < KolDeathPort1; k++)//����������� ������ ���������
				{
					if ((dP1[k]->GetEX()) == true)
						dP1[k]->Show();
				}//for
				for (int k = 0; k < KolDeathPort2; k++)//����������� ������ ���������
				{
					if ((dP2[k]->GetEX()) == true)
						dP2[k]->Show();
				}//for
				for (int k = 0; k < KolDeathPort3; k++)//����������� ������ ���������
				{
					if ((dP3[k]->GetEX()) == true)
						dP3[k]->Show();
				}//for
				for (int k = 0; k < KolDeathPort4; k++)//����������� ������ ���������
				{
					if ((dP4[k]->GetEX()) == true)
						dP4[k]->Show();
				}//for
				for (int k = 0; k < KolDeathPort5; k++)//����������� ������ ���������
				{
					if ((dP5[k]->GetEX()) == true)
						dP5[k]->Show();
				}//for
				//------------------------------------------------------------
				pSt->Show();//�������� ����� � ��������� �����
				Tw->Show();
				RT->Show();
				Score = (pSt->GetScor()); //���������� ������� ��������� ������

				pSt->Drag(10 + (int)(0.5 * (pSt->GetScor())));//������ �������� ����������� ����� ����� ����

				///-------------------------����� ���������-------------------------------------///

				for (int i = 0; i < KolGoodPort; i++)
				{
					int X1 = (pSt->GetX());
					int Y1 = (pSt->GetY());
					Overlap(pSt, GoodP[i]);

					if (Overlap(pSt, GoodP[i]))//���� ������� ��������� ������� �� ������� �������� � ���� � ������� ����� �������������
					{
						Score = Score + 3 + GoodP[i]->GetScale();
						GoodP[i]->SetEx(false);
						GoodP[i]->Hide();
					}//end if


				}//end for
				//-----------------------------���������� ���� ���� ����� �������� �� ��������
				for (int i = 0; i < KolDeathPort1; i++)//-----------------------------��������� ������� ���������
				{
					if (Overlap(pSt, dP1[i]))
					{
						dP1[i]->SetEx(false);
						dP1[i]->Hide();

						cout << "Game Over" << endl;
						system("pause");
						cout << endl;
						return 1;
					}//end if
				}//end for
				for (int i = 0; i < KolDeathPort2; i++)//-----------------------------------������ ��������� ����� ������ �����
				{
					if (Overlap(pSt, dP2[i]))
					{
						dP2[i]->SetEx(false);
						dP2[i]->Hide();

						cout << "Game Over" << endl;
						system("pause");
						cout << endl;
						return 2;
					}//end if
				}//end for
				for (int i = 0; i < KolDeathPort3; i++)//---------------------------------------------����������� �������� ���������
				{
					if (Overlap(pSt, dP3[i]))
					{
						dP3[i]->SetEx(false);
						dP3[i]->Hide();

						cout << "Game Over" << endl;
						system("pause");
						cout << endl;
						return 3;
					}//end if
				}//end for
				for (int i = 0; i < KolDeathPort4; i++)//--------------------------------------------------������ ��������� ������ �����
				{
					if (Overlap(pSt, dP4[i]))
					{
						dP4[i]->SetEx(false);
						dP4[i]->Hide();

						cout << "Game Over" << endl;
						system("pause");
						cout << endl;
						return 4;
					}//end if
				}//end for
				for (int i = 0; i < KolDeathPort5; i++)//-----------------------------------------��������� �������
				{
					if (Overlap(pSt, dP5[i]))
					{
						dP5[i]->SetEx(false);
						dP5[i]->Hide();

						cout << "Game Over" << endl;
						system("pause");
						cout << endl;
						return 5;
					}//end if
				}//end for
				//-----------------------------------------------------
				//---------------------------------------------���������� ���� (������) ���� ����� ��������� �����
				if (Overlap(pSt, Tw))
				{
					cout << "Congratulations!!!" << endl;
					system("pause");
					cout << endl;
					return 666;
				}
				//---------------------------------------------------------------
				if (Score != pSt->GetScor())//�������� ������� ����� � �������� ��� � ������ ���������
					pSt->Hide();
				//��������� �������� �� ������
				if (Score != 0)
				{
					GoodLantern.SetX(pSt->GetX());
					GoodLantern.SetY(pSt->GetY());
					//GoodLantern.SetHomeS(HScore);
					GoodLantern.SetScore(Score);
					pSt = &GoodLantern;
				}//if(Score != 0)
				else//���� ���� ����� ���� �� ����������� ������ � ����� rgb
				{
					NormBomb.SetX(pSt->GetX());
					NormBomb.SetY(pSt->GetY());
					pSt = &NormBomb;
				}//else

				if ((KEY_DOWN(VK_ESCAPE)))    //����� ������ 
					break;

			}//while

			system("PAUSE");

		}//if (hdc != 0)
	}//if (hwnd != NULL)

	system("PAUSE");
	return 0;

}//main()