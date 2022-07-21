#include "StageSelectScene.h"


//�R���X�g���N�^
StageSelectScene::StageSelectScene(GameObject* parent)
	: GameObject(parent, "StageSelectScene"),
	  Drawflg(true)
{
	//STAGE_NUMBER ������
	for (int i = STAGE_NUMBER_1; i < STAGE_NUMBER_MAX; i++) {
		StageHandle_[i] = INITIAL_ERROR_VALUE;
	}

	//STAGE_LEVEL ������
	for (int i = STAGE_LEVEL_EASY; i < STAGE_LEVEL_MAX; i++)
	{
		LevelHandle_[i] = INITIAL_ERROR_VALUE;
	}

	//STAGE_LOCK ������
	for (int i = STAGE_LOCK_2; i < STAGE_LOCK_MAX; i++)
	{
		StageLockHandle_[i] = INITIAL_ERROR_VALUE;
	}

	//SELECT_SOUND ������
	for (int i = SOUND_SELECT; i < SOUND_MAX; i++)
	{
		SoundHandle_[i] = INITIAL_ERROR_VALUE;
	}

	//Load ������
	for (int i = LOAD_MIN + 1; i < LOAD_MAX; i++)
	{
		LoadHandle_[i] = INITIAL_ERROR_VALUE;
	}
}

//������
void StageSelectScene::Initialize()
{
	//�摜�f�[�^�̃��[�h
	//---------------------- STAGE ----------------------
	{
		StageHandle_[STAGE_NUMBER_1] = Image::Load("Image/StageSelectScene/STAGE1.png");
		assert(StageHandle_[STAGE_NUMBER_1] >= 0);
		Stage[STAGE_NUMBER_1].position_ = ST1_IMAGE_POS;

		StageHandle_[STAGE_NUMBER_2] = Image::Load("Image/StageSelectScene/STAGE2.png");
		assert(StageHandle_[STAGE_NUMBER_2] >= 0);
		Stage[STAGE_NUMBER_2].position_ = ST2_IMAGE_POS;

		StageHandle_[STAGE_NUMBER_3] = Image::Load("Image/StageSelectScene/STAGE3.png");
		assert(StageHandle_[STAGE_NUMBER_3] >= 0);
		Stage[STAGE_NUMBER_3].position_ = ST3_IMAGE_POS;


		Image::SetTransform(StageHandle_[STAGE_NUMBER_1], Stage[STAGE_NUMBER_1]);
		Image::SetTransform(StageHandle_[STAGE_NUMBER_2], Stage[STAGE_NUMBER_2]);
		Image::SetTransform(StageHandle_[STAGE_NUMBER_3], Stage[STAGE_NUMBER_3]);
	}
	//---------------------------------------------------

	//------------------- STAGE_ROCK --------------------
	{
		StageLockHandle_[STAGE_LOCK_2] = Image::Load("Image/StageSelectScene/Lock_Stage2.png");
		assert(StageLockHandle_[STAGE_LOCK_2] >= 0);
		Lock[STAGE_LOCK_2].position_ = ST2_IMAGE_POS;

		StageLockHandle_[STAGE_LOCK_3] = Image::Load("Image/StageSelectScene/Lock_Stage3.png");
		assert(StageLockHandle_[STAGE_LOCK_3] >= 0);
		Lock[STAGE_LOCK_3].position_ = ST3_IMAGE_POS;

		Image::SetTransform(StageLockHandle_[STAGE_LOCK_2], Lock[STAGE_LOCK_2]);
		Image::SetTransform(StageLockHandle_[STAGE_LOCK_3], Lock[STAGE_LOCK_3]);
	}
	//---------------------------------------------------

	//---------------------- Level ----------------------
	{
		LevelHandle_[STAGE_LEVEL_EASY] = Image::Load("Image/StageSelectScene/Easy.png");
		assert(LevelHandle_[STAGE_LEVEL_EASY] >= 0);
		Level[STAGE_LEVEL_EASY].position_ = EASY_POSITION;

		LevelHandle_[STAGE_LEVEL_NORMAL] = Image::Load("Image/StageSelectScene/Normal.png");
		assert(LevelHandle_[STAGE_LEVEL_NORMAL] >= 0);
		Level[STAGE_LEVEL_NORMAL].position_ = NOMAL_POSITION;

		LevelHandle_[STAGE_LEVEL_HARD] = Image::Load("Image/StageSelectScene/Hard.png");
		assert(LevelHandle_[STAGE_LEVEL_HARD] >= 0);
		Level[STAGE_LEVEL_HARD].position_ = HARD_POSITION;

		Image::SetTransform(LevelHandle_[STAGE_LEVEL_EASY], Level[STAGE_LEVEL_EASY]);
		Image::SetTransform(LevelHandle_[STAGE_LEVEL_NORMAL], Level[STAGE_LEVEL_NORMAL]);
		Image::SetTransform(LevelHandle_[STAGE_LEVEL_HARD], Level[STAGE_LEVEL_HARD]);
	}
	//---------------------------------------------------


	//-------------------- Load�摜 ---------------------
	{
		//--------------- �I��p�t���[�� ------------
		LoadHandle_[FrameImage_] = Image::Load("Image/StageSelectScene/Frame.png");
		assert(LoadHandle_[FrameImage_] >= 0);
		FrameTransform.position_ = ST1_IMAGE_POS;
		Image::SetTransform(LoadHandle_[FrameImage_], FrameTransform);


		LoadHandle_[BackImage_] = Image::Load("Image/TitleScene/Title_Back.png");
		assert(BackImage_ >= 0);
		//---------------------------------------------

		//---------------- ���� ----------------------
		LoadHandle_[DescriptionImage_] = Image::Load("Image/StageSelectScene/Description.png");
		assert(LoadHandle_[DescriptionImage_] >= 0);
		auto DescTrans = Transform();
		DescTrans.position_ = DESCRIPTION_POS;
		Image::SetTransform(LoadHandle_[DescriptionImage_], DescTrans);
	}
	//---------------------------------------------------


	//----------------------- �� ------------------------
	{
		//------ Select --------------
		SoundHandle_[SOUND_SELECT] = Audio::Load("Sound/Title&Menu/Select.wav");
		assert(SoundHandle_[SOUND_SELECT] >= 0);

		//------ Determination -------------
		SoundHandle_[SOUND_DETERMINATION] = Audio::Load("Sound/Title&Menu/Determination.wav");
		assert(SoundHandle_[SOUND_DETERMINATION] >= 0);

		//------------ ���b�N�� -----------
		SoundHandle_[SOUND_LOCK] = Audio::Load("Sound/Title&Menu/KeyLock.wav");
		assert(SoundHandle_[SOUND_LOCK] >= 0);
	}
	//---------------------------------------------------
}

