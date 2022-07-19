#include "ItemImage.h"

//コンストラクタ
ItemImage::ItemImage(GameObject* parent)
    :GameObject(parent, "ItemImage"),
    FrameImage_(INITIAL_ERROR_VALUE), 
    CoinImage_(INITIAL_ERROR_VALUE)
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
    FrameTrans.scale_ = FRAME_SIZE;
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
    SceneManager* pSceneManager_ = (SceneManager*)FindObject("SceneManager");

    //現在シーンがSELECTの場合
    if (pSceneManager_->GetCurrentSceneID() == SCENE_ID_SELECT)
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
    FrameImage_ = INITIAL_ERROR_VALUE;
    CoinImage_ = INITIAL_ERROR_VALUE;
}