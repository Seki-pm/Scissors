#include "Pause.h"
#include "Engine/SceneManager.h"
#include "Engine/Image.h"
#include "Engine/Input.h"
#include "Global.h"

//コンストラクタ
Pause::Pause(GameObject* parent)
    :GameObject(parent, "Pause"),
    PauseBackImage_(-1), ContinueImage_(-1),
    BackMenuImage_(-1), SelectFrameImage_(-1),
    select_(0), alpha_(150)
{
    Continue.position_ = XMFLOAT3(-0.3f, 0, 0);
    BackMenu.position_ = XMFLOAT3(0.3f, 0, 0);
}

//デストラクタ
Pause::~Pause()
{
}

//初期化
void Pause::Initialize()
{
    //画像データのロード
    //不透明背景
    PauseBackImage_ = Image::Load("Image/InGameMenu/BlackBack.png");
    assert(PauseBackImage_ >= 0);

    //続ける
    ContinueImage_ = Image::Load("Image/InGameMenu/Continue.png");
    assert(ContinueImage_ >= 0);

    //ステージ選択に戻る
    BackMenuImage_ = Image::Load("Image/InGameMenu/BackButton.png");
    assert(BackMenuImage_ >= 0);

    //セレクトフレーム
    SelectFrameImage_ = Image::Load("Image/InGameMenu/SelectFrame.png");
    assert(SelectFrameImage_ >= 0);

}

//更新
void Pause::Update()
{

    //プレイシーンに戻るが選択されているとき
    if (Global::Pause && select_ == 0)
    {
        if (Input::IsKeyDown(DIK_SPACE))
        {
            KillMe();
            Global::Pause = false;
        }
    }
}

//描画
void Pause::Draw()
{

    //背景
    Image::SetAlpha(PauseBackImage_, alpha_);
    Image::SetTransform(PauseBackImage_, transform_);
    Image::Draw(PauseBackImage_);

    Image::SetTransform(ContinueImage_, Continue);
    Image::Draw(ContinueImage_);

    Image::SetTransform(BackMenuImage_, BackMenu);
    Image::Draw(BackMenuImage_);





    //プレイシーンに戻るが選択されいるとき
    if (select_ == 0)
    {
        Image::SetTransform(SelectFrameImage_, Continue);

        if (Input::IsKeyDown(DIK_SPACE))
        {
            KillMe();
        }
    }
    //メニューシーンに戻るが選択されているとき
    else if (select_ == 1)
    {
        Image::SetTransform(SelectFrameImage_, BackMenu);
    }

    Image::Draw(SelectFrameImage_);
}

//開放
void Pause::Release()
{
    PauseBackImage_ = -1;
    ContinueImage_ = -1;
    BackMenuImage_ = -1;

}
