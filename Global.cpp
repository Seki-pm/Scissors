#include "Global.h"


//グローバル変数初期化
XMFLOAT3 Global::Position_ = XMFLOAT3(0, 0, 0);

XMFLOAT2 Global::Camera_Start = XMFLOAT2(0, 0);
XMFLOAT2 Global::Camera_Goal = XMFLOAT2(0, 0);

XMFLOAT3 Global::ItemModelPos = XMFLOAT3(0, 0, 0);
XMFLOAT3 Global::ItemImagePos = XMFLOAT3(0,0,0);
XMFLOAT3 Global::ItemImageSca = XMFLOAT3(0,0,0);

int Global::SelectStage = 1;

int Global::MAXHP = 500;

bool Global::GetCoin  = false;
bool Global::Pause  = false;
bool Global::GameOver = false;
bool Global::IsGameOver = false;
bool Global::ItemReDraw = false;

vector<int>Global::Repel_;
vector<int>Global::Sink_;

Global::Stage_Status Global::stage1 = { false,false,false };
Global::Stage_Status Global::stage2 = { false,false,false };
Global::Stage_Status Global::stage3 = { false,false,false };


//グローバル関数
void Global::SetTransPos(XMFLOAT3 position)
{
	Position_ = position;
}

XMFLOAT3 Global::GetTransPos()
{
	return Position_;
}

void Global::SetCameraStart(float startX, float startY)
{
	Camera_Start = XMFLOAT2(startX, startY);
}

void Global::SetCameraGoal(float goalX, float goalY)
{
	Camera_Goal = XMFLOAT2(goalX, goalY);
}

XMFLOAT2 Global::GetCameraStart()
{
	return Camera_Start;
}

XMFLOAT2 Global::GetCameraGoal()
{
	return Camera_Goal;
}
