#include "Global.h"


//�O���[�o���ϐ�������
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

int Global::Status = 0x0000;

//�r�b�g�t���O�ŊǗ�
Global::Stage_Status Global::stage1 = { 1 << 0 ,1 << 1 ,1 << 2 };
Global::Stage_Status Global::stage2 = { 1 << 3 ,1 << 4 ,1 << 5 };
Global::Stage_Status Global::stage3 = { 1 << 6 ,1 << 7 ,1 << 8 };


//�O���[�o���֐�
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


void Global::setState(const unsigned char sstate )
{
	Status = Status | sstate; //�t���O�𗧂Ă�Ƃ��́@OR
}


void Global::unsetState(const unsigned char sstate)
{
	Status = Status & ~sstate; //�t���O��������Ƃ��� AND NOT
}

bool Global::getState(const unsigned char sstate)
{
	return(Status & sstate); //�t���O���m�F����Ƃ��� AND
}

