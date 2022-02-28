#include "GoalStaging.h"
#include "Engine/Input.h"
#include "Engine/Image.h"

//�R���X�g���N�^
GoalStaging::GoalStaging(GameObject* parent)
    :GameObject(parent, "GoalStaging"), hModel_(-1), BackImage_(-1), CircleImage_(-1), size_(10),flg(false)
{
}

//�f�X�g���N�^
GoalStaging::~GoalStaging()
{
}

//������
void GoalStaging::Initialize()
{
    //���f���f�[�^�̃��[�h
    hModel_ = Model::Load("d.fbx");
    assert(hModel_ >= 0);
    auto BalloonTrans = Transform();
    Model::SetTransform(hModel_, BalloonTrans);


    //�摜�f�[�^�̓ǂݍ���
    BackImage_ = Image::Load("Image/GameOverBack.png");
    assert(BackImage_ >= 0);


    CircleImage_ = Image::Load("Image/GetCoinFrame.png");
    assert(CircleImage_ >= 0);
    CircleTrans.scale_ = XMFLOAT3(size_,size_,size_);


    //transform_.position_ = XMFLOAT3(2.0f,0.f,0.f);
    //transform_.scale_ = XMFLOAT3(0.4f,0.4f,0.4f);
}

//�X�V
void GoalStaging::Update()
{
    if (Input::IsKeyDown(DIK_I))
    {
        Model::SetAnimFrame(hModel_, 1, 300, 1.0f);
    }

    if (Input::IsKeyDown(DIK_P))
    {
        flg = true;

    }
}

//�`��
void GoalStaging::Draw()
{
    if (flg)
    {
        if (size_ > 0)
        {
            size_ -= 0.2f;
        }
        CircleTrans.scale_ = XMFLOAT3(size_, size_, size_);
        Image::SetTransform(CircleImage_, CircleTrans);

        Image::Draw(BackImage_);
        Image::Draw(CircleImage_);
    }



    Model::Draw(hModel_);
}

//�J��
void GoalStaging::Release()
{
}