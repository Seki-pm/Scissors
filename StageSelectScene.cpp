#include "StageSelectScene.h"

//�R���X�g���N�^
StageSelectScene::StageSelectScene(GameObject* parent)
	: GameObject(parent, "StageSelectScene"),
	FrameImageHandle_(-1), BackImage_(-1), SelectSound_(-1),
	DeterSound_(-1), DescriptionImage_(-1), Drawflg(true)
{
	for (int i = 1; i < STAGE_NUMBER_MAX; i++) {
		StageHandle_[i] = -1;
	}

	for (int i = 0; i < STAGE_LEVEL_MAX; i++)
	{
		LevelHandle_[i] = -1;
	}

	for (int i = STAGE_LOCK_MIN; i < STAGE_LOCK_MAX; i++)
	{
		StageLockHandle_[i] = -1;
	}
}

//������
void StageSelectScene::Initialize()
{


	//�摜�f�[�^�̃��[�h
	//---------------------- STAGE ------------------------------

	StageHandle_[STAGE_NUMBER_1] = Image::Load("Image/STAGE1.png");
	assert(StageHandle_[STAGE_NUMBER_1] >= 0);
	Stage[STAGE_NUMBER_1].position_ = XMFLOAT3(-0.6f, 0.2f, 0);

	StageHandle_[STAGE_NUMBER_2] = Image::Load("Image/STAGE2.png");
	assert(StageHandle_[STAGE_NUMBER_2] >= 0);
	Stage[STAGE_NUMBER_2].position_ = XMFLOAT3(0, 0.2f, 0);

	StageHandle_[STAGE_NUMBER_3] = Image::Load("Image/STAGE3.png");
	assert(StageHandle_[STAGE_NUMBER_3] >= 0);
	Stage[STAGE_NUMBER_3].position_ = XMFLOAT3(0.6f, 0.2f, 0);


	Image::SetTransform(StageHandle_[STAGE_NUMBER_1], Stage[STAGE_NUMBER_1]);
	Image::SetTransform(StageHandle_[STAGE_NUMBER_2], Stage[STAGE_NUMBER_2]);
	Image::SetTransform(StageHandle_[STAGE_NUMBER_3], Stage[STAGE_NUMBER_3]);

	//---------------------------------------------------

	//------------------- STAGE_ROCK --------------------------

	StageLockHandle_[STAGE_LOCK_2] = Image::Load("Image/Lock_Stage2.png");
	assert(StageLockHandle_[STAGE_LOCK_2] >= 0);
	Lock[STAGE_LOCK_2].position_ = XMFLOAT3(0, 0.2f, 0);

	StageLockHandle_[STAGE_LOCK_3] = Image::Load("Image/Lock_Stage3.png");
	assert(StageLockHandle_[STAGE_LOCK_3] >= 0);
	Lock[STAGE_LOCK_3].position_ = XMFLOAT3(0.6f, 0.2f, 0);

	Image::SetTransform(StageLockHandle_[STAGE_LOCK_2], Lock[STAGE_LOCK_2]);
	Image::SetTransform(StageLockHandle_[STAGE_LOCK_3], Lock[STAGE_LOCK_3]);

	//--------------------------------------------------

	//-------------------- Level ---------------------------
	LevelHandle_[STAGE_LEVEL_EASY] = Image::Load("Image/Easy.png");
	assert(LevelHandle_[STAGE_LEVEL_EASY] >= 0);
	Level[STAGE_LEVEL_EASY].position_ = XMFLOAT3(-0.6f, 0.5f, 0);

	LevelHandle_[STAGE_LEVEL_NORMAL] = Image::Load("Image/Normal.png");
	assert(LevelHandle_[STAGE_LEVEL_NORMAL] >= 0);
	Level[STAGE_LEVEL_NORMAL].position_ = XMFLOAT3(0, 0.5f, 0);

	LevelHandle_[STAGE_LEVEL_HARD] = Image::Load("Image/Hard.png");
	assert(LevelHandle_[STAGE_LEVEL_HARD] >= 0);
	Level[STAGE_LEVEL_HARD].position_ = XMFLOAT3(0.6f, 0.5f, 0);

	Image::SetTransform(LevelHandle_[STAGE_LEVEL_EASY], Level[STAGE_LEVEL_EASY]);
	Image::SetTransform(LevelHandle_[STAGE_LEVEL_NORMAL], Level[STAGE_LEVEL_NORMAL]);
	Image::SetTransform(LevelHandle_[STAGE_LEVEL_HARD], Level[STAGE_LEVEL_HARD]);

	//---------------------------------------------------


	//--------------- �I��p�t���[�� ------------
	FrameImageHandle_ = Image::Load("Image/Frame.png");
	assert(FrameImageHandle_ >= 0);
	FrameTransform.position_ = XMFLOAT3(-0.6f, 0.2f, 0);
	Image::SetTransform(FrameImageHandle_, FrameTransform);


	BackImage_ = Image::Load("Image/Title_Back.png");
	assert(BackImage_ >= 0);
	//---------------------------------------------

	//---------------- ���� ----------------------
	DescriptionImage_ = Image::Load("Image/Description.png");
	assert(DescriptionImage_ >= 0);
	auto DescTrans = Transform();
	DescTrans.position_ = XMFLOAT3(0.0f, -0.5f, 0);
	Image::SetTransform(DescriptionImage_, DescTrans);
	//--------------------------------------------

	//------------- �� ----------------------------------

	//------ Select --------------
	SelectSound_ = Audio::Load("Sound/Select.wav");
	assert(SelectSound_ >= 0);

	//------ Determination -------------

	DeterSound_ = Audio::Load("Sound/Determination.wav");
	assert(DeterSound_ >= 0);

	//----------------------------------------------------
}

