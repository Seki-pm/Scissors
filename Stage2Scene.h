#pragma once
#include "Engine/GameObject.h"
#include "Engine/SceneManager.h"
#include "Engine/Camera.h"
#include "Engine/Input.h"
#include "Engine/Image.h"
#include "GameOver.h"
#include "Global.h"
#include "GoalStaging.h"
#include "HP.h"
#include "ItemImage.h"
#include "ItemModel.h"
#include "Pause.h"
#include "Scissors.h"
#include "Stage.h"


//STAGE2�V�[�����Ǘ�����N���X
class Stage2Scene : public GameObject
{
	ItemModel* pItemModel_;

	float X, Y, Z;

	int Gselect_; //GameOver�I��p�ϐ�
	int Pselect_; //Pause�I��p�ϐ�

	int BackImage_;

public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	Stage2Scene(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	//GAMEOVER
	void GameOverSEL();

	//�ꎞ��~
	void PauseSEL();

	//�J�����ړ�
	void CameraMove(float start, float goal);

};