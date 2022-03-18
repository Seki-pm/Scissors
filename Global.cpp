#include "Global.h"


//グローバル変数初期化
float Global::Trans_Pos_X = 0.f;
float Global::Trans_Pos_Y = 0.f;
float Global::Trans_Pos_Z = 0.f;

float Global::Camera_StartX = 0.f;
float Global::Camera_StartY = 0.f;
float Global::Camera_GoalX = 0.f;
float Global::Camera_GoalY = 0.f;

XMFLOAT3 Global::InitPos = XMFLOAT3(0, 2.0f, 0);
XMFLOAT3 Global::InitRot = XMFLOAT3(0, 0, 0);

int Global::Select = 0;

bool Global::Unlock2 = false;
bool Global::Unlock3 = false;

bool Global::GetCoin  = false;
bool Global::GameOver = false;
bool Global::IsGameOver = false;
bool Global::Timer = false;


int   Global::MAXHP = 500;
int   Global::HP = Global::MAXHP;
int   Global::NORMAL_DAMAGE = 1;
float Global::JumpStart = 0.f;
float Global::JumpEnd = 0.f;


int Global::SCENE_ID = 0;

//x座標
void Global::SetTransPos_X(float x)
{
	Trans_Pos_X = x;
}

float Global::GetTransPos_X()
{
	return Trans_Pos_X;
}

//y座標
void Global::SetTransPos_Y(float y)
{
	Trans_Pos_Y = y;
}

float Global::GetTransPos_Y()
{
	return Trans_Pos_Y;
}

//z座標
void Global::SetTransPos_Z(float z)
{
	Trans_Pos_Z = z;
}

float Global::GetTransPos_Z()
{
	return Trans_Pos_Z;
}

void Global::SetCameraStartX(float start)
{
	Camera_StartX = start;
}

void Global::SetCameraStartY(float start)
{
	Camera_StartY = start;
}

float Global::GetCameraStartX()
{
	return Camera_StartX;
}

float Global::GetCameraStartY()
{
	return Camera_StartY;
}

void Global::SetCameraGoalX(float goal)
{
	Camera_GoalX = goal;
}

void Global::SetCameraGoalY(float goal)
{
	Camera_GoalY = goal;
}

float Global::GetCameraGoalX()
{
	return Camera_GoalX;
}

float Global::GetCameraGoalY()
{
	return Camera_GoalY;
}