//�X�V
void StageSelectScene::Update()
{
	//�X�y�[�X���������Ƃ���
	if (Input::IsKeyDown(DIK_SPACE) || Input::IsMouseButtonDown(0))
	{
		//1�Ȃ�STAGE1��
		if (Global::SelectStage == STAGE_NUMBER_1 ||
			Global::SelectStage == STAGE_NUMBER_2 && Global::stage2.UnLock ||
			Global::SelectStage == STAGE_NUMBER_3 && Global::stage3.UnLock)
		{
			Audio::Play(SoundHandle_[SOUND_DETERMINATION]); //��
			SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
			pSceneManager->ChangeScene(SCENE_ID_STAGE);
		}
		else
		{
			Audio::Play(SoundHandle_[SOUND_LOCK]); //�~
		}
	}

	//�B���R�}���h �S�X�e�[�W�A�����b�N
	if (Input::IsKeyDown(DIK_LSHIFT))
	{
		Global::stage2.UnLock = true;
		Global::stage3.UnLock = true;
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
		Audio::Play(SoundHandle_[SOUND_SELECT]);

		switch (Global::SelectStage)
		{
		case STAGE_NUMBER_1: Global::SelectStage = STAGE_NUMBER_2; break;
		case STAGE_NUMBER_2: Global::SelectStage = STAGE_NUMBER_3; break;
		case STAGE_NUMBER_3: Global::SelectStage = STAGE_NUMBER_1; break;
		}
	}

	if (Input::IsKeyDown(DIK_LEFT))
	{
		Audio::Play(SoundHandle_[SOUND_SELECT]);

		switch (Global::SelectStage)
		{
		case STAGE_NUMBER_1: Global::SelectStage = STAGE_NUMBER_3; break;
		case STAGE_NUMBER_2: Global::SelectStage = STAGE_NUMBER_1; break;
		case STAGE_NUMBER_3: Global::SelectStage = STAGE_NUMBER_2; break;
		}
	}

	//�t���[���̈ʒu�ύX
	switch (Global::SelectStage)
	{
	case STAGE_NUMBER_1: FrameTransform.position_ = ST1_IMAGE_POS; break;
	case STAGE_NUMBER_2: FrameTransform.position_ = ST2_IMAGE_POS; break;
	case STAGE_NUMBER_3: FrameTransform.position_ = ST3_IMAGE_POS; break;
	}
}

