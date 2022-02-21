#include "PlayScene.h"
#include "Engine/Camera.h"
#include "Scissors.h"
#include "Stage.h"


//�R���X�g���N�^
PlayScene::PlayScene(GameObject * parent)
	: GameObject(parent, "PlayScene")
{
}

//������
void PlayScene::Initialize()
{
	//�X�e�[�W
	Instantiate<Stage>(this);

	//�n�T�~�{��
	Instantiate<Scissors>(this);


	Camera::SetPosition(XMFLOAT3(5, 5, -10));
	Camera::SetTarget(XMFLOAT3(5, 3, 0));
}

//�X�V
void PlayScene::Update()
{
}

//�`��
void PlayScene::Draw()
{
}

//�J��
void PlayScene::Release()
{
}
