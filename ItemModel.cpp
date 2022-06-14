#include "ItemModel.h"

//�R���X�g���N�^
ItemModel::ItemModel(GameObject* parent)
    :GameObject(parent, "ItemModel"),
     CoinModel_(-1),rotate(8), CoinSound_(-1)
{
}

//�f�X�g���N�^
ItemModel::~ItemModel()
{
}

//������
void ItemModel::Initialize()
{

    CoinModel_ = Model::Load("Model/InGameObject/Coin.fbx");
    assert(CoinModel_ >= 0);

    CoinSound_ = Audio::Load("Sound/InStage/Get_Coin.wav");
    assert(CoinSound_ >= 0);


    transform_.position_ = Global::ItemModelPos;
    transform_.scale_ = XMFLOAT3(1.1f, 1.1f , 1.1f);

    SphereCollider* collision = 
    new SphereCollider(XMFLOAT3(0, 0, 0), 0.6f);
    AddCollider(collision);
}

//�X�V
void ItemModel::Update()
{
    //�R�C�����擾������
    if (Global::GetCoin)
    {
        //rotate�̉�]���ɖ����Ȃ���Animation
        if (transform_.rotate_.y < rotate * 180)
        {
            Animation();
        }
        else{
            KillMe();  //����
        }
    }
}

//�`��
void ItemModel::Draw()
{
    Model::SetTransform(CoinModel_, transform_);
    Model::Draw(CoinModel_);
}

//�J��
void ItemModel::Release()
{
    CoinModel_ = -1;
    CoinSound_ = -1;
}

//�����ɓ�������
void ItemModel::OnCollision(GameObject* pTarget)
{
    //���������Ƃ��̏���
    //Player�ɓ��������Ƃ�
    if (pTarget->GetObjectName() == "Scissors")
    {
        //�ǂ��̃R�C�����擾������
        switch (Global::SelectStage)
        {
        case STAGE_NUMBER_1:
            Global::GetCoin_1 = true;
            break;
        case STAGE_NUMBER_2:
            Global::GetCoin_2 = true;
            break;
        case STAGE_NUMBER_3:
            Global::GetCoin_3 = true;
            break;
        }

        Global::GetCoin = true;
        Audio::Play(CoinSound_);
    }
}

//�ȈՃA�j���[�V����
void ItemModel::Animation()
{
    transform_.position_.y += 0.01f * 3;
    transform_.rotate_.y += 16.6f * 3;
}
