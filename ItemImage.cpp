#include "ItemImage.h"

//�R���X�g���N�^
ItemImage::ItemImage(GameObject* parent)
    :GameObject(parent, "ItemImage"),
    FrameImage_(-1), CoinImage_(-1)
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
    FrameImage_ = Image::Load("Image/StageScene/GetCoinFrame.png");
    assert(FrameImage_);
    auto FrameTrans = Transform();
    FrameTrans.position_ = Global::ItemImagePos;
    FrameTrans.scale_ = XMFLOAT3(0.3f,0.3f,0.3f);
    Image::SetTransform(FrameImage_, FrameTrans);

    //�擾����
    CoinImage_ = Image::Load("Model/InGameObject/Coin.png");
    assert(CoinImage_);
    auto CoinTrans = Transform();
    CoinTrans.position_ = Global::ItemImagePos;
    CoinTrans.scale_ = Global::ItemImageSca;
    Image::SetTransform(CoinImage_, CoinTrans);

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
        Image::Draw(CoinImage_);
    }
    //����ȊO�i�X�e�[�W�V�[���̏ꍇ�j
    else
    {
        //�R�C�����擾������
        if (Global::GetCoin)
        {
            Image::Draw(CoinImage_); //�R�C���摜
        }
        //�R�C�����擾���Ă��Ȃ�
        else
        {
            Image::Draw(FrameImage_); //�t���[���摜
        }
    }
}

//�J��
void ItemImage::Release()
{
    FrameImage_ = -1;
    CoinImage_ = -1;
}