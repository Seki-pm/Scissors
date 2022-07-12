#include "GoalStaging.h"

#define Bal_Ent_Size XMFLOAT3(0.8f,0.8f,0.8f);
#define Enter_Pos XMFLOAT3(0.1f,0.1f,0.f);
#define BackImage_Size XMFLOAT3(1.4f,1.4f,1.4f);

const int TIME = 90;
const float Size_Min = 1.4f;
const float Scale_Down_Val = 0.15f;

//コンストラクタ
GoalStaging::GoalStaging(GameObject* parent)
    :GameObject(parent, "GoalStaging"), 
    BalloonModel_(-1), BackImage_(-1), EnterImage_(-1),
    CircleImage_(-1),  GoalSound_(-1), time_(0),size_(10),
    timer_(false),StagingFlg(false), StringFlg(false)
{
}

//デストラクタ
GoalStaging::~GoalStaging()
{
}

//初期化
void GoalStaging::Initialize()
{

    //モデルデータのロード
    BalloonModel_ = Model::Load("Model/InGameObject/Balloon.fbx");
    assert(BalloonModel_ >= 0);
    BalloonTrans.position_ = XMFLOAT3(gl.GetCameraGoal().x, gl.GetCameraGoal().y, 0.f);
    BalloonTrans.scale_ = Bal_Ent_Size;
    Model::SetTransform(BalloonModel_, BalloonTrans);

    //Enter
    EnterImage_ = Image::Load("Image/InGameMenu/Enter.png");
    assert(EnterImage_ >= 0);
    EnterTrans.position_ = Enter_Pos;
    EnterTrans.scale_ = Bal_Ent_Size;
    Image::SetTransform(EnterImage_, EnterTrans);

    //暗転
    BackImage_ = Image::Load("Image/InGameMenu/Clear_Black.png");
    assert(BackImage_ >= 0);
    auto BlackTrans = Transform();
    BlackTrans.scale_ = BackImage_Size;
    Image::SetTransform(BackImage_, BlackTrans);

    //収縮用
    CircleImage_ = Image::Load("Image/InGameMenu/Clear_Effect.png");
    assert(CircleImage_ >= 0);
    CircleTrans.scale_ = XMFLOAT3(size_, size_, size_);

    //サウンド
    GoalSound_ = Audio::Load("Sound/InStage/Staging.wav");
    assert(GoalSound_ >= 0);
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
    if (gl.GetTransPos().x >= gl.GetCameraGoal().x - 1.5f)
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
            Audio::Play(GoalSound_);

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

        if (size_ > Size_Min)
        {
            size_ -= Scale_Down_Val;
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
    BalloonModel_ = -1;
    CircleImage_ = -1;
    EnterImage_ = -1;
    GoalSound_ = -1;
    BackImage_ = -1;
}

//時間管理
void GoalStaging::Timer()
{
    time_++;

    if (time_ >= TIME)
    {
        timer_ = true;
        time_ = 0;
    }
}
