#include "GameOver.h"

//コンストラクタ
GameOver::GameOver(GameObject* parent)
    :GameObject(parent, "GameOver"),
    GameOverBackImage_(-1), BackMenuImage_(-1),
    RetryImage_(-1),SelectFrameImage_(-1),
    alpha_(150), select_(0),
    RETRY_POS(XMFLOAT3(-0.3f, 0, 0)), BACKMENU_POS(XMFLOAT3(0.3f, 0, 0))
{
    Retry.position_ = RETRY_POS;
    BackMenu.position_ = BACKMENU_POS;
}

//デストラクタ
GameOver::~GameOver()
{
}

//初期化
void GameOver::Initialize()
{
    //画像データのロード
    //ゲームオーバー
    GameOverBackImage_ = Image::Load("Image/InGameMenu/BlackBack.png");
    assert(GameOverBackImage_ >= 0);

    //リトライ
    RetryImage_ = Image::Load("Image/InGameMenu/Retry.png");
    assert(RetryImage_ >= 0);

    //セレクトフレーム
    SelectFrameImage_ = Image::Load("Image/InGameMenu/SelectFrame.png");
    assert(SelectFrameImage_ >= 0);

    //ステージ選択に戻る
    BackMenuImage_ = Image::Load("Image/InGameMenu/BackButton.png");
    assert(BackMenuImage_ >= 0);

}

//更新
void GameOver::Update()
{
}

//描画
void GameOver::Draw()
{
    Scissors* pScissors_ = (Scissors*)FindObject("Scissors");

    //背景描画
    Image::SetAlpha(GameOverBackImage_, alpha_);
    Image::SetTransform(GameOverBackImage_, transform_);
    Image::Draw(GameOverBackImage_);

    Image::SetTransform(RetryImage_, Retry);
    Image::Draw(RetryImage_);

    Image::SetTransform(BackMenuImage_, BackMenu);
    Image::Draw(BackMenuImage_);


    //リトライが選択されている時
    if (select_ == 0)
    {
        Image::SetTransform(SelectFrameImage_, Retry);
        
        if (Input::IsKeyDown(DIK_SPACE))
        {
            KillMe();
            pScissors_->Restart();
        }
    }
    //ステージ選択が選択されている時
    else if(select_ == 1)
    {
        Image::SetTransform(SelectFrameImage_, BackMenu);
    }

    Image::Draw(SelectFrameImage_);
}

//開放
void GameOver::Release()
{
    GameOverBackImage_ = -1;
    BackMenuImage_     = -1;
    RetryImage_        = -1;
    SelectFrameImage_  = -1;
}

//セット
void GameOver::SetSelect(int select)
{
    select_ = select;
}

