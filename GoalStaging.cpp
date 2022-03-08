#include "GoalStaging.h"
#include "Engine/Input.h"
#include "Engine/Image.h"
#include "Global.h"

//�R���X�g���N�^
GoalStaging::GoalStaging(GameObject* parent)
    :GameObject(parent, "GoalStaging"), hModel_(-1), BackImage_(-1),
    CircleImage_(-1), size_(10),flg(false)
{
}

//�f�X�g���N�^
GoalStaging::~GoalStaging()
{
}

//������
void GoalStaging::Initialize()
{
    Global gl;

    //���f���f�[�^�̃��[�h
    hModel_ = Model::Load("d.fbx");
    assert(hModel_ >= 0);
    auto BalloonTrans = Transform();
    BalloonTrans.position_ = XMFLOAT3(gl.GetCameraGoal(), 4.f, 0.f);
    BalloonTrans.scale_ = XMFLOAT3(0.8f, 0.8f, 0.8f);
    Model::SetTransform(hModel_, BalloonTrans);


    //�摜�f�[�^�̓ǂݍ���
    BackImage_ = Image::Load("Image/GameOverBack.png");
    assert(BackImage_ >= 0);


    CircleImage_ = Image::Load("Image/GetCoinFrame.png");
    assert(CircleImage_ >= 0);
    CircleTrans.scale_ = XMFLOAT3(size_,size_,size_);
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

    //Enter�L�[����������
    if (Input::IsKeyDown(DIK_RETURN))
    {
        
    }
}

//�`��
void GoalStaging::Draw()
{
    if (flg)
    {
        Image::Draw(BackImage_);
        CircleTrans.scale_ = XMFLOAT3(size_, size_, size_);
        Image::SetTransform(CircleImage_, CircleTrans);

        //�T�[�N���̎��k
        if (size_ > -0.2f)
        {
            size_ -= 0.2f;
            Image::Draw(CircleImage_);
        }

    }





    Model::Draw(hModel_);
}

//�J��
void GoalStaging::Release()
{
}