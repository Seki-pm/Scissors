#include "ItemModel.h"

//�R���X�g���N�^
ItemModel::ItemModel(GameObject* parent)
    :GameObject(parent, "ItemModel"), hModel_(-1)
{
}

//�f�X�g���N�^
ItemModel::~ItemModel()
{
}

//������
void ItemModel::Initialize()
{

    hModel_ = Model::Load("SuccessModel/Coin.fbx");
    assert(hModel_ >= 0);

    transform_.position_ = XMFLOAT3(-2.8f,2, 0);
    transform_.scale_ = XMFLOAT3(0.9f, 0.9f, 0.9f);

    SphereCollider* collision = 
        new SphereCollider(XMFLOAT3(1.3f, 16, 0), 0.8f);
    AddCollider(collision);
}

//�X�V
void ItemModel::Update()
{
    if (Global::GetCoin)
    {
        Model::SetAnimFrame(hModel_, 1, 60, 1);
    }
}

//�`��
void ItemModel::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//�J��
void ItemModel::Release()
{
}

//�����ɓ�������
void ItemModel::OnCollision(GameObject* pTarget)
{
    //���������Ƃ��̏���
    //�e�ɓ��������Ƃ�
    if (pTarget->GetObjectName() == "Scissors")
    {
        Global::GetCoin = true;
        Model::SetAnimFrame(hModel_, 1, 120, 1);
    }
}