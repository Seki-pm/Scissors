#include "GoalStaging.h"


//コンストラクタ
GoalStaging::GoalStaging(GameObject* parent)
    :GameObject(parent, "GoalStaging"), hModel_(-1), BackImage_(-1), EnterImage_(-1),
    CircleImage_(-1), size_(10), flg(false), Sflg(false),timer(0)
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
    hModel_ = Model::Load("d.fbx");
    assert(hModel_ >= 0);
    BalloonTrans.position_ = XMFLOAT3(gl.GetCameraGoal(), 4.f, 0.f);
    BalloonTrans.scale_ = XMFLOAT3(0.8f, 0.8f, 0.8f);
    Model::SetTransform(hModel_, BalloonTrans);


    //画像データの読み込み
    //暗転
    BackImage_ = Image::Load("Image/Clear_Black.png");
    assert(BackImage_ >= 0);
    auto BlackTrans = Transform();
    BlackTrans.scale_ = XMFLOAT3(1.4f, 1.4f, 1.4f);
    Image::SetTransform(BackImage_, BlackTrans);

    CircleImage_ = Image::Load("Image/Clear_Effect.png");
    assert(CircleImage_ >= 0);
    CircleTrans.scale_ = XMFLOAT3(size_,size_,size_);



    //Enter
    EnterImage_ = Image::Load("Image/Enter.png");
    assert(EnterImage_ >= 0);
    EnterTrans.position_ = XMFLOAT3(0.1f, 0.1f, 0);
    EnterTrans.scale_ = XMFLOAT3(0.8f, 0.8f, 0.8f);
    Image::SetTransform(EnterImage_, EnterTrans);

 


}

//更新
void GoalStaging::Update()
{

    if (Input::IsKeyDown(DIK_I))
    {
        Model::SetAnimFrame(hModel_, 1, 300, 1.0f);
    }


    if (gl.GetTransPos_X() >= gl.GetCameraGoal() - 1.5f)
    {
        //文字表示
        Sflg = true;
    }
    else
    {
        Sflg = false;
    }

    if (flg) Timer();
}

//描画
void GoalStaging::Draw()
{
    Model::Draw(hModel_);

    //ゴール演出
    if(Sflg)
    {
        //文字表示
        Image::Draw(EnterImage_);

        //Enterキーを押したら
        if (Input::IsKeyDown(DIK_RETURN))
        {
            Sflg = false;
            //ゴール演出スタート
            flg = true;
        }
    }

    //暗転処理
    if (flg)
    {
        CircleTrans.scale_ = XMFLOAT3(size_, size_, size_);
        Image::SetTransform(CircleImage_, CircleTrans);

        if (size_ > 1.4f)
        {
            size_ -= 0.2f;
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
}

//時間管理
void GoalStaging::Timer()
{
    timer++;

    if (timer >= 60)
    {
        Global::Timer = true;
        timer = 0;
    }
}
