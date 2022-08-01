#include "Game.h"


//グローバル変数初期化
XMFLOAT3 Game::Position_ = XMFLOAT3(0, 0, 0);

XMFLOAT2 Game::Camera_Start = XMFLOAT2(0, 0);
XMFLOAT2 Game::Camera_Goal = XMFLOAT2(0, 0);

XMFLOAT3 Game::ItemModelPos = XMFLOAT3(0, 0, 0);
XMFLOAT3 Game::ItemImagePos = XMFLOAT3(0,0,0);
XMFLOAT3 Game::ItemImageSca = XMFLOAT3(0,0,0);

int Game::SelectStage = 1;

int Game::MAXHP = 500;

bool Game::GetCoin  = false;
bool Game::Pause  = false;
bool Game::GameOver = false;
bool Game::IsGameOver = false;
bool Game::ItemReDraw = false;

vector<int>Game::Repel_;
vector<int>Game::Sink_;

unsigned int Game::Status = 0x0000;

//ビットフラグで管理
Game::Stage_Status Game::stage1 = { 1 << 0 ,1 << 1 ,1 << 2 };  //右から 1,2,3番目で管理
Game::Stage_Status Game::stage2 = { 1 << 3 ,1 << 4 ,1 << 5 };  //右から 4,5,6番目で管理
Game::Stage_Status Game::stage3 = { 1 << 6 ,1 << 7 ,1 << 8 };  //右から 7,8,9番目で管理


//グローバル関数
void Game::SetTransPos(XMFLOAT3 position)
{
	Position_ = position;
}

XMFLOAT3 Game::GetTransPos()
{
	return Position_;
}

void Game::SetCameraStart(float startX, float startY)
{
	Camera_Start = XMFLOAT2(startX, startY);
}

void Game::SetCameraGoal(float goalX, float goalY)
{
	Camera_Goal = XMFLOAT2(goalX, goalY);
}

XMFLOAT2 Game::GetCameraStart()
{
	return Camera_Start;
}

XMFLOAT2 Game::GetCameraGoal()
{
	return Camera_Goal;
}


void Game::setState(const unsigned char sstate )
{
	Status = Status | sstate; //フラグを立てるときは　OR
}

void Game::unsetState(const unsigned char sstate)
{
	Status = Status & ~sstate; //フラグを下げるときは AND NOT
}

bool Game::getState(const unsigned char sstate)
{
	return(Status & sstate); //フラグを確認するときは AND
}

