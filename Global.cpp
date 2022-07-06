#include "Global.h"


//ÉOÉçÅ[ÉoÉãïœêîèâä˙âª
XMFLOAT3 Global::Position_ = XMFLOAT3(0, 0, 0);


XMFLOAT2 Global::Camera_Start = XMFLOAT2(0, 0);
XMFLOAT2 Global::Camera_Goal = XMFLOAT2(0, 0);

XMFLOAT3 Global::ItemModelPos = XMFLOAT3(0, 0, 0);

XMFLOAT3 Global::ItemImagePos = XMFLOAT3(0,0,0);
XMFLOAT3 Global::ItemImageSca = XMFLOAT3(0,0,0);
XMFLOAT3 Global::ItemImagePos_Stage = XMFLOAT3(0.9f, 0.8f, 0.f);
XMFLOAT3 Global::ItemImageSca_Stage = XMFLOAT3(0.5f, 0.5f, 0.5f);
XMFLOAT3 Global::ItemImageSca_Select = XMFLOAT3(0.4f, 0.4f, 0.4f);

XMFLOAT3 Global::InitPos = XMFLOAT3(0, 1, 0);
XMFLOAT3 Global::InitRot = XMFLOAT3(0, 0, 0);

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
bool Global::Timer = false;

bool Global::RepelFlg = false;
bool Global::SinkFlg = false;
bool Global::ItemReDraw = false;

int   Global::MAXHP = 500;
int   Global::NORMAL_DAMAGE = 1;
float Global::JumpStart = 0.f;
float Global::JumpEnd = 0.f;

bool Global::Soundflg = false;

int Global::SCENE_ID = 0;


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
