#include "GameOver.h"
#include "Global.h"

//コンストラクタ
GameOver::GameOver(GameObject* parent)
    :GameObject(parent, "GameOver"), 
    alpha_(0),select_(0), Balpha_(0),
    GameOverBackImage_(-1), BackMenuImage_(-1),
    RetryImage_(-1), size_(0.8), siz_(0.4f)
{
    Retry.position_ = XMFLOAT3(0, 0.3f, 0);
    BackMenu.position_ = XMFLOAT3(0, -0.3f, 0);
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
    RetryImage_ = Image::Load("Image/Retry.png");
    assert(RetryImage_ >= 0);

    //戻る
    BackMenuImage_ = Image::Load("Image/BackButton.png");
    assert(BackMenuImage_ >= 0);

}

//更新
void GameOver::Update()
{
    Retry.scale_ = XMFLOAT3(size_,size_, size_);
    BackMenu.scale_ = XMFLOAT3(siz_,siz_, siz_);


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
    Image::SetTransform(GameOverBackImage_, transform_);
    Image::Draw(GameOverBackImage_);



    Image::SetTransform(RetryImage_, Retry);
    Image::SetTransform(BackMenuImage_, BackMenu);

    Image::Draw(RetryImage_);
    Image::Draw(BackMenuImage_);
}

//開放
void GameOver::Release()
{
    GameOverBackImage_ = -1;
    BackMenuImage_     = -1;
    RetryImage_        = -1;
}

//選択
void GameOver::Select()
{
    //選択
    if (Input::IsKeyDown(DIK_UP))
    {
        select_ = 0;
        size_ = 0.8f;
        siz_ = 0.4f;
    }
    if (Input::IsKeyDown(DIK_DOWN))
    {
        select_ = 1;
        siz_ = 0.4f;
        size_ = 0.8f;
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
