#include "ItemImage.h"

//コンストラクタ
ItemImage::ItemImage(GameObject* parent)
    :GameObject(parent, "ItemImage"),
    FrameImage_(-1), CoinImage_(-1)
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
    FrameImage_ = Image::Load("Image/StageScene/GetCoinFrame.png");
    assert(FrameImage_);
    auto FrameTrans = Transform();
    FrameTrans.position_ = Global::ItemImagePos;
    FrameTrans.scale_ = XMFLOAT3(0.3f,0.3f,0.3f);
    Image::SetTransform(FrameImage_, FrameTrans);

    //取得した
    CoinImage_ = Image::Load("Model/InGameObject/Coin.png");
    assert(CoinImage_);
    auto CoinTrans = Transform();
    CoinTrans.position_ = Global::ItemImagePos;
    CoinTrans.scale_ = Global::ItemImageSca;
    Image::SetTransform(CoinImage_, CoinTrans);

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
        Image::Draw(CoinImage_);
    }
    //それ以外（ステージシーンの場合）
    else
    {
        //コインを取得したら
        if (Global::GetCoin)
        {
            Image::Draw(CoinImage_); //コイン画像
        }
        //コインを取得していない
        else
        {
            Image::Draw(FrameImage_); //フレーム画像
        }
    }
}

//開放
void ItemImage::Release()
{
    FrameImage_ = -1;
    CoinImage_ = -1;
}