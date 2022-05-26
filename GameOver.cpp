#include "GameOver.h"

//コンストラクタ
GameOver::GameOver(GameObject* parent)
    :GameObject(parent, "GameOver"),
    GameOverBackImage_(-1), BackMenuImage_(-1),
    RetryImage_(-1),SelectFrameImage_(-1),
    alpha_(150), select_(0)
{
    Retry.position_ = XMFLOAT3(-0.3f, 0, 0);
    BackMenu.position_ = XMFLOAT3(0.3f, 0, 0);
}

//デストラクタ
GameOver::~GameOver()
{
}

//初期化
void GameOver::Initialize()
{
    //取得したコインを無くす
    switch (Global::SelectStage)
    {
    case STAGE_NUMBER_1:
        Global::GetCoin_1 = false;
        break;
    case STAGE_NUMBER_2:
        Global::GetCoin_2 = false;
        break;
    }

    //画像データのロード
    //ゲームオーバー
    GameOverBackImage_ = Image::Load("Image/BlackBack.png");
    assert(GameOverBackImage_ >= 0);

    //リトライ
    RetryImage_ = Image::Load("Image/Retry.png");
    assert(RetryImage_ >= 0);

    //セレクトフレーム
    SelectFrameImage_ = Image::Load("Image/SelectFrame.png");
    assert(SelectFrameImage_ >= 0);

    //ステージ選択に戻る
    BackMenuImage_ = Image::Load("Image/BackButton.png");
    assert(BackMenuImage_ >= 0);

}

//更新
void GameOver::Update()
{
}

//描画
void GameOver::Draw()
{
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

//ゲット
int GameOver::GetSelect()
{
    return select_;
}
