#include "TitleScene.h"

//コンストラクタ
TitleScene::TitleScene(GameObject* parent)
	: GameObject(parent, "TitleScene"),
	  alpha_(255.f), theta_(0), TimerCnt(0), Timer_(false)
{
	//Load 初期化
	for (int i = LOAD_MIN + 1; i < LOAD_MAX; i++)
	{
		LoadHandle_[i] = INITIAL_ERROR_VALUE;
	}
}

//初期化
void TitleScene::Initialize()
{
	//-----------------------タイトル-----------------------------
	LoadHandle_[TitleImage_] = Image::Load("Image/TitleScene/Scissors.png");
	assert(LoadHandle_[TitleImage_] >= 0);
	TitleTrans.position_ = TITLE_POS;
	TitleTrans.scale_ = TITLE_SCA;
	Image::SetTransform(LoadHandle_[TitleImage_], TitleTrans);
	//------------------------------------------------------------

	//----------------------- 背景 -------------------------------
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

//更新
void TitleScene::Update()
{

	//SPACE or マウスクリックで動き出す
	if (Input::IsKeyDown(DIK_SPACE) || Input::IsMouseButtonDown(0))
	{
		Audio::Play(LoadHandle_[ScissorsSound_]);

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
	Image::Draw(LoadHandle_[BackImage_]);

	//タイトルの描画
	Image::Draw(LoadHandle_[TitleImage_]);

	//Space
	Image::SetAlpha(LoadHandle_[SpaceKeyImage_], (int)alpha_);
	Image::SetTransform(LoadHandle_[SpaceKeyImage_], SpaceTrans);
	Image::Draw(LoadHandle_[SpaceKeyImage_]);

}

//開放
void TitleScene::Release()
{
	//Load 開放
	for (int i = LOAD_MIN; i < LOAD_MAX; i++)
	{
		LoadHandle_[i] = INITIAL_ERROR_VALUE;
	}
}

//点滅
void TitleScene::Blinking()
{
	//alpha_を増やして点滅させる
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
	if (TimerCnt >= TIMER_COUNT)
	{
		Timer_ = false;

		//StageSelectSceneに遷移
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_SELECT);
	}
}
