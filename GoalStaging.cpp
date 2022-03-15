#include "GoalStaging.h"


//�R���X�g���N�^
GoalStaging::GoalStaging(GameObject* parent)
    :GameObject(parent, "GoalStaging"), hModel_(-1), BackImage_(-1), EnterImage_(-1),
    CircleImage_(-1), size_(10), flg(false), Sflg(false),timer(0)
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
    BalloonTrans.position_ = XMFLOAT3(gl.GetCameraGoal(), 4.f, 0.f);
    BalloonTrans.scale_ = XMFLOAT3(0.8f, 0.8f, 0.8f);
    Model::SetTransform(hModel_, BalloonTrans);


    //�摜�f�[�^�̓ǂݍ���
    //�Ó]
    BackImage_ = Image::Load("Image/Clear_Black.png");
    assert(BackImage_ >= 0);
    auto BlackTrans = Transform();
    BlackTrans.scale_ = XMFLOAT3(1.4f, 1.4f, 1.4f);
    Image::SetTransform(BackImage_, BlackTrans);

    CircleImage_ = Image::Load("Image/Clear_Effect.png");
    assert(CircleImage_ >= 0);
    CircleTrans.scale_ = XMFLOAT3(size_,size_,size_);



    //Enter
    EnterImage_ = Image::Load("Image/Enter.png");
    assert(EnterImage_ >= 0);
    EnterTrans.position_ = XMFLOAT3(0.1f, 0.1f, 0);
    EnterTrans.scale_ = XMFLOAT3(0.8f, 0.8f, 0.8f);
    Image::SetTransform(EnterImage_, EnterTrans);

 


}

//�X�V
void GoalStaging::Update()
{

    if (Input::IsKeyDown(DIK_I))
    {
        Model::SetAnimFrame(hModel_, 1, 300, 1.0f);
    }


    if (gl.GetTransPos_X() >= gl.GetCameraGoal() - 1.5f)
    {
        //�����\��
        Sflg = true;
    }
    else
    {
        Sflg = false;
    }

    if (flg) Timer();
}

//�`��
void GoalStaging::Draw()
{
    Model::Draw(hModel_);

    //�S�[�����o
    if(Sflg)
    {
        //�����\��
        Image::Draw(EnterImage_);

        //Enter�L�[����������
        if (Input::IsKeyDown(DIK_RETURN))
        {
            Sflg = false;
            //�S�[�����o�X�^�[�g
            flg = true;
        }
    }

    //�Ó]����
    if (flg)
    {
        CircleTrans.scale_ = XMFLOAT3(size_, size_, size_);
        Image::SetTransform(CircleImage_, CircleTrans);

        if (size_ > 1.4f)
        {
            size_ -= 0.2f;
            Image::Draw(CircleImage_);
        }
        else
        {
            Image::Draw(BackImage_);
        }
    }

}

//�J��
void GoalStaging::Release()
{
    EnterImage_ = -1;
}

//���ԊǗ�
void GoalStaging::Timer()
{
    timer++;

    if (timer >= 60)
    {
        Global::Timer = true;
        timer = 0;
    }
}
