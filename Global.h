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
	static float Camera_StartX;
	static float Camera_StartY;
	static float Camera_GoalX;
	static float Camera_GoalY;

public:

	//Playerの初期位置 & 初期回転角度
	static XMFLOAT3 InitPos;
	static XMFLOAT3 InitRot;

	//StageSelectSceneの選択されている番号
	static int Select;

	static XMFLOAT3 ItemPos;

	//StageUnlock変数
	static bool Unlock2;
	static bool Unlock3;

	//Player関連
	static int HP;
	static int MAXHP;
	static int NORMAL_DAMAGE;
	static float JumpStart;
	static float JumpEnd;

	//Globalのフラグ
	static bool Timer;
	static bool GetCoin;
	static bool GameOver;
	static bool Pause;
	static bool IsGameOver;

	//Scene管理用
	static int SCENE_ID;

	//ハサミの現在ポジションをGlobalを通じて送る
	void SetTransPos_X(float x);
	float GetTransPos_X();

	void SetTransPos_Y(float y);
	float GetTransPos_Y();

	void SetTransPos_Z(float z);
	float GetTransPos_Z();

	//カメラのスタートとゴール位置を設定
	void SetCameraStartX(float start);
	void SetCameraStartY(float start);
	float GetCameraStartX();
	float GetCameraStartY();

	void SetCameraGoalX(float goal);
	void SetCameraGoalY(float goal);
	float GetCameraGoalX();
	float GetCameraGoalY();
};
