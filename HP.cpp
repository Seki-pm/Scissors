#include "HP.h"

//�R���X�g���N�^
HP::HP(GameObject* parent)
    :GameObject(parent, "HP"),
    pGauge_(nullptr),GaugeHandle_(-1), GaugeFrame_(-1)
{
}

//�f�X�g���N�^
HP::~HP()
{
}

//������
void HP::Initialize()
{
    //�Q�[�W
    GaugeHandle_ = Image::Load("Image/StageScene/HP.png");
    assert(GaugeHandle_ >= 0);

    //�Q�[�W�t���[��
    GaugeFrame_ = Image::Load("Image/StageScene/GaugeFrame.png");
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
    pGauge_->Draw(Global::HP, -0.978f, 0.77f, GaugeHandle_);
    Image::Draw(GaugeFrame_);
}

//�J��
void HP::Release()
{
    GaugeHandle_ = -1;
    GaugeFrame_ = -1;
}

//HP�v�Z
void HP::HPCalc()
{
    float JS = Global::JumpStart;
    float JE = Global::JumpEnd;
    float ND = Global::NORMAL_DAMAGE;

    //�����Ƃ��납��~�肽��
    if (JS - JE > 0.5f)
    {
        Global::HP -= (JS - JE + ND) * 2;
    }

    //���ʈړ�or�����
    if (JS - JE <= 0.5f)
    {
        Global::HP -= ND;
    }

    //�Q�[���I�[�o�[����
    if (Global::HP <= 0)
    {
        Global::IsGameOver = true;
        Global::GameOver = true;
    }
}
