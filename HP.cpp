#include "HP.h"

//コンストラクタ
HP::HP(GameObject* parent)
    :GameObject(parent, "HP"),
    pNumber_(nullptr), pGauge_(nullptr),
    MaxHp(Global::HP)
{
}

//デストラクタ
HP::~HP()
{
}

//初期化
void HP::Initialize()
{
    NumberHandle_ = Image::Load("Number.png");
    assert(NumberHandle_ >= 0);

    GaugeHandle_ = Image::Load("Image/HP2.png");
    assert(GaugeHandle_ >= 0);

    GaugeFrame_ = Image::Load("Image/GaugeFrame.png");
    assert(GaugeFrame_ >= 0);
    FrameTrans.position_ = XMFLOAT3(-0.58f, 0.8f, 0);
    Image::SetTransform(GaugeFrame_, FrameTrans);

}

//更新
void HP::Update()
{
}

//描画
void HP::Draw()
{

    pNumber_->Draw(Global::HP, 0, 0, NumberHandle_);
    pGauge_->Draw(Global::HP, 0, 0.5f, GaugeHandle_, MaxHp);
    Image::Draw(GaugeFrame_);
}

//開放
void HP::Release()
{
}