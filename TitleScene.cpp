#include "TitleScene.h"

//�R���X�g���N�^
TitleScene::TitleScene(GameObject* parent)
	: GameObject(parent, "TitleScene"),
	BackImageHandle_(-1), TitleImageHandle_(-1),
	SpaceKeyImageHandle_(-1), size_(1), alpha_(255.f),theta_(0)
{
}

//������
void TitleScene::Initialize()
{
	//-----------------------�^�C�g��-----------------------------
	TitleImageHandle_ = Image::Load("Image/Scissors.png");
	assert(TitleImageHandle_ >= 0);
	TitleTrans.position_ = XMFLOAT3(0, 0.3f, 0);
	TitleTrans.scale_ = XMFLOAT3(1.5f, 1.5f, 0);
	Image::SetTransform(TitleImageHandle_, TitleTrans);
	//------------------------------------------------------------

	//-----------------------�w�i--------------------------------
	BackImageHandle_ = Image::Load("Image/Title_Back.png");
	assert(BackImageHandle_ >= 0);
	Image::SetTransform(BackImageHandle_, transform_);
	//------------------------------------------------------------

	//------------------ Space -------------------------
	SpaceKeyImageHandle_ = Image::Load("Image/Space.png");
	assert(SpaceKeyImageHandle_ >= 0);
	SpaceTrans.scale_ = XMFLOAT3(size_, size_, size_);
	SpaceTrans.position_ = XMFLOAT3(0, -0.6f, 0);
	//------------------------------------------------------------

}

//�X�V
void TitleScene::Update()
{
	if (Input::IsKeyDown(DIK_SPACE))
	{
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_SELECT);
	}

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
}

void TitleScene::Blinking()
{
	alpha_ = (float)abs(cos(XMConvertToRadians((float)theta_)));
	alpha_ *= 255.f;

	theta_ += 2;
	if (theta_ == 360) { theta_ = 0; }

}
