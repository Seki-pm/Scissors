#pragma once
#include "Engine/GameObject.h"
#include "Engine/SceneManager.h"
#include "Engine/Camera.h"
#include "Engine/Input.h"
#include "DrawGauge.h"
#include "DrawNumber.h"
#include "GameOver.h"
#include "Global.h"
#include "GoalStaging.h"
#include "HP.h"
#include "Scissors.h"
#include "Sign.h"
#include "Stage.h"




//STAGE1�V�[�����Ǘ�����N���X
class Stage1Scene : public GameObject
{
	Scissors* pScissors;  //Scissors�̃|�C���^
	DrawNumber* pNumber_; //�f�o�b�N�p
	DrawGauge*  pGauge_;  //HP�Q�[�W�p

	float X, Y, Z;   //�󂯎��e���W�n

	int select_; //�I��p�ϐ�

public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	Stage1Scene(GameObject* parent);

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

	//�J�����ړ�
	void CameraMove(float start, float goal);
};