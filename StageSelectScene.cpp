#include "StageSelectScene.h"

#define St1_ItemImage_Pos XMFLOAT3(-0.4f, 0, 0); 
#define St2_ItemImage_Pos XMFLOAT3( 0.2f, 0, 0);
#define St3_ItemImage_Pos XMFLOAT3( 0.8f, 0, 0);

#define St1_Image_Pos XMFLOAT3(-0.6f, 0.2f, 0);
#define St2_Image_Pos XMFLOAT3(   0 , 0.2f, 0);
#define St3_Image_Pos XMFLOAT3( 0.6f, 0.2f, 0);

#define Easy_Position   XMFLOAT3(-0.6f, 0.5f, 0);
#define Normal_Position XMFLOAT3(   0 , 0.5f, 0);
#define Hard_Position   XMFLOAT3( 0.6f, 0.5f, 0);

#define Description_Pos XMFLOAT3(0.0f, -0.6f, 0);

#define ItemImage_Scale_Select XMFLOAT3(0.4f, 0.4f, 0.4f);

//�R���X�g���N�^
StageSelectScene::StageSelectScene(GameObject* parent)
	: GameObject(parent, "StageSelectScene"),
	FrameImageHandle_(-1), BackImage_(-1), SelectSound_(-1),
	DeterSound_(-1), DescriptionImage_(-1), LockSound_(-1),
	Drawflg(true)
{
	//STAGE_NUMBER ������
	for (int i = STAGE_NUMBER_1; i < STAGE_NUMBER_MAX; i++) {
		StageHandle_[i] = -1;
	}

	//STAGE_LEVEL ������
	for (int i = STAGE_LEVEL_EASY; i < STAGE_LEVEL_MAX; i++)
	{
		LevelHandle_[i] = -1;
	}

	//STAGE_LOCK ������
	for (int i = STAGE_LOCK_2; i < STAGE_LOCK_MAX; i++)
	{
		StageLockHandle_[i] = -1;
	}
}

