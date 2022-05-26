#include "ItemModel.h"

//コンストラクタ
ItemModel::ItemModel(GameObject* parent)
    :GameObject(parent, "ItemModel"),
     Coin_(-1),rotate(8), Coin_Sound(-1)
{
}

//デストラクタ
ItemModel::~ItemModel()
{
}

//初期化
void ItemModel::Initialize()
{

    Coin_ = Model::Load("SuccessModel/Coin.fbx");
    assert(Coin_ >= 0);

    Coin_Sound = Audio::Load("Sound/Get_Coin.wav");
    assert(Coin_Sound >= 0);


    transform_.position_ = Global::ItemModelPos;
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
        //rotateの回転数に満たない間Animation
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
    Model::SetTransform(Coin_, transform_);
    Model::Draw(Coin_);
}

//開放
void ItemModel::Release()
{
    Coin_ = -1;
    Coin_Sound = -1;
}

//何かに当たった
void ItemModel::OnCollision(GameObject* pTarget)
{
    //当たったときの処理
    //Playerに当たったとき
    if (pTarget->GetObjectName() == "Scissors")
    {
        //どこのコインを取得したか
        switch (Global::SelectStage)
        {
        case STAGE_NUMBER_1:
            Global::GetCoin_1 = true;
            break;
        case STAGE_NUMBER_2:
            Global::GetCoin_2 = true;
            break;
        case STAGE_NUMBER_3:
            Global::GetCoin_3 = true;
            break;
        }

        Global::GetCoin = true;
        Audio::Play(Coin_Sound);
    }
}

//簡易アニメーション
void ItemModel::Animation()
{
    transform_.position_.y += 0.01f * 3;
    transform_.rotate_.y += 16.6f * 3;
}
