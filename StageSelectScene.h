#pragma once
#include "Engine/GameObject.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"
#include "Engine/Image.h"
#include "Engine/Transform.h"
#include "Engine/Audio.h"
#include "Global.h"

//�X�e�[�W�ԍ�
enum STAGE_NUMBER
{
	STAGE_NUMBER_MIN = 0,
	STAGE_NUMBER_1 = 1,
	STAGE_NUMBER_2 = 2,
	STAGE_NUMBER_3 = 3,
	STAGE_NUMBER_MAX
};

//�X�e�[�W���b�N
enum STAGE_LOCK
{
	STAGE_LOCK_MIN = 1,
	STAGE_LOCK_2 = 2,
	STAGE_LOCK_3 = 3,
	STAGE_LOCK_MAX
};

//�X�e�[�W���x��
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

	//enum�̂��̂�z��ɂ��Ă�
	int StageHandle_[STAGE_NUMBER_MAX];       
	int StageLockHandle_[STAGE_LOCK_MAX];
	int LevelHandle_[STAGE_LEVEL_MAX];

	int FrameImageHandle_; //�t���[��
	int BackImage_;        //�w�i
	int DescriptionImage_; //����
	int SelectSound_;      //�I����
	int DeterSound_;       //���艹

	//�etransform
	Transform Stage[STAGE_NUMBER_MAX];
	Transform Lock[STAGE_LOCK_MAX];
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

	//�X�e�[�W�A�����b�N
	void StageUnlock();
};