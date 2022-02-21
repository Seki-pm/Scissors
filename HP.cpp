#include "HP.h"

//�R���X�g���N�^
HP::HP(GameObject* parent)
    :GameObject(parent, "HP"),
    pNumber_(nullptr), pGauge_(nullptr),
    MaxHp(Global::HP)
{
}

//�f�X�g���N�^
HP::~HP()
{
}

//������
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

//�X�V
void HP::Update()
{
}

//�`��
void HP::Draw()
{

    pNumber_->Draw(Global::HP, 0, 0, NumberHandle_);
    pGauge_->Draw(Global::HP, 0, 0.5f, GaugeHandle_, MaxHp);
    Image::Draw(GaugeFrame_);
}

//�J��
void HP::Release()
{
}