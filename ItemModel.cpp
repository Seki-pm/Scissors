#include "ItemModel.h"

#define Item_Size XMFLOAT3(1.1f,1.1f,1.1f);

const float Rotation_Speed = 16.6f;
const float Up_Distance = 0.01f;
const int   Rotation_Number = 8;

//コンストラクタ
ItemModel::ItemModel(GameObject* parent)
    :GameObject(parent, "ItemModel"),
     CoinModel_(-1),rotate(Rotation_Number), CoinSound_(-1)
{
}

//デストラクタ
ItemModel::~ItemModel()
{
}

//初期化
void ItemModel::Initialize()
{

    CoinModel_ = Model::Load("Model/InGameObject/Coin.fbx");
    assert(CoinModel_ >= 0);

    CoinSound_ = Audio::Load("Sound/InStage/Get_Coin.wav");
    assert(CoinSound_ >= 0);


    transform_.position_ = Global::ItemModelPos;
    transform_.scale_ = Item_Size;

    SphereCollider* collision = 
    new SphereCollider(XMFLOAT3(0, 0, 0), 0.6f);
    AddCollider(collision);
}

//更新
void ItemModel::Update()
{
    //コインを取得したら
    if (Global::GetCoin)
    {
        //rotateの回転数に満たない間Animation
        if (transform_.rotate_.y < rotate * 180)
        {
            Animation();
        }
        else{
            KillMe();  //消す
        }
    }
}

//描画
void ItemModel::Draw()
{
    Model::SetTransform(CoinModel_, transform_);
    Model::Draw(CoinModel_);
}

//開放
void ItemModel::Release()
{
    CoinModel_ = -1;
    CoinSound_ = -1;
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
        Audio::Play(CoinSound_);
    }
}

//簡易アニメーション
void ItemModel::Animation()
{
    transform_.position_.y += Up_Distance * 3;
    transform_.rotate_.y += Rotation_Speed * 3;
}
