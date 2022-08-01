#include "ItemModel.h"

//�R���X�g���N�^
ItemModel::ItemModel(GameObject* parent)
    :GameObject(parent, "ItemModel"),
     CoinModel_(INITIAL_ERROR_VALUE), 
     CoinSound_(INITIAL_ERROR_VALUE)
{
}

//�f�X�g���N�^
ItemModel::~ItemModel()
{
}

//������
void ItemModel::Initialize()
{
    //----- �f�[�^�̓ǂݍ��� ------ 
    {
        //-------------- �R�C�����f�� --------------------
        CoinModel_ = Model::Load("Model/InGameObject/Coin.fbx");
        assert(CoinModel_ >= 0);

        //------------ �擾���̃T�E���h ------------------
        CoinSound_ = Audio::Load("Sound/InStage/Get_Coin.wav");
        assert(CoinSound_ >= 0);
    }
    //-----------------------------

    //�R�C���̈ʒu��ݒ�
    transform_.position_ = Game::ItemModelPos;
    transform_.scale_ = ITEM_SIZE;

    //�R���C�_�ݒ�
    SphereCollider* collision = 
    new SphereCollider(XMFLOAT3(0, 0, 0), 0.6f);
    AddCollider(collision);
}

//�X�V
void ItemModel::Update()
{
    //�R�C�����擾������
    if (Game::GetCoin)
    {
        //ROTATION_NUMBER�̒l�ɖ����Ȃ���Animation
        if (transform_.rotate_.y < ROTATION_NUMBER * 180)
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
    CoinModel_ = INITIAL_ERROR_VALUE;
    CoinSound_ = INITIAL_ERROR_VALUE;
}

//�����ɓ�������
void ItemModel::OnCollision(GameObject* pTarget)
{

    //���������Ƃ��̏���
    //Player�ɓ��������Ƃ�
    if (pTarget->GetObjectName() == "Scissors")
    {
        //�ǂ��̃R�C�����擾������
        switch (Game::SelectStage)
        {
        case STAGE_NUMBER_1: game.setState(Game::stage1.GetCoin); break;
        case STAGE_NUMBER_2: game.setState(Game::stage2.GetCoin); break;
        case STAGE_NUMBER_3: game.setState(Game::stage3.GetCoin); break;
        }

        Game::GetCoin = true;
        Audio::Play(CoinSound_);
    }
}

//�ȈՃA�j���[�V����
void ItemModel::Animation()
{
    //��]���Ȃ���㏸
    transform_.position_.y += UP_DISTANCE * 3;
    transform_.rotate_.y += ROTATION_SPEED * 3;
}
