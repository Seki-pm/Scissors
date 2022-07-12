#include "Global.h"


//ÉOÉçÅ[ÉoÉãïœêîèâä˙âª
XMFLOAT3 Global::Position_ = XMFLOAT3(0, 0, 0);

XMFLOAT2 Global::Camera_Start = XMFLOAT2(0, 0);
XMFLOAT2 Global::Camera_Goal = XMFLOAT2(0, 0);

XMFLOAT3 Global::ItemModelPos = XMFLOAT3(0, 0, 0);
XMFLOAT3 Global::ItemImagePos = XMFLOAT3(0,0,0);
XMFLOAT3 Global::ItemImageSca = XMFLOAT3(0,0,0);

int Global::SelectStage = 1;

vector<int>Global::Repel_;
vector<int>Global::Sink_;

bool Global::Unlock2 = false;
bool Global::Unlock3 = false;

bool Global::GetCoin  = false;
bool Global::GetCoin_1 = false;
bool Global::GetCoin_2 = false;
bool Global::GetCoin_3 = false;

bool Global::Pause  = false;
bool Global::GameOver = false;
bool Global::IsGameOver = false;

bool Global::ItemReDraw = false;

int   Global::MAXHP = 500;


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
