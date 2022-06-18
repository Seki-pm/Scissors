#include "Sign.h"

//コンストラクタ
Sign::Sign(GameObject* parent)
    :GameObject(parent, "Sign"),
    TipsHandle_(-1), TipsHandle2_(-1), TipsHandle3_(-1), 
    TipsHandle4_(-1), TipsHandle5_(-1),size_(1.7f),
    Tutorial_(-1), Tutorial2_(-1)
{
}

//デストラクタ
Sign::~Sign()
{
}

//初期化
void Sign::Initialize()
{
    //===================== 看板モデルのロード ==============================
    //方向を決める...ジャンプ...
    TipsHandle_ = Model::Load("Model/InGameObject/Sign1.fbx");
    assert(TipsHandle_ >= 0);
    SignTrans.position_ = XMFLOAT3(2, 0, 0);
    SignTrans.scale_ = XMFLOAT3(size_, size_, size_);
    Model::SetTransform(TipsHandle_, SignTrans);

    //刃が地面に刺さってる時は,,,
    TipsHandle2_ = Model::Load("Model/InGameObject/Sign2.fbx");
    assert(TipsHandle2_ >= 0);
    SignTrans2.position_ = XMFLOAT3(8, 0, 0);
    SignTrans2.scale_ = XMFLOAT3(size_, size_, size_);
    Model::SetTransform(TipsHandle2_, SignTrans2);

    //刃が地面に着くたびに...
    TipsHandle3_ = Model::Load("Model/InGameObject/Sign3.fbx");
    assert(TipsHandle3_ >= 0);
    auto SignTrans3 = Transform();
    SignTrans3.position_ = XMFLOAT3(11, 0, 0);
    SignTrans3.scale_ = XMFLOAT3(size_, size_, size_);
    Model::SetTransform(TipsHandle3_, SignTrans3);

    //[Esc]を押すと...
    TipsHandle4_ = Model::Load("Model/InGameObject/Sign4.fbx");
    assert(TipsHandle4_ >= 0);
    auto SignTrans4 = Transform();
    SignTrans4.position_ = XMFLOAT3(11, 0, 0);
    SignTrans4.scale_ = XMFLOAT3(size_, size_, size_);
    Model::SetTransform(TipsHandle4_, SignTrans4);


    //壁に刃を向けてジャンプすると...
    TipsHandle5_ = Model::Load("Model/InGameObject/Sign5.fbx");
    assert(TipsHandle5_ >= 0);
    SignTrans5.position_ = XMFLOAT3(30, 0, 0);
    SignTrans5.scale_ = XMFLOAT3(size_, size_, size_);
    Model::SetTransform(TipsHandle5_, SignTrans5);




    //====================  チュートリアル画像  =======================
    Tutorial_ = Image::Load("Image/StageScene/Tutorial.png");
    assert(Tutorial_ >= 0);
    auto TutorialTrans = Transform();
    TutorialTrans.position_ = XMFLOAT3(0, 0.65f,0);
    TutorialTrans.scale_ = XMFLOAT3(0.5f, 0.5f, 0.5f);
    Image::SetTransform(Tutorial_, TutorialTrans);


    Tutorial2_ = Image::Load("Image/StageScene/Tutorial2.png");
    assert(Tutorial2_ >= 0);
    Image::SetTransform(Tutorial2_, TutorialTrans);


}

//更新
void Sign::Update()
{
}

//描画
void Sign::Draw()
{
    //看板の描画
    Model::Draw(TipsHandle_);
    Model::Draw(TipsHandle2_);
    Model::Draw(TipsHandle3_);
    Model::Draw(TipsHandle4_);
    Model::Draw(TipsHandle5_);


    //条件付きでチュートリアルの描画
    if (gl.GetTransPos_X() >= SignTrans.position_.x &&
        gl.GetTransPos_X() <= SignTrans2.position_.x)
    {
        Image::Draw(Tutorial_);
    }

    if (gl.GetTransPos_X() >= SignTrans5.position_.x &&
        gl.GetTransPos_Y() <= 4.5f)
    {
        Image::Draw(Tutorial2_);
    }
}

//開放
void Sign::Release()
{
    TipsHandle_ = -1;
    TipsHandle2_ = -1;
    TipsHandle3_ = -1;
    TipsHandle4_ = -1;
    TipsHandle5_ = -1;
    Tutorial_ = -1;
    Tutorial2_ = -1;
}