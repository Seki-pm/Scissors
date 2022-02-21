#include "Global.h"


//グローバル変数初期化


float Global::Trans_Pos_X = 0.f;
float Global::Trans_Pos_Y = 0.f;
float Global::Trans_Pos_Z = 0.f;

float Global::Camera_Start = 0.f;
float Global::Camera_Goal = 0.f;

XMFLOAT3 Global::InitPos = XMFLOAT3(0, 2.0f, 0);
XMFLOAT3 Global::InitRot = XMFLOAT3(0, 0, 0);

int Global::Select = 0;

bool Global::Unlock2 = true;
bool Global::Unlock3 = false;

bool Global::GetCoin = false;


int   Global::HP = 200;
int   Global::NORMAL_DAMAGE = 10;
float Global::JumpStart = 0.f;
float Global::JumpEnd = 0.f;
int Global::NowHP = 0;
int Global::prevHP = 0;

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


void Global::SetCameraStart(float start)
{
	Camera_Start = start;
}

float Global::GetCameraStart()
{
	return Camera_Start;
}

void Global::SetCameraGoal(float goal)
{
	Camera_Goal = goal;
}

float Global::GetCameraGoal()
{
	return Camera_Goal;
}
