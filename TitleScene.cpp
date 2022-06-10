#include "TitleScene.h"

//�R���X�g���N�^
TitleScene::TitleScene(GameObject* parent)
	: GameObject(parent, "TitleScene"),
	BackImageHandle_(-1), TitleImageHandle_(-1),
	SpaceKeyImageHandle_(-1), SoundHandle_(-1),
	size_(1), alpha_(255.f), theta_(0), TimerCnt(0), Timer_(false)
{
}

//������
void TitleScene::Initialize()
{
	//-----------------------�^�C�g��-----------------------------
	TitleImageHandle_ = Image::Load("Image/TitleScene/Scissors.png");
	assert(TitleImageHandle_ >= 0);
	TitleTrans.position_ = XMFLOAT3(0, 0.3f, 0);
	TitleTrans.scale_ = XMFLOAT3(3.f, 3.f, 0);
	Image::SetTransform(TitleImageHandle_, TitleTrans);
	//------------------------------------------------------------

	//-----------------------�w�i--------------------------------
	BackImageHandle_ = Image::Load("Image/TitleScene/Title_Back.png");
	assert(BackImageHandle_ >= 0);
	Image::SetTransform(BackImageHandle_, transform_);
	//------------------------------------------------------------

	//------------------ Space -------------------------
	SpaceKeyImageHandle_ = Image::Load("Image/TitleScene/Space.png");
	assert(SpaceKeyImageHandle_ >= 0);
	SpaceTrans.scale_ = XMFLOAT3(size_, size_, size_);
	SpaceTrans.position_ = XMFLOAT3(0, -0.6f, 0);
	//------------------------------------------------------------


	//--------- Sound ----------------
	SoundHandle_ = Audio::Load("Sound/Cut.wav");
	assert(SoundHandle_ >= 0);
	//-------------------------------
}

//�X�V
void TitleScene::Update()
{


	if (Input::IsKeyDown(DIK_SPACE) || Input::IsMouseButtonDown(0))
	{
		Audio::Play(SoundHandle_);

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
	Image::Draw(BackImageHandle_);

	//�^�C�g���̕`��
	Image::Draw(TitleImageHandle_);

	//Space
	Image::SetAlpha(SpaceKeyImageHandle_, (int)alpha_);
	Image::SetTransform(SpaceKeyImageHandle_, SpaceTrans);
	Image::Draw(SpaceKeyImageHandle_);

}

//�J��
void TitleScene::Release()
{
	BackImageHandle_ = -1;
	TitleImageHandle_ = -1;
	SpaceKeyImageHandle_ = -1;
	SoundHandle_ = -1;
}

void TitleScene::Blinking()
{
	alpha_ = (float)abs(cos(XMConvertToRadians((float)theta_)));
	alpha_ *= 255.f;

	theta_ += 2;
	if (theta_ == 360) { theta_ = 0; }

}

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
	if (TimerCnt >= 80)
	{
		Timer_ = false;

		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_SELECT);
	}
}
