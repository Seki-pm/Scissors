#include "GoalStaging.h"


//�R���X�g���N�^
GoalStaging::GoalStaging(GameObject* parent)
    :GameObject(parent, "GoalStaging"), hModel_(-1), BackImage_(-1), EnterImage_(-1),
    CircleImage_(-1), size_(10), flg(false), Sflg(false), Aflg(false)
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

    EnterImage_ = Image::Load("Image/HP.png");
    assert(EnterImage_ >= 0);
    //EnterTrans.scale_ = XMFLOAT3(0.5f, 0.5f, 0.5f);
}

//�X�V
void GoalStaging::Update()
{
    float X = gl.GetTransPos_X();

    EnterTrans.position_ = XMFLOAT3( X, gl.GetTransPos_Y() + 0.5f, 0);


    if (Input::IsKeyDown(DIK_I))
    {
        Model::SetAnimFrame(hModel_, 1, 300, 1.0f);
    }

    if (Input::IsKeyDown(DIK_P))
    {
        flg = true;

    }


    if (gl.GetTransPos_X() >= gl.GetCameraGoal() - 1)
    {
        //�\��flg = true
        Sflg = true;
    }
    else
    {
        Sflg = false;
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

    Image::SetTransform(EnterImage_, EnterTrans);
    Image::Draw(EnterImage_);
    if(Sflg)
    {
        //�����\��


        //Enter�L�[����������
        if (Input::IsKeyDown(DIK_RETURN))
        {
            //�S�[�����o�X�^�[�g
            Aflg = true;
        }
    }


    Model::Draw(hModel_);
}

//�J��
void GoalStaging::Release()
{
    EnterImage_ = -1;
}