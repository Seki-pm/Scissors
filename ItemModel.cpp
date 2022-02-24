#include "ItemModel.h"

//�R���X�g���N�^
ItemModel::ItemModel(GameObject* parent)
    :GameObject(parent, "ItemModel"), hModel_(-1),rotate(8)
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

    transform_.position_ = XMFLOAT3(-1.5f, 1, 0);
    transform_.scale_ = XMFLOAT3(1.1f, 1.1f , 1.1f);

    SphereCollider* collision = 
    new SphereCollider(XMFLOAT3(0, 0, 0), 0.6f);
    AddCollider(collision);
}

//�X�V
void ItemModel::Update()
{

    if (Global::GetCoin)
    {
        if (transform_.rotate_.y < rotate * 180)
        {
            Animation();
        }
        else
        {
            KillMe();
        }
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
    }
}

//�ȈՃA�j���[�V����
void ItemModel::Animation()
{
    transform_.position_.y += 0.01f * 3;
    transform_.rotate_.y += 16.6f * 3;
}