//������
void StageSelectScene::Initialize()
{
	//�摜�f�[�^�̃��[�h
	//---------------------- STAGE ------------------------------

	StageHandle_[STAGE_NUMBER_1] = Image::Load("Image/StageSelectScene/STAGE1.png");
	assert(StageHandle_[STAGE_NUMBER_1] >= 0);
	Stage[STAGE_NUMBER_1].position_ = St1_Image_Pos;

	StageHandle_[STAGE_NUMBER_2] = Image::Load("Image/StageSelectScene/STAGE2.png");
	assert(StageHandle_[STAGE_NUMBER_2] >= 0);
	Stage[STAGE_NUMBER_2].position_ = St2_Image_Pos;

	StageHandle_[STAGE_NUMBER_3] = Image::Load("Image/StageSelectScene/STAGE3.png");
	assert(StageHandle_[STAGE_NUMBER_3] >= 0);
	Stage[STAGE_NUMBER_3].position_ = St3_Image_Pos;


	Image::SetTransform(StageHandle_[STAGE_NUMBER_1], Stage[STAGE_NUMBER_1]);
	Image::SetTransform(StageHandle_[STAGE_NUMBER_2], Stage[STAGE_NUMBER_2]);
	Image::SetTransform(StageHandle_[STAGE_NUMBER_3], Stage[STAGE_NUMBER_3]);

	//---------------------------------------------------

	//------------------- STAGE_ROCK --------------------------

	StageLockHandle_[STAGE_LOCK_2] = Image::Load("Image/StageSelectScene/Lock_Stage2.png");
	assert(StageLockHandle_[STAGE_LOCK_2] >= 0);
	Lock[STAGE_LOCK_2].position_ = St2_Image_Pos;

	StageLockHandle_[STAGE_LOCK_3] = Image::Load("Image/StageSelectScene/Lock_Stage3.png");
	assert(StageLockHandle_[STAGE_LOCK_3] >= 0);
	Lock[STAGE_LOCK_3].position_ = St3_Image_Pos;

	Image::SetTransform(StageLockHandle_[STAGE_LOCK_2], Lock[STAGE_LOCK_2]);
	Image::SetTransform(StageLockHandle_[STAGE_LOCK_3], Lock[STAGE_LOCK_3]);

	//--------------------------------------------------

	//-------------------- Level ---------------------------
	LevelHandle_[STAGE_LEVEL_EASY] = Image::Load("Image/StageSelectScene/Easy.png");
	assert(LevelHandle_[STAGE_LEVEL_EASY] >= 0);
	Level[STAGE_LEVEL_EASY].position_ = Easy_Position;

	LevelHandle_[STAGE_LEVEL_NORMAL] = Image::Load("Image/StageSelectScene/Normal.png");
	assert(LevelHandle_[STAGE_LEVEL_NORMAL] >= 0);
	Level[STAGE_LEVEL_NORMAL].position_ = Normal_Position;

	LevelHandle_[STAGE_LEVEL_HARD] = Image::Load("Image/StageSelectScene/Hard.png");
	assert(LevelHandle_[STAGE_LEVEL_HARD] >= 0);
	Level[STAGE_LEVEL_HARD].position_ = Hard_Position;

	Image::SetTransform(LevelHandle_[STAGE_LEVEL_EASY], Level[STAGE_LEVEL_EASY]);
	Image::SetTransform(LevelHandle_[STAGE_LEVEL_NORMAL], Level[STAGE_LEVEL_NORMAL]);
	Image::SetTransform(LevelHandle_[STAGE_LEVEL_HARD], Level[STAGE_LEVEL_HARD]);

	//---------------------------------------------------


	//--------------- �I��p�t���[�� ------------
	FrameImageHandle_ = Image::Load("Image/StageSelectScene/Frame.png");
	assert(FrameImageHandle_ >= 0);
	FrameTransform.position_ = St1_Image_Pos;
	Image::SetTransform(FrameImageHandle_, FrameTransform);


	BackImage_ = Image::Load("Image/TitleScene/Title_Back.png");
	assert(BackImage_ >= 0);
	//---------------------------------------------

	//---------------- ���� ----------------------
	DescriptionImage_ = Image::Load("Image/StageSelectScene/Description.png");
	assert(DescriptionImage_ >= 0);
	auto DescTrans = Transform();
	DescTrans.position_ = Description_Pos;
	Image::SetTransform(DescriptionImage_, DescTrans);
	//--------------------------------------------


	//------------- �� ----------------------------------

	//------ Select --------------
	SelectSound_ = Audio::Load("Sound/Title&Menu/Select.wav");
	assert(SelectSound_ >= 0);

	//------ Determination -------------
	DeterSound_ = Audio::Load("Sound/Title&Menu/Determination.wav");
	assert(DeterSound_ >= 0);

	//------------ ���b�N�� -----------
	LockSound_ = Audio::Load("Sound/Title&Menu/KeyLock.wav");
	assert(LockSound_ >= 0);

	//----------------------------------------------------
}

//�X�V
void StageSelectScene::Update()
{
	//�X�y�[�X���������Ƃ���
	if (Input::IsKeyDown(DIK_SPACE) || Input::IsMouseButtonDown(0))
	{
		//1�Ȃ�STAGE1��
		if (Global::SelectStage == STAGE_NUMBER_1 ||
			Global::SelectStage == STAGE_NUMBER_2 && Global::Unlock2 || 
			Global::SelectStage == STAGE_NUMBER_3 && Global::Unlock3)
		{
			Audio::Play(DeterSound_); //��
			SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
			pSceneManager->ChangeScene(SCENE_ID_STAGE);
		}
		else
		{
			Audio::Play(LockSound_); //�~
		}
	}

	//�B���R�}���h �S�X�e�[�W�A�����b�N
	if (Input::IsKeyDown(DIK_LSHIFT))
	{
		Global::Unlock2 = true;
		Global::Unlock3 = true;
	}

	//�I��
	MouseSelect();
	Select();
}

