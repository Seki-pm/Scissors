#pragma once
#include "Engine/GameObject.h"
#include "Engine/SceneManager.h"
#include "DrawNumber.h"
#include "DrawGauge.h"
#include "Scissors.h"
#include "Global.h"
#include "GameOver.h"


//STAGE1�V�[�����Ǘ�����N���X
class Stage1Scene : public GameObject
{
	Scissors* pScissors;  //Scissors�̃|�C���^
	DrawNumber* pNumber_; //�f�o�b�N�p
	DrawGauge*  pGauge_;  //HP�Q�[�W�p
	float X, Y, Z;

	int ImageHandle_;
	int GaugeHandle_;

	int MaxHp;
	int select_;

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