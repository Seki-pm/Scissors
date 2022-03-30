#include "ItemModel.h"

//�R���X�g���N�^
ItemModel::ItemModel(GameObject* parent)
    :GameObject(parent, "ItemModel"), Coin_(-1),rotate(8), Coin_Sound(-1)
{
}

//�f�X�g���N�^
ItemModel::~ItemModel()
{
}

//������
void ItemModel::Initialize()
{

    Coin_ = Model::Load("SuccessModel/Coin.fbx");
    assert(Coin_ >= 0);

    Coin_Sound = Audio::Load("Sound/Get_Coin.wav");
    assert(Coin_Sound >= 0);



    transform_.position_ = XMFLOAT3(-1.5f, 17, 0);
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
        Audio::Play(Coin_Sound);

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
    Model::SetTransform(Coin_, transform_);
    Model::Draw(Coin_);
}

//�J��
void ItemModel::Release()
{
    Coin_ = -1;
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
