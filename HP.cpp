#include "HP.h"
#include "Scissors.h"

#define NORMAL_DAMAGE 1

//�R���X�g���N�^
HP::HP(GameObject* parent)
    :GameObject(parent, "HP"),
    pGauge_(nullptr),GaugeImage_(-1), GaugeFrameImage_(-1)
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
    GaugeImage_ = Image::Load("Image/StageScene/HP.png");
    assert(GaugeImage_ >= 0);

    //�Q�[�W�t���[��
    GaugeFrameImage_ = Image::Load("Image/StageScene/GaugeFrame.png");
    assert(GaugeFrameImage_ >= 0);
    FrameTrans.position_ = XMFLOAT3(-0.59f, 0.88f, 0);
    Image::SetTransform(GaugeFrameImage_, FrameTrans);

    pScissors_ = (Scissors*)FindObject("Scissors");
}

//�X�V
void HP::Update()
{
}

//�`��
void HP::Draw()
{
    pGauge_->Draw(pScissors_->CurrentHP, -0.99f, 0.85f, GaugeImage_);
    Image::Draw(GaugeFrameImage_);
}

//�J��
void HP::Release()
{
    GaugeImage_ = -1;
    GaugeFrameImage_ = -1;
}

//HP�v�Z
void HP::HPCalc()
{
    float JS = Global::JumpStart;
    float JE = Global::JumpEnd;
    float ND = NORMAL_DAMAGE;

    //�����Ƃ��납��~�肽��
    if (JS - JE > 0.5f)
    {
        pScissors_->CurrentHP -= (JS - JE + ND) * 2;
    }

    //���ʈړ�or�����
    if (JS - JE <= 0.5f)
    {
        pScissors_->CurrentHP -= ND;
    }

    //�Q�[���I�[�o�[����
    if (pScissors_->CurrentHP <= 0)
    {
        Global::IsGameOver = true;
        Global::GameOver = true;
    }
}
