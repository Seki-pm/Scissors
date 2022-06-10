#include "GoalStaging.h"


//コンストラクタ
GoalStaging::GoalStaging(GameObject* parent)
    :GameObject(parent, "GoalStaging"), 
    BalloonModel_(-1), BackImage_(-1), EnterImage_(-1),
    CircleImage_(-1), SoundHandle_(-1), size_(10), timer(0),
    StagingFlg(false), StringFlg(false)
{
}

//デストラクタ
GoalStaging::~GoalStaging()
{
}

//初期化
void GoalStaging::Initialize()
{
    Global gl;

    //モデルデータのロード
    BalloonModel_ = Model::Load("Model/InGameObject/Balloon.fbx");
    assert(BalloonModel_ >= 0);
    BalloonTrans.position_ = XMFLOAT3(gl.GetCameraGoalX(), gl.GetCameraGoalY(), 0.f);
    BalloonTrans.scale_ = XMFLOAT3(0.8f, 0.8f, 0.8f);
    Model::SetTransform(BalloonModel_, BalloonTrans);

    //Enter
    EnterImage_ = Image::Load("Image/InGameMenu/Enter.png");
    assert(EnterImage_ >= 0);
    EnterTrans.position_ = XMFLOAT3(0.1f, 0.1f, 0);
    EnterTrans.scale_ = XMFLOAT3(0.8f, 0.8f, 0.8f);
    Image::SetTransform(EnterImage_, EnterTrans);

    //暗転
    BackImage_ = Image::Load("Image/InGameMenu/Clear_Black.png");
    assert(BackImage_ >= 0);
    auto BlackTrans = Transform();
    BlackTrans.scale_ = XMFLOAT3(1.4f, 1.4f, 1.4f);
    Image::SetTransform(BackImage_, BlackTrans);

    //収縮用
    CircleImage_ = Image::Load("Image/InGameMenu/Clear_Effect.png");
    assert(CircleImage_ >= 0);
    CircleTrans.scale_ = XMFLOAT3(size_,size_,size_);

    //サウンド
    SoundHandle_ = Audio::Load("Sound/InStage/Staging.wav");
    assert(SoundHandle_ >= 0);
}

//更新
void GoalStaging::Update()
{
    //風船のアニメーション開始
    //if (Input::IsKeyDown(DIK_I))
    //{
    //    Model::SetAnimFrame(BalloonModel_, 1, 300, 1.0f);
    //}

    //ゴールについたら文字表示
    if (gl.GetTransPos_X() >= gl.GetCameraGoalX() - 1.5f)
    {
        //文字表示
        StringFlg = true;
    }
    else
    {
        StringFlg = false;
    }

    //Enterが押されたらタイマー開始
    if (StagingFlg) Timer();
}

//描画
void GoalStaging::Draw()
{
    Model::Draw(BalloonModel_);

    //ゴール演出
    if(StringFlg)
    {
        //文字表示
        Image::Draw(EnterImage_);

        //Enterキーを押したら
        if (Input::IsKeyDown(DIK_RETURN))
        {
            Audio::Play(SoundHandle_);

            StringFlg = false;
            //ゴール演出スタート
            StagingFlg = true;
        }
    }

    //暗転処理
    if (StagingFlg)
    {
        CircleTrans.scale_ = XMFLOAT3(size_, size_, size_);
        Image::SetTransform(CircleImage_, CircleTrans);

        if (size_ > 1.4f)
        {
            size_ -= 0.15f;
            Image::Draw(CircleImage_);
        }
        else
        {
            Image::Draw(BackImage_);
        }
    }

}

//開放
void GoalStaging::Release()
{
    EnterImage_ = -1;
    BalloonModel_ = -1;
    SoundHandle_ = -1;
    BackImage_ = -1;
    CircleImage_ = -1;
}

//時間管理
void GoalStaging::Timer()
{
    timer++;

    if (timer >= 90)
    {
        Global::Timer = true;
        timer = 0;
    }
}
