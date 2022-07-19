#include "HP.h"
#include "Scissors.h"

//�R���X�g���N�^
HP::HP(GameObject* parent)
    :GameObject(parent, "HP"),
     pGauge_(nullptr), pScissors_(nullptr),
     GaugeImage_(INITIAL_ERROR_VALUE), 
     GaugeFrameImage_(INITIAL_ERROR_VALUE)
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
    FrameTrans.position_ = FRAME_POS;
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
    pGauge_->Draw(pScissors_->CurrentHP, HP_IMAGE_POS.x, HP_IMAGE_POS.y, GaugeImage_);
    Image::Draw(GaugeFrameImage_);
}

//�J��
void HP::Release()
{
    GaugeImage_ = INITIAL_ERROR_VALUE;
    GaugeFrameImage_ = INITIAL_ERROR_VALUE;
}

//HP�v�Z
void HP::HPCalc()
{
    float JS = pScissors_->JumpStart;  //�W�����v�J�n�ʒu
    float JE = pScissors_->JumpEnd;    //�W�����v���n�ʒu
    float ND = NORMAL_DAMAGE;          //�_���[�W��

    //�����Ƃ��납��~�肽��
    if (JS - JE > HAS_DAMAGE)
    {
        pScissors_->CurrentHP -= (JS - JE + ND) * 2;
    }

    //���ʈړ�or�����
    if (JS - JE <= HAS_DAMAGE)
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
