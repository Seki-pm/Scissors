#pragma once
#include "Engine/GameObject.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"
#include "Engine/Image.h"
#include "Engine/Transform.h"
#include "Global.h"

enum STAGE_NUMBER
{
	STAGE_NUMBER_MIN = 0,
	STAGE_NUMBER_1 = 1,
	STAGE_NUMBER_2 = 2,
	STAGE_NUMBER_3 = 3,
	STAGE_NUMBER_MAX
};

enum STAGE_LEVEL
{
	STAGE_LEVEL_EASY = 0,
	STAGE_LEVEL_NORMAL,
	STAGE_LEVEL_HARD,
	STAGE_LEVEL_MAX
};


//�X�e�[�W�I���V�[�����Ǘ�����N���X
class StageSelectScene : public GameObject
{
private:
	int StageHandle_[STAGE_NUMBER_MAX];
	int LevelImageHandle_[STAGE_LEVEL_MAX];
	int FrameImageHandle_;


	Transform Stage[STAGE_NUMBER_MAX];
	Transform Level[STAGE_LEVEL_MAX];
	Transform FrameTransform;

public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	StageSelectScene(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�I��
	void Select();

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
};