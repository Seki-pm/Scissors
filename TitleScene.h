#pragma once
#include "Engine/GameObject.h"
#include "Engine/SceneManager.h"
#include "Engine/Audio.h"
#include "Engine/Input.h"
#include "Engine/Image.h"

//�^�C�g���V�[�����Ǘ�����N���X
class TitleScene : public GameObject
{
	//���[�h�p�ϐ�
	enum Load
	{
		LOAD_MIN = 0,
		BackImage_,     //�w�i�摜
		TitleImage_,    //�^�C�g���摜
		SpaceKeyImage_, //SPACE�摜
		ScissorsSound_, //�n�T�~�̉�
		LOAD_MAX
	};

	//enum������z��
	int LoadHandle_[LOAD_MAX];

	//�^�C���𐔂���
	int TimerCnt;

	//�^�C�}�[�t���O
	bool Timer_;

	//�摜�̓����p�̕ϐ�
	float alpha_;
	float theta_;

	//Transform�ϐ�
	Transform TitleTrans;
	Transform SpaceTrans;

	//�萔
	const XMFLOAT3 TITLE_POS = XMFLOAT3(0, 0.3f, 0);  //�^�C�g���ʒu
	const XMFLOAT3 TITLE_SCA = XMFLOAT3(3, 3, 0);     //�^�C�g���T�C�Y
	const XMFLOAT3 SPACE_POS = XMFLOAT3(0, -0.6f, 0); //SPACE�ʒu
	const int TIMER_COUNT = 80;       //���Ԑ�����

public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	TitleScene(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	//�_��
	void Blinking();

	//���Ԍv��
	void Timer();
};