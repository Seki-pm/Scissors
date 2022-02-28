#include "ItemImage.h"

//コンストラクタ
ItemImage::ItemImage(GameObject* parent)
    :GameObject(parent, "ItemImage"), FrameHandle_(-1), CoinHandle_(-1)
{
}

//デストラクタ
ItemImage::~ItemImage()
{
}

//初期化
void ItemImage::Initialize()
{
    FrameHandle_ = Image::Load("Image/GetCoinFrame.png");
    assert(FrameHandle_);
    auto FrameTrans = Transform();
    FrameTrans.position_ = XMFLOAT3(0.9f,0.8f,0.f);
    FrameTrans.scale_ = XMFLOAT3(0.3f,0.3f,0.3f);
    Image::SetTransform(FrameHandle_, FrameTrans);



    CoinHandle_ = Image::Load("SuccessModel/Coin.png");
    assert(CoinHandle_);
    auto CoinTrans = Transform();
    CoinTrans.position_ = XMFLOAT3(0.9f,0.8f,0.f);
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


    if (Global::GetCoin)
    {
        Image::Draw(CoinHandle_);
    }
    else
    {
        Image::Draw(FrameHandle_);
    }
}

//開放
void ItemImage::Release()
{
    FrameHandle_ = -1;
    CoinHandle_ = -1;
}