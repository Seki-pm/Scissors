#include "ItemImage.h"

//コンストラクタ
ItemImage::ItemImage(GameObject* parent)
    :GameObject(parent, "ItemImage"), ImageHandle_(-1)
{
}

//デストラクタ
ItemImage::~ItemImage()
{
}

//初期化
void ItemImage::Initialize()
{
    ImageHandle_ = Image::Load("ファイル名");
    assert(ImageHandle_);


}

//更新
void ItemImage::Update()
{
}

//描画
void ItemImage::Draw()
{
    Image::SetTransform(ImageHandle_, transform_);
    Image::Draw(ImageHandle_);
}

//開放
void ItemImage::Release()
{
}