#include "ItemModel.h"

//コンストラクタ
ItemModel::ItemModel(GameObject* parent)
    :GameObject(parent, "ItemModel"), hModel_(-1)
{
}

//デストラクタ
ItemModel::~ItemModel()
{
}

//初期化
void ItemModel::Initialize()
{

    hModel_ = Model::Load("SuccessModel/Coin.fbx");
    assert(hModel_ >= 0);

    transform_.position_ = XMFLOAT3(-2.8f,2, 0);
    transform_.scale_ = XMFLOAT3(0.9f, 0.9f, 0.9f);

    SphereCollider* collision = 
        new SphereCollider(XMFLOAT3(1.3f, 16, 0), 0.8f);
    AddCollider(collision);
}

//更新
void ItemModel::Update()
{
    if (Global::GetCoin)
    {
        Model::SetAnimFrame(hModel_, 1, 60, 1);
    }
}

//描画
void ItemModel::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//開放
void ItemModel::Release()
{
}

//何かに当たった
void ItemModel::OnCollision(GameObject* pTarget)
{
    //当たったときの処理
    //弾に当たったとき
    if (pTarget->GetObjectName() == "Scissors")
    {
        Global::GetCoin = true;
        Model::SetAnimFrame(hModel_, 1, 120, 1);
    }
}