#pragma once
#include "Engine/GameObject.h"
#include "Engine/SceneManager.h"
#include "Engine/Camera.h"
#include "Engine/Input.h"
#include "Engine/Model.h"
#include "PolygonCollider.h"
#include "Stage.h"
#include "Scissors.h"
#include "Global.h"
#include "HP.h"
#include "ItemModel.h"

//�X�e�[�W2�V�[�����Ǘ�����N���X
class Stage2Scene : public GameObject
{

	Scissors* pScissors;
	float X, Y, Z;

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

	//�J�����ړ�
	void CameraMove(float start, float goal);

	void Collider();

};