//�I��
void StageSelectScene::Select()
{
	//�����L�[�őI��
	if (Input::IsKeyDown(DIK_RIGHT))
	{
		Audio::Play(SelectSound_);

		switch (Global::SelectStage)
		{
		case STAGE_NUMBER_1:
			Global::SelectStage = STAGE_NUMBER_2; break;
		case STAGE_NUMBER_2:
			Global::SelectStage = STAGE_NUMBER_3; break;
		case STAGE_NUMBER_3:
			Global::SelectStage = STAGE_NUMBER_1; break;
		}
	}

	if (Input::IsKeyDown(DIK_LEFT))
	{
		Audio::Play(SelectSound_);

		switch (Global::SelectStage)
		{
		case STAGE_NUMBER_1:
			Global::SelectStage = STAGE_NUMBER_3; break;
		case STAGE_NUMBER_2:
			Global::SelectStage = STAGE_NUMBER_1; break;
		case STAGE_NUMBER_3:
			Global::SelectStage = STAGE_NUMBER_2; break;
		}
	}

	//�t���[���̈ʒu�ύX
	switch (Global::SelectStage)
	{
	case STAGE_NUMBER_1:
		FrameTransform.position_ = St1_Image_Pos;
		break;
	case STAGE_NUMBER_2:
		FrameTransform.position_ = St2_Image_Pos;
		break;
	case STAGE_NUMBER_3:
		FrameTransform.position_ = St3_Image_Pos;
		break;
	}
}

//�}�E�X�őI��
void StageSelectScene::MouseSelect()
{
	//�}�E�X�J�[�\���̈ʒu���擾
	XMFLOAT3 mousePos = Input::GetMousePosition();

	//Stage1��
	if ( 132 < mousePos.x && mousePos.x < 388 && 
		 228 < mousePos.y && mousePos.y < 356)
	{
		Global::SelectStage = STAGE_NUMBER_1;
	}
	//Stage2��
	else if (513 < mousePos.x && mousePos.x < 765 &&
		     226 < mousePos.y && mousePos.y < 351)
	{
		Global::SelectStage = STAGE_NUMBER_2;
	}
	//Stage3��
	else if (897 < mousePos.x && mousePos.x < 1148 &&
		     224 < mousePos.y && mousePos.y < 347)
	{
		Global::SelectStage = STAGE_NUMBER_3;
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
	//STAGE_NUMBER �J��
	for (int i = STAGE_NUMBER_1; i < STAGE_NUMBER_MAX; i++) {
		StageHandle_[i] = -1;
	}

	//STAGE_LEVEL �J��
	for (int i = STAGE_LEVEL_EASY; i < STAGE_LEVEL_MAX; i++)
	{
		LevelHandle_[i] = -1;
	}

	//STAGE_LOCK �J��
	for (int i = STAGE_LOCK_2; i < STAGE_LOCK_MAX; i++)
	{
		StageLockHandle_[i] = -1;
	}

	FrameImageHandle_ = -1;
	DescriptionImage_ = -1;
	SelectSound_ = -1;
	DeterSound_ = -1;
	BackImage_ = -1;
	LockSound_ = -1;
}

//�X�e�[�W�̃��b�N�����Ǘ�
void StageSelectScene::StageUnlock()
{
	Image::Draw(StageHandle_[STAGE_NUMBER_1]);

	//�A�����b�N�t���O����ɕ`��̓��e��ς���
	if (Global::Unlock2){
		Image::Draw(StageHandle_[STAGE_NUMBER_2]);
	}
	else{
		Image::Draw(StageLockHandle_[STAGE_LOCK_2]);
	}

	if (Global::Unlock3){
		Image::Draw(StageHandle_[STAGE_NUMBER_3]);
	}
	else{
		Image::Draw(StageLockHandle_[STAGE_LOCK_3]);
	}
}

//�R�C���̎擾��
void StageSelectScene::GetCoin()
{
	//��x�����`��
	if (Drawflg)
	{
		Global::ItemImageSca = ItemImage_Scale_Select; //�\���T�C�Y

		//Stage1�̃R�C��
		if (Global::GetCoin_1)
		{
			Global::ItemImagePos = St1_ItemImage_Pos //�\���ʒu
			Instantiate<ItemImage>(this);            //�\��
		}
		//Stage2�̃R�C��
		if (Global::GetCoin_2)
		{
			Global::ItemImagePos = St2_ItemImage_Pos//�\���ʒu
			Instantiate<ItemImage>(this);          //�\��
		}
		//Stage3�̃R�C��
		if (Global::GetCoin_3)
		{
			Global::ItemImagePos = St3_ItemImage_Pos //�\���ʒu
			Instantiate<ItemImage>(this);            //�\��
		}

		Drawflg = false;
	}
}

XMFLOAT4 StageSelectScene::ImagePos(int x, int y)
{
	int x2 = x + 256;
	int y2 = y + 128;

	return XMFLOAT4(x,y,x2,y2);
}
