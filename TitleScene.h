#pragma once
#include "Engine/GameObject.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"
#include "Engine/Image.h"

//�^�C�g���V�[�����Ǘ�����N���X
class TitleScene : public GameObject
{
	int BackImageHandle_;
	int TitleImageHandle_;
	int SpaceKeyImageHandle_;

	float size_;

	Transform TitleTrans;
	Transform SpaceTrans;

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
};