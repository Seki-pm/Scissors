#include "GoalStaging.h"


//コンストラクタ
GoalStaging::GoalStaging(GameObject* parent)
    :GameObject(parent, "GoalStaging"), hModel_(-1), BackImage_(-1), EnterImage_(-1),
    CircleImage_(-1), size_(10), flg(false), Sflg(false), Aflg(false)
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
    auto BalloonTrans = Transform();
    BalloonTrans.position_ = XMFLOAT3(gl.GetCameraGoal(), 4.f, 0.f);
    BalloonTrans.scale_ = XMFLOAT3(0.8f, 0.8f, 0.8f);
    Model::SetTransform(hModel_, BalloonTrans);


    //画像データの読み込み
    BackImage_ = Image::Load("Image/GameOverBack.png");
    assert(BackImage_ >= 0);


    CircleImage_ = Image::Load("Image/GetCoinFrame.png");
    assert(CircleImage_ >= 0);
    CircleTrans.scale_ = XMFLOAT3(size_,size_,size_);

    EnterImage_ = Image::Load("Image/HP.png");
    assert(EnterImage_ >= 0);
    //EnterTrans.scale_ = XMFLOAT3(0.5f, 0.5f, 0.5f);
}

//更新
void GoalStaging::Update()
{
    float X = gl.GetTransPos_X();

    EnterTrans.position_ = XMFLOAT3( X, gl.GetTransPos_Y() + 0.5f, 0);


    if (Input::IsKeyDown(DIK_I))
    {
        Model::SetAnimFrame(hModel_, 1, 300, 1.0f);
    }

    if (Input::IsKeyDown(DIK_P))
    {
        flg = true;

    }


    if (gl.GetTransPos_X() >= gl.GetCameraGoal() - 1)
    {
        //表示flg = true
        Sflg = true;
    }
    else
    {
        Sflg = false;
    }
}

//描画
void GoalStaging::Draw()
{
    if (flg)
    {
        Image::Draw(BackImage_);
        CircleTrans.scale_ = XMFLOAT3(size_, size_, size_);
        Image::SetTransform(CircleImage_, CircleTrans);

        //サークルの収縮
        if (size_ > -0.2f)
        {
            size_ -= 0.2f;
            Image::Draw(CircleImage_);
        }

    }

    Image::SetTransform(EnterImage_, EnterTrans);
    Image::Draw(EnterImage_);
    if(Sflg)
    {
        //文字表示


        //Enterキーを押したら
        if (Input::IsKeyDown(DIK_RETURN))
        {
            //ゴール演出スタート
            Aflg = true;
        }
    }


    Model::Draw(hModel_);
}

//開放
void GoalStaging::Release()
{
    EnterImage_ = -1;
}