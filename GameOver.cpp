#include "GameOver.h"
#include "Global.h"

//コンストラクタ
GameOver::GameOver(GameObject* parent)
    :GameObject(parent, "GameOver"), 
    alpha_(0),select_(0), Balpha_(0),
    GameOverBackImage_(-1), BackMenuImage_(-1),
    BackMenuUpImage_(-1), RetryImage_(-1),
    RetryUpImage_(-1)
{
    Retry.position_ = XMFLOAT3(0, 0.2f, 0);
    BackMenu.position_ = XMFLOAT3(0, -0.2f, 0);
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
    GameOverBackImage_ = Image::Load("Image/GameOverBack.png");
    assert(GameOverBackImage_ >= 0);
    //リトライ
    RetryImage_ = Image::Load("Image/GameOverBack.png");
    assert(RetryImage_ >= 0);
    //リトライ(選択)
    RetryUpImage_ = Image::Load("Image/GameOverBack.png");
    assert(RetryUpImage_ >= 0);
    //戻る
    BackMenuImage_ = Image::Load("Image/GameOverBack.png");
    assert(BackMenuImage_ >= 0);
    //戻る(選択)
    BackMenuUpImage_ = Image::Load("Image/GameOverBack.png");
    assert(BackMenuUpImage_ >= 0);
}

//更新
void GameOver::Update()
{
    //不透明度
    if (Balpha_ == 10) {
        Balpha_ = 10;
    }
    else if (alpha_ >= 255) {
        alpha_ = 255;
    }
    else
    {
        Balpha_ += 2;
        alpha_ += 25;
    }

    //選択
    Select();
}

//描画
void GameOver::Draw()
{
    Image::SetAlpha(GameOverBackImage_, Balpha_);
    Image::SetAlpha(RetryImage_, alpha_);
    Image::SetAlpha(RetryUpImage_, alpha_);
    Image::SetAlpha(BackMenuImage_, alpha_);
    Image::SetAlpha(BackMenuUpImage_, alpha_);

    Image::SetTransform(GameOverBackImage_, transform_);
    Image::Draw(GameOverBackImage_);

    //リトライが選択されいるとき
    if (select_ == 0)
    {
        Image::SetTransform(RetryUpImage_, BackMenu);
        Image::Draw(RetryUpImage_);

        Image::SetTransform(BackMenuImage_, Retry);
        Image::Draw(BackMenuImage_);

    }
    //メニューシーンに戻るが選択されいるとき
    if (select_ == 1)
    {
        Image::SetTransform(RetryImage_, Retry);
        Image::Draw(RetryImage_);

        Image::SetTransform(BackMenuUpImage_, BackMenu);
        Image::Draw(BackMenuUpImage_);
    }

}

//開放
void GameOver::Release()
{
    GameOverBackImage_ = -1;
    BackMenuImage_     = -1;
    BackMenuUpImage_   = -1;
    RetryImage_        = -1;
    RetryUpImage_      = -1;
}

//選択
void GameOver::Select()
{
    //選択
    if (Input::IsKeyDown(DIK_UP))
    {
        select_--;
        if (select_ < 0)
        {
            select_ = 0;
        }
    }
    if (Input::IsKeyDown(DIK_DOWN))
    {
        select_++;
        if (select_ > 1)
        {
            select_ = 1;
        }
    }

    Scissors* pScissors = (Scissors*)FindObject("Scissors");

    if (Input::IsKeyDown(DIK_SPACE))
    {
        if (select_ == 0)
        {
            KillMe();
            Global::GameOver = false;
            pScissors->Restart();
        }
        else if (select_ == 1)
        {
            Global::GameOver = false;

            //ステージセレクトシーンに移動
            SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
            pSceneManager->ChangeScene(SCENE_ID_SELECT);
        }
    }
}
