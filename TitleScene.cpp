#include "TitleScene.h"

//�R���X�g���N�^
TitleScene::TitleScene(GameObject* parent)
	: GameObject(parent, "TitleScene"),
	BackImage_(-1), TitleImage_(-1),SpaceKeyImage_(-1), ScissorsSound_(-1),
	alpha_(255.f), theta_(0), TimerCnt(0), Timer_(false)
{
}

//������
void TitleScene::Initialize()
{
	//-----------------------�^�C�g��-----------------------------
	TitleImage_ = Image::Load("Image/TitleScene/Scissors.png");
	assert(TitleImage_ >= 0);
	TitleTrans.position_ = TITLE_POS;
	TitleTrans.scale_ = TITLE_SCA;
	Image::SetTransform(TitleImage_, TitleTrans);
	//------------------------------------------------------------

	//-----------------------�w�i--------------------------------
	BackImage_ = Image::Load("Image/TitleScene/Title_Back.png");
	assert(BackImage_ >= 0);
	Image::SetTransform(BackImage_, transform_);
	//------------------------------------------------------------

	//------------------ Space -------------------------
	SpaceKeyImage_ = Image::Load("Image/TitleScene/Space.png");
	assert(SpaceKeyImage_ >= 0);
	SpaceTrans.position_ = SPACE_POS;
	//------------------------------------------------------------


	//--------- Sound ----------------
	ScissorsSound_ = Audio::Load("Sound/Title&Menu/Cut.wav");
	assert(ScissorsSound_ >= 0);
	//-------------------------------
}

//�X�V
void TitleScene::Update()
{

	//SPACE or �}�E�X�N���b�N�œ����o��
	if (Input::IsKeyDown(DIK_SPACE) || Input::IsMouseButtonDown(0))
	{
		Audio::Play(ScissorsSound_);

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
	Image::Draw(BackImage_);

	//�^�C�g���̕`��
	Image::Draw(TitleImage_);

	//Space
	Image::SetAlpha(SpaceKeyImage_, (int)alpha_);
	Image::SetTransform(SpaceKeyImage_, SpaceTrans);
	Image::Draw(SpaceKeyImage_);

}

//�J��
void TitleScene::Release()
{
	BackImage_ = -1;
	TitleImage_ = -1;
	SpaceKeyImage_ = -1;
	ScissorsSound_ = -1;
}

//�_��
void TitleScene::Blinking()
{
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
