#include "ItemImage.h"

//�R���X�g���N�^
ItemImage::ItemImage(GameObject* parent)
    :GameObject(parent, "ItemImage"),
    FrameHandle_(-1), CoinHandle_(-1)
{
}

//�f�X�g���N�^
ItemImage::~ItemImage()
{
}

//������
void ItemImage::Initialize()
{

    //�擾���Ă��Ȃ�
    FrameHandle_ = Image::Load("Image/GetCoinFrame.png");
    assert(FrameHandle_);
    auto FrameTrans = Transform();
    FrameTrans.position_ = Global::ItemImagePos;
    FrameTrans.scale_ = XMFLOAT3(0.3f,0.3f,0.3f);
    Image::SetTransform(FrameHandle_, FrameTrans);

    //�擾����
    CoinHandle_ = Image::Load("SuccessModel/Coin.png");
    assert(CoinHandle_);
    auto CoinTrans = Transform();
    CoinTrans.position_ = Global::ItemImagePos_Stage;
    CoinTrans.scale_ = XMFLOAT3(0.5f,0.5f,0.5f);
    Image::SetTransform(CoinHandle_, CoinTrans);

}

//�X�V
void ItemImage::Update()
{
}

//�`��
void ItemImage::Draw()
{
    //���݃V�[����SELECT�̏ꍇ
    if (Global::SCENE_ID == SCENE_ID_SELECT)
    {
        //�R�C����\��
        Image::Draw(CoinHandle_);
    }
    //����ȊO�i�X�e�[�W�V�[���̏ꍇ�j
    else
    {
        //�R�C�����擾������
        if (Global::GetCoin)
        {
            Image::Draw(CoinHandle_); //�R�C���摜
        }
        //�R�C�����擾���Ă��Ȃ�
        else
        {
            Image::Draw(FrameHandle_); //�t���[���摜
        }
    }
}

//�J��
void ItemImage::Release()
{
    FrameHandle_ = -1;
    CoinHandle_ = -1;
}