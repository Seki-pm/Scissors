#pragma once
#include "Engine/GameObject.h"
#include "Engine/SceneManager.h"
#include "Engine/Camera.h"
#include "Engine/Input.h"
#include "Engine/Image.h"
#include "Engine/Audio.h"
#include "DrawNumber.h"
#include "GameOver.h"
#include "Global.h"
#include "GoalStaging.h"
#include "ItemImage.h"
#include "ItemModel.h"
#include "HP.h"
#include "Pause.h"
#include "Scissors.h"
#include "Sign.h"
#include "Stage.h"


//STAGE1�V�[�����Ǘ�����N���X
class Stage3Scene : public GameObject
{
	Global gl;

	DrawNumber* pNumber_; //�f�o�b�N�p

	float X, Y, Z;   //�󂯎��e���W�n

	int Gselect_; //GameOver�I��p�ϐ�
	int Pselect_; //Pause�I��p�ϐ�

	int BackImage_;   //�w�i�摜

	bool Itemflg;          //�A�C�e���̏o���t���O
	int cnt;               //�J�E���g�p

	int SelectSound_;      //�I����
	int DeterSound_;       //���艹

public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	Stage3Scene(GameObject* parent);

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