#pragma once
#include "Engine/GameObject.h"
#include "Engine/SceneManager.h"
#include "Engine/Audio.h"
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
#include "Sign.h"
#include "Stage.h"
#include "StageSelectScene.h"



//�X�e�[�W�V�[�����Ǘ�����N���X
class StageScene : public GameObject
{
	Global gl;




	int Gselect_; //GameOver�I��p�ϐ�
	int Pselect_; //Pause�I��p�ϐ�

	//�萔
	const float CAMERA_SET_POS = -10.f;  //�J�����ʒu
	const float CAMERA_FALL_MAX = -3.f;  //�������̃J�������E
	const int FALL_MAX = -8;             //Player�̗������E
	const XMFLOAT3 ITEMIMAGE_SCALE_STAGE = XMFLOAT3(0.5f,0.5f,0.5f);     //�A�C�e���摜�̃T�C�Y
	const XMFLOAT3 ITEMIMAGE_POSITION_STAGE = XMFLOAT3(0.9f, 0.8f, 0.f); //�A�C�e���摜�̈ʒu

public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	StageScene(GameObject* parent);

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

	//���̃X�e�[�W���A�����b�N
	void NextStageUnlock(int SelectStage);

	//�S�[�����o�p
	void Timer();

	//�e�X�e�[�W�̃R�C������肵�����ǂ����̔���
	void GetCoinJudge();
};