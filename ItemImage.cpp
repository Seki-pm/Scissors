#include "ItemImage.h"

//コンストラクタ
ItemImage::ItemImage(GameObject* parent)
    :GameObject(parent, "ItemImage"),
    FrameHandle_(-1), CoinHandle_(-1)
{
}

//デストラクタ
ItemImage::~ItemImage()
{
}

//初期化
void ItemImage::Initialize()
{

    //取得していない
    FrameHandle_ = Image::Load("Image/GetCoinFrame.png");
    assert(FrameHandle_);
    auto FrameTrans = Transform();
    FrameTrans.position_ = Global::ItemImagePos;
    FrameTrans.scale_ = XMFLOAT3(0.3f,0.3f,0.3f);
    Image::SetTransform(FrameHandle_, FrameTrans);

    //取得した
    CoinHandle_ = Image::Load("SuccessModel/Coin.png");
    assert(CoinHandle_);
    auto CoinTrans = Transform();
    CoinTrans.position_ = Global::ItemImagePos_Stage;
    CoinTrans.scale_ = XMFLOAT3(0.5f,0.5f,0.5f);
    Image::SetTransform(CoinHandle_, CoinTrans);

}

//更新
void ItemImage::Update()
{
}

//描画
void ItemImage::Draw()
{
    //現在シーンがSELECTの場合
    if (Global::SCENE_ID == SCENE_ID_SELECT)
    {
        //コインを表示
        Image::Draw(CoinHandle_);
    }
    //それ以外（ステージシーンの場合）
    else
    {
        //コインを取得したら
        if (Global::GetCoin)
        {
            Image::Draw(CoinHandle_); //コイン画像
        }
        //コインを取得していない
        else
        {
            Image::Draw(FrameHandle_); //フレーム画像
        }
    }
}

//開放
void ItemImage::Release()
{
    FrameHandle_ = -1;
    CoinHandle_ = -1;
}