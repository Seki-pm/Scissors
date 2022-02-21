#include "ItemImage.h"

//�R���X�g���N�^
ItemImage::ItemImage(GameObject* parent)
    :GameObject(parent, "ItemImage"), ImageHandle_(-1)
{
}

//�f�X�g���N�^
ItemImage::~ItemImage()
{
}

//������
void ItemImage::Initialize()
{
    ImageHandle_ = Image::Load("�t�@�C����");
    assert(ImageHandle_);


}

//�X�V
void ItemImage::Update()
{
}

//�`��
void ItemImage::Draw()
{
    Image::SetTransform(ImageHandle_, transform_);
    Image::Draw(ImageHandle_);
}

//�J��
void ItemImage::Release()
{
}