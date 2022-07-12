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
#include "ItemModel.h"
#include "ItemImage.h"
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

	int SelectSound_;      //�I����
	int DeterSound_;       //���艹


	const int Camera_Set_Pos;
	const int Camera_Fall_Max;
	const int Fall_Max;

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
};