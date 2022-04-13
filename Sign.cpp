#include "Sign.h"

//コンストラクタ
Sign::Sign(GameObject* parent)
    :GameObject(parent, "Sign"),
    TipsHandle_(-1), TipsHandle2_(-1), TipsHandle3_(-1), 
    TipsHandle4_(-1), TipsHandle5_(-1),size_(1.7f)
{
}

//デストラクタ
Sign::~Sign()
{
}

//初期化
void Sign::Initialize()
{
    //モデルデータのロード
    //方向を決める...ジャンプ...
    TipsHandle_ = Model::Load("SuccessModel/Sign1.fbx");
    assert(TipsHandle_ >= 0);
    auto SignTrans = Transform();
    SignTrans.position_ = XMFLOAT3(2, 0, 0);
    SignTrans.scale_ = XMFLOAT3(size_, size_, size_);
    Model::SetTransform(TipsHandle_, SignTrans);

    //刃が地面に刺さってる時は,,,
    TipsHandle2_ = Model::Load("SuccessModel/Sign2.fbx");
    assert(TipsHandle2_ >= 0);
    auto SignTrans2 = Transform();
    SignTrans2.position_ = XMFLOAT3(5, 0, 0);
    SignTrans2.scale_ = XMFLOAT3(size_, size_, size_);
    Model::SetTransform(TipsHandle2_, SignTrans2);

    //刃が地面に着くたびに...
    TipsHandle3_ = Model::Load("SuccessModel/Sign3.fbx");
    assert(TipsHandle3_ >= 0);
    auto SignTrans3 = Transform();
    SignTrans3.position_ = XMFLOAT3(8, 0, 0);
    SignTrans3.scale_ = XMFLOAT3(size_, size_, size_);
    Model::SetTransform(TipsHandle3_, SignTrans3);

    //壁に刃を向けてジャンプすると...
    TipsHandle4_ = Model::Load("SuccessModel/Sign4.fbx");
    assert(TipsHandle4_ >= 0);
    auto SignTrans4 = Transform();
    SignTrans4.position_ = XMFLOAT3(30, 0, 0);
    SignTrans4.scale_ = XMFLOAT3(size_, size_, size_);
    Model::SetTransform(TipsHandle4_, SignTrans4);

    //[Esc]を押すと...
    TipsHandle5_ = Model::Load("SuccessModel/Sign5.fbx");
    assert(TipsHandle5_ >= 0);
    auto SignTrans5 = Transform();
    SignTrans5.position_ = XMFLOAT3(11, 0, 0);
    SignTrans5.scale_ = XMFLOAT3(size_, size_, size_);
    Model::SetTransform(TipsHandle5_, SignTrans5);
}

//更新
void Sign::Update()
{
}

//描画
void Sign::Draw()
{
    Model::Draw(TipsHandle_);
    Model::Draw(TipsHandle2_);
    Model::Draw(TipsHandle3_);
    Model::Draw(TipsHandle4_);
    Model::Draw(TipsHandle5_);
}

//開放
void Sign::Release()
{
    TipsHandle_ = -1;
    TipsHandle2_ = -1;
    TipsHandle3_ = -1;
    TipsHandle4_ = -1;
    TipsHandle5_ = -1;
}