#pragma once
#include "Engine/GameObject.h"
#include "Engine/SceneManager.h"
#include "Engine/Audio.h"
#include "Engine/Input.h"
#include "Engine/Image.h"


//�^�C�g���V�[�����Ǘ�����N���X
class TitleScene : public GameObject
{
	//�摜�p�ϐ�
	int BackImage_;
	int TitleImage_;
	int SpaceKeyImage_;

	//���p�ϐ�
	int ScissorsSound_;

	//�^�C���𐔂���
	int TimerCnt;

	//
	bool Timer_;

	//�摜�̓����p�̕ϐ�
	float alpha_;
	float theta_;

	//Transform�ϐ�
	Transform TitleTrans;
	Transform SpaceTrans;

	//�萔
	const XMFLOAT3 TITLE_POS; //�^�C�g���̈ʒu
	const XMFLOAT3 TITLE_SCA; //�^�C�g���̑傫��
	const XMFLOAT3 SPACE_POS; //SPACE�̈ʒu
	const int TIMER_COUNT;    //���Ԍv��

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