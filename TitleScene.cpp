#include "TitleScene.h"

//コンストラクタ
TitleScene::TitleScene(GameObject* parent)
	: GameObject(parent, "TitleScene"),
	BackImage_(-1), TitleImage_(-1),SpaceKeyImage_(-1), ScissorsSound_(-1),
	size_(1), alpha_(255.f), theta_(0), TimerCnt(0), Timer_(false)
{
}

//初期化
void TitleScene::Initialize()
{
	//-----------------------タイトル-----------------------------
	TitleImage_ = Image::Load("Image/TitleScene/Scissors.png");
	assert(TitleImage_ >= 0);
	TitleTrans.position_ = XMFLOAT3(0, 0.3f, 0);
	TitleTrans.scale_ = XMFLOAT3(3.f, 3.f, 0);
	Image::SetTransform(TitleImage_, TitleTrans);
	//------------------------------------------------------------

	//-----------------------背景--------------------------------
	BackImage_ = Image::Load("Image/TitleScene/Title_Back.png");
	assert(BackImage_ >= 0);
	Image::SetTransform(BackImage_, transform_);
	//------------------------------------------------------------

	//------------------ Space -------------------------
	SpaceKeyImage_ = Image::Load("Image/TitleScene/Space.png");
	assert(SpaceKeyImage_ >= 0);
	SpaceTrans.scale_ = XMFLOAT3(size_, size_, size_);
	SpaceTrans.position_ = XMFLOAT3(0, -0.6f, 0);
	//------------------------------------------------------------


	//--------- Sound ----------------
	ScissorsSound_ = Audio::Load("Sound/Title&Menu/Cut.wav");
	assert(ScissorsSound_ >= 0);
	//-------------------------------
}

//更新
void TitleScene::Update()
{

	//SPACE or マウスクリックで動き出す
	if (Input::IsKeyDown(DIK_SPACE) || Input::IsMouseButtonDown(0))
	{
		Audio::Play(ScissorsSound_);

		Timer_ = true;
	}

	//タイマー
	Timer();

	//点滅
	Blinking();
}

//描画
void TitleScene::Draw()
{
	//背景の描画
	Image::Draw(BackImage_);

	//タイトルの描画
	Image::Draw(TitleImage_);

	//Space
	Image::SetAlpha(SpaceKeyImage_, (int)alpha_);
	Image::SetTransform(SpaceKeyImage_, SpaceTrans);
	Image::Draw(SpaceKeyImage_);

}

//開放
void TitleScene::Release()
{
	BackImage_ = -1;
	TitleImage_ = -1;
	SpaceKeyImage_ = -1;
	ScissorsSound_ = -1;
}

//点滅
void TitleScene::Blinking()
{
	alpha_ = (float)abs(cos(XMConvertToRadians((float)theta_)));
	alpha_ *= 255.f;

	theta_ += 2;
	if (theta_ == 360) { theta_ = 0; }

}

//時間計測
void TitleScene::Timer()
{
	//Timerフラグがtrueなら
	if (Timer_) {
		TimerCnt++;
	}
	else {
		TimerCnt = 0;
	}

	//約1.3秒後...
	if (TimerCnt >= 80)
	{
		Timer_ = false;

		//StageSelectSceneに遷移
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_SELECT);
	}
}
