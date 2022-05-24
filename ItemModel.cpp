#include "ItemModel.h"

//�R���X�g���N�^
ItemModel::ItemModel(GameObject* parent)
    :GameObject(parent, "ItemModel"),
     Coin_(-1),rotate(8), Coin_Sound(-1)
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


    transform_.position_ = Global::ItemModelPos;
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
    Model::SetTransform(Coin_, transform_);
    Model::Draw(Coin_);
}

//�J��
void ItemModel::Release()
{
    Coin_ = -1;
    Coin_Sound = -1;
}

//�����ɓ�������
void ItemModel::OnCollision(GameObject* pTarget)
{
    //���������Ƃ��̏���
    //Player�ɓ��������Ƃ�
    if (pTarget->GetObjectName() == "Scissors")
    {
        //�ǂ��̃R�C�����擾������
        switch (Global::SCENE_ID)
        {
        case SCENE_ID_STAGE1:
            Global::GetCoin_1 = true;
            break;
        case SCENE_ID_STAGE2:
            Global::GetCoin_2 = true;
            break;
        case SCENE_ID_STAGE3:
            Global::GetCoin_3 = true;
            break;
        }

        Global::GetCoin = true;
        Audio::Play(Coin_Sound);
    }
}

//�ȈՃA�j���[�V����
void ItemModel::Animation()
{
    transform_.position_.y += 0.01f * 3;
    transform_.rotate_.y += 16.6f * 3;
}
