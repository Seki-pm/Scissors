#include "GameOver.h"

//コンストラクタ
GameOver::GameOver(GameObject* parent)
    :GameObject(parent, "GameOver"),
     alpha_(150), select_(0)
{
    //Load 初期化
    for (int i = LOAD_MIN + 1; i < LOAD_MAX; i++)
    {
        LoadHandle_[i] = INITIAL_ERROR_VALUE;
    }

}

//デストラクタ
GameOver::~GameOver()
{
}

//初期化
void GameOver::Initialize()
{
    //表示位置設定
    Retry.position_ = RETRY_POS;
    BackMenu.position_ = BACKMENU_POS;

    //--------------------  画像データのロード  ---------------------
    {
        //ゲームオーバー
        LoadHandle_[GameOverBackImage_] = Image::Load("Image/InGameMenu/BlackBack.png");
        assert(LoadHandle_[GameOverBackImage_] >= 0);

        //リトライ
        LoadHandle_[RetryImage_] = Image::Load("Image/InGameMenu/Retry.png");
        assert(LoadHandle_[RetryImage_] >= 0);

        //セレクトフレーム
        LoadHandle_[SelectFrameImage_] = Image::Load("Image/InGameMenu/SelectFrame.png");
        assert(LoadHandle_[SelectFrameImage_] >= 0);

        //ステージ選択に戻る
        LoadHandle_[BackMenuImage_] = Image::Load("Image/InGameMenu/BackButton.png");
        assert(LoadHandle_[BackMenuImage_] >= 0);
    }
    //---------------------------------------------------------------
}

//更新
void GameOver::Update()
{
}

//描画
void GameOver::Draw()
{
    pScissors_ = (Scissors*)FindObject("Scissors");

    //背景描画
    Image::SetAlpha(LoadHandle_[GameOverBackImage_], alpha_);
    Image::SetTransform(LoadHandle_[GameOverBackImage_], transform_);
    Image::Draw(LoadHandle_[GameOverBackImage_]);

    Image::SetTransform(LoadHandle_[RetryImage_], Retry);
    Image::Draw(LoadHandle_[RetryImage_]);

    Image::SetTransform(LoadHandle_[BackMenuImage_], BackMenu);
    Image::Draw(LoadHandle_[BackMenuImage_]);


    //リトライが選択されている時
    if (select_ == 0)
    {
        Image::SetTransform(LoadHandle_[SelectFrameImage_], Retry);
    }
    //ステージ選択が選択されている時
    else if(select_ == 1)
    {
        Image::SetTransform(LoadHandle_[SelectFrameImage_], BackMenu);
    }

    Image::Draw(LoadHandle_[SelectFrameImage_]);
}

//開放
void GameOver::Release()
{
    //Load 開放
    for (int i = LOAD_MIN + 1; i < LOAD_MAX; i++)
    {
        LoadHandle_[i] = INITIAL_ERROR_VALUE;
    }
}

//セット
void GameOver::SetSelect(int select)
{
    select_ = select;
}

