#include "StageSelectScene.h"

//�R���X�g���N�^
StageSelectScene::StageSelectScene(GameObject* parent)
	: GameObject(parent, "StageSelectScene"),
	FrameImageHandle_(-1)
{
	for (int i = 1; i < STAGE_NUMBER_MAX; i++) {
		StageHandle_[i] = -1;
	}

	for (int i = 0; i < STAGE_LEVEL_MAX; i++)
	{
		LevelImageHandle_[i] = -1;
	}
}

//������
void StageSelectScene::Initialize()
{
	//�摜�f�[�^�̃��[�h
	//-------------- STAGE ------------------------------

	StageHandle_[STAGE_NUMBER_1] = Image::Load("Image/STAGE1.png");
	assert(StageHandle_[STAGE_NUMBER_1] >= 0);
	Stage[STAGE_NUMBER_1].position_ = XMFLOAT3(-0.6f, 0.2f, 0);

	StageHandle_[STAGE_NUMBER_2] = Image::Load("Image/Rock_Stage2.png");
	assert(StageHandle_[STAGE_NUMBER_2] >= 0);
	Stage[STAGE_NUMBER_2].position_ = XMFLOAT3(0, 0.2f, 0);

	StageHandle_[STAGE_NUMBER_3] = Image::Load("Image/Rock_Stage3.png");
	assert(StageHandle_[STAGE_NUMBER_3] >= 0);
	Stage[STAGE_NUMBER_3].position_ = XMFLOAT3(0.6f, 0.2f, 0);


	Image::SetTransform(StageHandle_[STAGE_NUMBER_1], Stage[STAGE_NUMBER_1]);
	Image::SetTransform(StageHandle_[STAGE_NUMBER_2], Stage[STAGE_NUMBER_2]);
	Image::SetTransform(StageHandle_[STAGE_NUMBER_3], Stage[STAGE_NUMBER_3]);

	//---------------------------------------------------

	//-------------- Level ---------------------------
	LevelImageHandle_[STAGE_LEVEL_EASY] = Image::Load("Image/Easy.png");
	assert(LevelImageHandle_[STAGE_LEVEL_EASY] >= 0);
	Level[STAGE_LEVEL_EASY].position_ = XMFLOAT3(-0.6f, 0.5f, 0);

	LevelImageHandle_[STAGE_LEVEL_NORMAL] = Image::Load("Image/Normal.png");
	assert(LevelImageHandle_[STAGE_LEVEL_NORMAL] >= 0);
	Level[STAGE_LEVEL_NORMAL].position_ = XMFLOAT3(0, 0.5f, 0);

	LevelImageHandle_[STAGE_LEVEL_HARD] = Image::Load("Image/Hard.png");
	assert(LevelImageHandle_[STAGE_LEVEL_HARD] >= 0);
	Level[STAGE_LEVEL_HARD].position_ = XMFLOAT3(0.6f, 0.5f, 0);

	Image::SetTransform(LevelImageHandle_[STAGE_LEVEL_EASY], Level[STAGE_LEVEL_EASY]);
	Image::SetTransform(LevelImageHandle_[STAGE_LEVEL_NORMAL], Level[STAGE_LEVEL_NORMAL]);
	Image::SetTransform(LevelImageHandle_[STAGE_LEVEL_HARD], Level[STAGE_LEVEL_HARD]);

	//------------------------------------------------

	FrameImageHandle_ = Image::Load("Image/Frame.png");
	assert(FrameImageHandle_ >= 0);
	FrameTransform.position_ = XMFLOAT3(-0.6f, 0.2f, 0);
	Image::SetTransform(FrameImageHandle_, FrameTransform);


}

//�X�V
void StageSelectScene::Update()
{
	//�X�y�[�X���������Ƃ���
	if (Input::IsKeyDown(DIK_SPACE))
	{
		//0�Ȃ�STAGE1��
		if (Global::Select == 0)
		{
			SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
			pSceneManager->ChangeScene(SCENE_ID_STAGE1);
		}
		//1����STAGE2���A�����b�N����Ă���Ȃ�
		else if (Global::Select == 1 && Global::Unlock2)
		{
			SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
			pSceneManager->ChangeScene(SCENE_ID_STAGE2);
		}
		else if (Global::Select == 2 && Global::Unlock3)
		{
			SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
			pSceneManager->ChangeScene(SCENE_ID_STAGE2);
		}
	}

	if (Input::IsKeyDown(DIK_P))
	{

		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_PLAY);

	}



	//�I��
	Select();
}

//�I��
void StageSelectScene::Select()
{
	if (Input::IsKeyDown(DIK_RIGHT))
	{
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


	//STAGE���̕`��
	for (int i = 1; i < STAGE_NUMBER_MAX; i++)
	{
		Image::Draw(StageHandle_[i]);
	}

	//STAGE��Փx�̕`��
	for (int i = 0; i < STAGE_LEVEL_MAX; i++)
	{
		Image::Draw(LevelImageHandle_[i]);
	}

	Image::SetTransform(FrameImageHandle_, FrameTransform);
	Image::Draw(FrameImageHandle_);
}

//�J��
void StageSelectScene::Release()
{
	for (int i = 1; i < STAGE_NUMBER_MAX; i++) {
		StageHandle_[i] = -1;
	}

	for (int i = 0; i < STAGE_LEVEL_MAX; i++)
	{
		LevelImageHandle_[i] = -1;
	}

	FrameImageHandle_ = -1;
}