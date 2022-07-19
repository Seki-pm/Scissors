#include "TitleScene.h"

//�R���X�g���N�^
TitleScene::TitleScene(GameObject* parent)
	: GameObject(parent, "TitleScene"),
	  alpha_(255.f), theta_(0), TimerCnt(0), Timer_(false)
{
	//Load ������
	for (int i = LOAD_MIN + 1; i < LOAD_MAX; i++)
	{
		LoadHandle_[i] = INITIAL_ERROR_VALUE;
	}
}

//������
void TitleScene::Initialize()
{
	//-----------------------�^�C�g��-----------------------------
	LoadHandle_[TitleImage_] = Image::Load("Image/TitleScene/Scissors.png");
	assert(LoadHandle_[TitleImage_] >= 0);
	TitleTrans.position_ = TITLE_POS;
	TitleTrans.scale_ = TITLE_SCA;
	Image::SetTransform(LoadHandle_[TitleImage_], TitleTrans);
	//------------------------------------------------------------

	//----------------------- �w�i -------------------------------
	LoadHandle_[BackImage_] = Image::Load("Image/TitleScene/Title_Back.png");
	assert(LoadHandle_[BackImage_] >= 0);
	Image::SetTransform(LoadHandle_[BackImage_], transform_);
	//------------------------------------------------------------

	//---------------------- Space -------------------------------
	LoadHandle_[SpaceKeyImage_] = Image::Load("Image/TitleScene/Space.png");
	assert(LoadHandle_[SpaceKeyImage_] >= 0);
	SpaceTrans.position_ = SPACE_POS;
	//------------------------------------------------------------


	//---------------------- Sound -------------------------------
	LoadHandle_[ScissorsSound_] = Audio::Load("Sound/Title&Menu/Cut.wav");
	assert(LoadHandle_[ScissorsSound_] >= 0);
	//------------------------------------------------------------
}

//�X�V
void TitleScene::Update()
{

	//SPACE or �}�E�X�N���b�N�œ����o��
	if (Input::IsKeyDown(DIK_SPACE) || Input::IsMouseButtonDown(0))
	{
		Audio::Play(LoadHandle_[ScissorsSound_]);

		Timer_ = true;
	}

	//�^�C�}�[
	Timer();

	//�_��
	Blinking();
}

//�`��
void TitleScene::Draw()
{
	//�w�i�̕`��
	Image::Draw(LoadHandle_[BackImage_]);

	//�^�C�g���̕`��
	Image::Draw(LoadHandle_[TitleImage_]);

	//Space
	Image::SetAlpha(LoadHandle_[SpaceKeyImage_], (int)alpha_);
	Image::SetTransform(LoadHandle_[SpaceKeyImage_], SpaceTrans);
	Image::Draw(LoadHandle_[SpaceKeyImage_]);

}

//�J��
void TitleScene::Release()
{
	//Load �J��
	for (int i = LOAD_MIN; i < LOAD_MAX; i++)
	{
		LoadHandle_[i] = INITIAL_ERROR_VALUE;
	}
}

//�_��
void TitleScene::Blinking()
{
	//alpha_�𑝂₵�ē_�ł�����
	alpha_ = (float)abs(cos(XMConvertToRadians((float)theta_)));
	alpha_ *= 255.f;

	theta_ += 2;
	if (theta_ == 360) { theta_ = 0; }

}

//���Ԍv��
void TitleScene::Timer()
{
	//Timer�t���O��true�Ȃ�
	if (Timer_) {
		TimerCnt++;
	}
	else {
		TimerCnt = 0;
	}

	//��1.3�b��...
	if (TimerCnt >= TIMER_COUNT)
	{
		Timer_ = false;

		//StageSelectScene�ɑJ��
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_SELECT);
	}
}
