#pragma once
#include "Engine/GameObject.h"
#include "Engine/SceneManager.h"
#include "Engine/Camera.h"
#include "Engine/Input.h"
#include "Engine/Image.h"
#include "Engine/Audio.h"
#include "GameOver.h"
#include "Global.h"
#include "HP.h"
#include "ItemModel.h"
#include "ItemImage.h"
#include "Pause.h"
#include "Scissors.h"
#include "Stage.h"
#include "StageSelectScene.h"
#include "GoalStaging.h"
#include "Sign.h"


//�X�e�[�W�V�[�����Ǘ�����N���X
class StageScene : public GameObject
{
	Stage* pStage_;
	Global global;


	int Gselect_; //GameOver�I��p�ϐ�
	int Pselect_; //Pause�I��p�ϐ�

	int BackImage_;

	//Scissors�̈ʒu���擾
	float Pos_X, Pos_Y, Pos_Z;

	int SelectSound_;      //�I����
	int DeterSound_;       //���艹

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
};