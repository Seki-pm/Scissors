#pragma once
#include "Engine/Direct3D.h"
using namespace std;

//�O���[�o���ϐ��i�V�[�����܂����ŗL���j
class Global
{
private:
	//Scissors��Position
	static float Trans_Pos_X;				
	static float Trans_Pos_Y;				
	static float Trans_Pos_Z;	

	//�J������Start & Goal
	static float Camera_Start;
	static float Camera_Goal;

public:

	//Player�̏����ʒu & ������]�p�x
	static XMFLOAT3 InitPos;
	static XMFLOAT3 InitRot;

	//StageSelectScene�̑I������Ă���ԍ�
	static int Select;

	//StageUnlock�ϐ�
	static bool Unlock2;
	static bool Unlock3;

	static int HP;
	static int MAXHP;
	static int NORMAL_DAMAGE;
	static float JumpStart;
	static float JumpEnd;
	static int NowHP;
	static int prevHP;

	static bool Timer;
	static bool GetCoin;
	static bool GameOver;
	static bool IsGameOver;


	void SetTransPos_X(float x);
	float GetTransPos_X();

	void SetTransPos_Y(float y);
	float GetTransPos_Y();

	void SetTransPos_Z(float z);
	float GetTransPos_Z();

	void SetCameraStart(float start);
	float GetCameraStart();

	void SetCameraGoal(float goal);
	float GetCameraGoal();
};
