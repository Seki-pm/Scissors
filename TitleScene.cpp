#include "TitleScene.h"

//コンストラクタ
TitleScene::TitleScene(GameObject* parent)
	: GameObject(parent, "TitleScene"),
	BackImageHandle_(-1), TitleImageHandle_(-1),
	SpaceKeyImageHandle_(-1), size_(1), alpha_(255.f),theta_(0)
{
}

//初期化
void TitleScene::Initialize()
{
	//-----------------------タイトル-----------------------------
	TitleImageHandle_ = Image::Load("Image/Scissors.png");
	assert(TitleImageHandle_ >= 0);
	TitleTrans.position_ = XMFLOAT3(0, 0.3f, 0);
	TitleTrans.scale_ = XMFLOAT3(1.5f, 1.5f, 0);
	Image::SetTransform(TitleImageHandle_, TitleTrans);
	//------------------------------------------------------------

	//-----------------------背景--------------------------------
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

//更新
void TitleScene::Update()
{
	if (Input::IsKeyDown(DIK_SPACE))
	{
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_SELECT);
	}

	//点滅
	Blinking();
}

//描画
void TitleScene::Draw()
{
	//背景の描画
	Image::Draw(BackImageHandle_);

	//タイトルの描画
	Image::Draw(TitleImageHandle_);

	//Space
	Image::SetAlpha(SpaceKeyImageHandle_, (int)alpha_);
	Image::SetTransform(SpaceKeyImageHandle_, SpaceTrans);
	Image::Draw(SpaceKeyImageHandle_);

}

//開放
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
