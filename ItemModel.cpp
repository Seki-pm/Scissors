#include "ItemModel.h"

//コンストラクタ
ItemModel::ItemModel(GameObject* parent)
    :GameObject(parent, "ItemModel"),
     CoinModel_(INITIAL_ERROR_VALUE), 
     CoinSound_(INITIAL_ERROR_VALUE)
{
}

//デストラクタ
ItemModel::~ItemModel()
{
}

//初期化
void ItemModel::Initialize()
{
    //----- データの読み込み ------ 
    {
        //-------------- コインモデル --------------------
        CoinModel_ = Model::Load("Model/InGameObject/Coin.fbx");
        assert(CoinModel_ >= 0);

        //------------ 取得時のサウンド ------------------
        CoinSound_ = Audio::Load("Sound/InStage/Get_Coin.wav");
        assert(CoinSound_ >= 0);
    }
    //-----------------------------

    //コインの位置を設定
    transform_.position_ = Game::ItemModelPos;
    transform_.scale_ = ITEM_SIZE;

    //コライダ設定
    SphereCollider* collision = 
    new SphereCollider(XMFLOAT3(0, 0, 0), 0.6f);
    AddCollider(collision);
}

//更新
void ItemModel::Update()
{
    //コインを取得したら
    if (Game::GetCoin)
    {
        //ROTATION_NUMBERの値に満たない間Animation
        if (transform_.rotate_.y < ROTATION_NUMBER * 180)
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
    CoinModel_ = INITIAL_ERROR_VALUE;
    CoinSound_ = INITIAL_ERROR_VALUE;
}

//何かに当たった
void ItemModel::OnCollision(GameObject* pTarget)
{

    //当たったときの処理
    //Playerに当たったとき
    if (pTarget->GetObjectName() == "Scissors")
    {
        //どこのコインを取得したか
        switch (Game::SelectStage)
        {
        case STAGE_NUMBER_1: game.setState(Game::stage1.GetCoin); break;
        case STAGE_NUMBER_2: game.setState(Game::stage2.GetCoin); break;
        case STAGE_NUMBER_3: game.setState(Game::stage3.GetCoin); break;
        }

        Game::GetCoin = true;
        Audio::Play(CoinSound_);
    }
}

//簡易アニメーション
void ItemModel::Animation()
{
    //回転しながら上昇
    transform_.position_.y += UP_DISTANCE * 3;
    transform_.rotate_.y += ROTATION_SPEED * 3;
}
