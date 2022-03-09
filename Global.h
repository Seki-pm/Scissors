#pragma once
#include "Engine/Direct3D.h"
using namespace std;

//グローバル変数（シーンをまたいで有効）
class Global
{
private:
	//ScissorsのPosition
	static float Trans_Pos_X;				
	static float Trans_Pos_Y;				
	static float Trans_Pos_Z;	

	//カメラのStart & Goal
	static float Camera_Start;
	static float Camera_Goal;

public:

	//Playerの初期位置 & 初期回転角度
	static XMFLOAT3 InitPos;
	static XMFLOAT3 InitRot;

	//StageSelectSceneの選択されている番号
	static int Select;

	//StageUnlock変数
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