//�X�V
void StageSelectScene::Update()
{
	//�X�y�[�X���������Ƃ���
	if (Input::IsKeyDown(DIK_SPACE))
	{
		Audio::Play(DeterSound_);

		//0�Ȃ�STAGE1��
		if (Global::Select == 0)
		{
			SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
			pSceneManager->ChangeScene(SCENE_ID_STAGE1);
		}
		//1����STAGE2���A�����b�N����Ă���Ȃ�STAGE2��
		else if (Global::Select == 1 && Global::Unlock2)
		{
			SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
			pSceneManager->ChangeScene(SCENE_ID_STAGE2);
		}
		//2���N���A���Ă�Ȃ�
		else if (Global::Select == 2 && Global::Unlock3)
		{
			//SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
			//pSceneManager->ChangeScene(SCENE_ID_STAGE2);
		}
	}


	//�I��
	Select();
}

//�I��
void StageSelectScene::Select()
{
	//�����őI��
	if (Input::IsKeyDown(DIK_RIGHT))
	{
		Audio::Play(SelectSound_);

		switch (Global::Select)
		{
		case 0:
			Global::Select = 1;
			FrameTransform.position_ = XMFLOAT3(0, 0.2f, 0);
			break;
		case 1:
			Global::Select = 2;
			FrameTransform.position_ = XMFLOAT3(0.6f, 0.2f, 0);
			break;
		case 2:
			Global::Select = 0;
			FrameTransform.position_ = XMFLOAT3(-0.6f, 0.2f, 0);
			break;
		}
	}

	if (Input::IsKeyDown(DIK_LEFT))
	{
		Audio::Play(SelectSound_);

		switch (Global::Select)
		{
		case 0:
			Global::Select = 2;
			FrameTransform.position_ = XMFLOAT3(0.6f, 0.2f, 0);
			break;
		case 1:
			Global::Select = 0;
			FrameTransform.position_ = XMFLOAT3(-0.6f, 0.2f, 0);
			break;
		case 2:
			Global::Select = 1;
			FrameTransform.position_ = XMFLOAT3(0, 0.2f, 0);
			break;
		}
	}
}

//�`��
void StageSelectScene::Draw()
{
	Image::Draw(BackImage_);
	Image::Draw(DescriptionImage_);

	//STAGE��Փx�̕`��
	for (int i = 0; i < STAGE_LEVEL_MAX; i++)
	{
		Image::Draw(LevelHandle_[i]);
	}

	//�X�e�[�W�̃��b�N����
	StageUnlock();

	Image::SetTransform(FrameImageHandle_, FrameTransform);
	Image::Draw(FrameImageHandle_);

	//�R�C���̎擾��
	GetCoin();
}

//�J��
void StageSelectScene::Release()
{
	for (int i = 1; i < STAGE_NUMBER_MAX; i++) {
		StageHandle_[i] = -1;
	}

	for (int i = 0; i < STAGE_LEVEL_MAX; i++)
	{
		LevelHandle_[i] = -1;
	}

	for (int i = STAGE_LOCK_MIN; i < STAGE_LOCK_MAX; i++)
	{
		StageLockHandle_[i] = -1;
	}

	FrameImageHandle_ = -1;
	BackImage_ = -1;
	SelectSound_ = -1;
	DeterSound_ = -1;
}

//�X�e�[�W�̃��b�N�����Ǘ�
void StageSelectScene::StageUnlock()
{
	Image::Draw(StageHandle_[STAGE_NUMBER_1]);

	if (Global::Unlock2)
	{
		Image::Draw(StageHandle_[STAGE_NUMBER_2]);
	}
	else
	{
		Image::Draw(StageLockHandle_[STAGE_LOCK_2]);
	}

	if (Global::Unlock3)
	{
		Image::Draw(StageHandle_[STAGE_NUMBER_3]);
	}
	else
	{
		Image::Draw(StageLockHandle_[STAGE_LOCK_3]);
	}
}

//�R�C���̎擾��
void StageSelectScene::GetCoin()
{
	if (Drawflg)
	{
		//Stage1�̃R�C��
		if (Global::GetCoin_1)
		{
			Global::ItemImagePos = XMFLOAT3(-0.6f, 0, 0); //�\���ʒu
			Instantiate<ItemImage>(this);          //�\��
		}

		//Stage2�̃R�C��
		if (Global::GetCoin_2)
		{
			Global::ItemImagePos = XMFLOAT3(0.2f, 0, 0); //�\���ʒu
			Instantiate<ItemImage>(this);           //�\��
		}
	}

	Drawflg = false;
}