//�}�E�X�őI��
void StageSelectScene::MouseSelect()
{
	//�}�E�X�J�[�\���̈ʒu���擾
	XMFLOAT3 mousePos = Input::GetMousePosition();

	//Stage1��
	if (ST1_MOUSE_POS.x < mousePos.x && mousePos.x < ST1_MOUSE_POS.z &&
		ST1_MOUSE_POS.y < mousePos.y && mousePos.y < ST1_MOUSE_POS.w)
	{
		Global::SelectStage = STAGE_NUMBER_1;
	}
	//Stage2��
	else if (ST2_MOUSE_POS.x < mousePos.x && mousePos.x < ST2_MOUSE_POS.z &&
		     ST2_MOUSE_POS.y < mousePos.y && mousePos.y < ST2_MOUSE_POS.w)
	{
		Global::SelectStage = STAGE_NUMBER_2;
	}
	//Stage3��
	else if (ST3_MOUSE_POS.x < mousePos.x && mousePos.x < ST3_MOUSE_POS.z &&
		     ST3_MOUSE_POS.y < mousePos.y && mousePos.y < ST3_MOUSE_POS.w)
	{
		Global::SelectStage = STAGE_NUMBER_3;
	}
}

//�`��
void StageSelectScene::Draw()
{
	Image::Draw(LoadHandle_[BackImage_]);
	Image::Draw(LoadHandle_[DescriptionImage_]);

	//STAGE��Փx�̕`��
	for (int i = 0; i < STAGE_LEVEL_MAX; i++)
	{
		Image::Draw(LevelHandle_[i]);
	}

	//�X�e�[�W�̃��b�N����
	StageUnlock();

	Image::SetTransform(LoadHandle_[FrameImage_], FrameTransform);
	Image::Draw(LoadHandle_[FrameImage_]);

	//�R�C���̎擾��
	GetCoin();
}

//�J��
void StageSelectScene::Release()
{
	//STAGE_NUMBER �J��
	for (int i = STAGE_NUMBER_1; i < STAGE_NUMBER_MAX; i++) {
		StageHandle_[i] = INITIAL_ERROR_VALUE;
	}

	//STAGE_LEVEL �J��
	for (int i = STAGE_LEVEL_EASY; i < STAGE_LEVEL_MAX; i++)
	{
		LevelHandle_[i] = INITIAL_ERROR_VALUE;
	}

	//STAGE_LOCK �J��
	for (int i = STAGE_LOCK_2; i < STAGE_LOCK_MAX; i++)
	{
		StageLockHandle_[i] = INITIAL_ERROR_VALUE;
	}

	//SELECT_SOUND �J��
	for (int i = SOUND_SELECT; i < SOUND_MAX; i++)
	{
		SoundHandle_[i] = INITIAL_ERROR_VALUE;
	}

	//Load �J��
	for (int i = FrameImage_; i < LOAD_MAX; i++)
	{
		LoadHandle_[i] = INITIAL_ERROR_VALUE;
	}

}

//�X�e�[�W�̃��b�N�����Ǘ�
void StageSelectScene::StageUnlock()
{
	Image::Draw(StageHandle_[STAGE_NUMBER_1]);

	//�A�����b�N�t���O����ɕ`��̓��e��ς���
	if (Global::stage2.UnLock){
		Image::Draw(StageHandle_[STAGE_NUMBER_2]);
	}
	else{
		Image::Draw(StageLockHandle_[STAGE_LOCK_2]);
	}

	if (Global::stage3.UnLock){
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
		Global::ItemImageSca = ITEMIMAGE_SCALE_SELECT; //�\���T�C�Y

		//Stage1�̃R�C��
		if (Global::stage1.Get_Coin)
		{
			Global::ItemImagePos = ST1_ITEMIMAGE_POS; //�\���ʒu
			Instantiate<ItemImage>(this);            //�\��
		}
		//Stage2�̃R�C��
		if (Global::stage2.Get_Coin)
		{
			Global::ItemImagePos = ST2_ITEMIMAGE_POS;//�\���ʒu
			Instantiate<ItemImage>(this);          //�\��
		}
		//Stage3�̃R�C��
		if (Global::stage3.Get_Coin)
		{
			Global::ItemImagePos = ST3_ITEMIMAGE_POS; //�\���ʒu
			Instantiate<ItemImage>(this);            //�\��
		}

		Drawflg = false;
	}
}

//�摜��4���_���擾
XMFLOAT4 StageSelectScene::ImagePos(int x1, int y1)
{
	//�E���̍��W�����߂�
	float x2 = (float)x1 + 256;  
	float y2 = (float)y1 + 128;

	return XMFLOAT4((float)x1, (float)y1, x2, y2);
}
