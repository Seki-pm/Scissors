#include "Pause.h"

//コンストラクタ
Pause::Pause(GameObject* parent)
    :GameObject(parent, "Pause"),
     select_(0), alpha_(150)
{
    //Load 初期化
    for (int i = LOAD_MIN + 1; i < LOAD_MAX; i++)
    {
        LoadHandle_[i] = INITIAL_ERROR_VALUE;
    }
}

//デストラクタ
Pause::~Pause()
{
}

//初期化
void Pause::Initialize()
{
    //表示位置の設定
    Continue.position_ = CONTINUE_POS;
    BackMenu.position_ = BACKMENU_POS;

    //-------------------- 画像データのロード --------------------------
    {
        //不透明背景
        LoadHandle_[PauseBackImage_] = Image::Load("Image/InGameMenu/BlackBack.png");
        assert(LoadHandle_[PauseBackImage_] >= 0);

        //続ける
        LoadHandle_[ContinueImage_] = Image::Load("Image/InGameMenu/Continue.png");
        assert(LoadHandle_[ContinueImage_] >= 0);

        //ステージ選択に戻る
        LoadHandle_[BackMenuImage_] = Image::Load("Image/InGameMenu/BackButton.png");
        assert(LoadHandle_[BackMenuImage_] >= 0);

        //セレクトフレーム
        LoadHandle_[SelectFrameImage_] = Image::Load("Image/InGameMenu/SelectFrame.png");
        assert(LoadHandle_[SelectFrameImage_] >= 0);
    }
    //------------------------------------------------------------------
}

//更新
void Pause::Update()
{
}

//描画
void Pause::Draw()
{

    //背景
    Image::SetAlpha(LoadHandle_[PauseBackImage_], alpha_);
    Image::SetTransform(LoadHandle_[PauseBackImage_], transform_);
    Image::Draw(LoadHandle_[PauseBackImage_]);

    Image::SetTransform(LoadHandle_[ContinueImage_], Continue);
    Image::Draw(LoadHandle_[ContinueImage_]);

    Image::SetTransform(LoadHandle_[BackMenuImage_], BackMenu);
    Image::Draw(LoadHandle_[BackMenuImage_]);




    //プレイシーンに戻るが選択されいるとき
    if (select_ == 0)
    {
        Image::SetTransform(LoadHandle_[SelectFrameImage_], Continue);

        if (Input::IsKeyDown(DIK_SPACE))
        {
            KillMe();
        }
    }
    //メニューシーンに戻るが選択されているとき
    else if (select_ == 1)
    {
        Image::SetTransform(LoadHandle_[SelectFrameImage_], BackMenu);
    }

    Image::Draw(LoadHandle_[SelectFrameImage_]);
}

//開放
void Pause::Release()
{
    //Load 開放
    for (int i = LOAD_MIN + 1; i < LOAD_MAX; i++)
    {
        LoadHandle_[i] = INITIAL_ERROR_VALUE;
    }
}
