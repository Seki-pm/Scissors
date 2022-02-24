#include "ItemModel.h"

//コンストラクタ
ItemModel::ItemModel(GameObject* parent)
    :GameObject(parent, "ItemModel"), hModel_(-1),rotate(8)
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

    transform_.position_ = XMFLOAT3(-1.5f, 1, 0);
    transform_.scale_ = XMFLOAT3(1.1f, 1.1f , 1.1f);

    SphereCollider* collision = 
    new SphereCollider(XMFLOAT3(0, 0, 0), 0.6f);
    AddCollider(collision);
}

//更新
void ItemModel::Update()
{

    if (Global::GetCoin)
    {
        if (transform_.rotate_.y < rotate * 180)
        {
            Animation();
        }
        else
        {
            KillMe();
        }
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
    }
}

//簡易アニメーション
void ItemModel::Animation()
{
    transform_.position_.y += 0.01f * 3;
    transform_.rotate_.y += 16.6f * 3;
}
