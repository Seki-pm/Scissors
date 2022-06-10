#include "GoalStaging.h"


//�R���X�g���N�^
GoalStaging::GoalStaging(GameObject* parent)
    :GameObject(parent, "GoalStaging"), 
    BalloonModel_(-1), BackImage_(-1), EnterImage_(-1),
    CircleImage_(-1), SoundHandle_(-1), size_(10), timer(0),
    StagingFlg(false), StringFlg(false)
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
    BalloonModel_ = Model::Load("Model/InGameObject/Balloon.fbx");
    assert(BalloonModel_ >= 0);
    BalloonTrans.position_ = XMFLOAT3(gl.GetCameraGoalX(), gl.GetCameraGoalY(), 0.f);
    BalloonTrans.scale_ = XMFLOAT3(0.8f, 0.8f, 0.8f);
    Model::SetTransform(BalloonModel_, BalloonTrans);

    //Enter
    EnterImage_ = Image::Load("Image/InGameMenu/Enter.png");
    assert(EnterImage_ >= 0);
    EnterTrans.position_ = XMFLOAT3(0.1f, 0.1f, 0);
    EnterTrans.scale_ = XMFLOAT3(0.8f, 0.8f, 0.8f);
    Image::SetTransform(EnterImage_, EnterTrans);

    //�Ó]
    BackImage_ = Image::Load("Image/InGameMenu/Clear_Black.png");
    assert(BackImage_ >= 0);
    auto BlackTrans = Transform();
    BlackTrans.scale_ = XMFLOAT3(1.4f, 1.4f, 1.4f);
    Image::SetTransform(BackImage_, BlackTrans);

    //���k�p
    CircleImage_ = Image::Load("Image/InGameMenu/Clear_Effect.png");
    assert(CircleImage_ >= 0);
    CircleTrans.scale_ = XMFLOAT3(size_,size_,size_);

    //�T�E���h
    SoundHandle_ = Audio::Load("Sound/InStage/Staging.wav");
    assert(SoundHandle_ >= 0);
}

//�X�V
void GoalStaging::Update()
{
    //���D�̃A�j���[�V�����J�n
    //if (Input::IsKeyDown(DIK_I))
    //{
    //    Model::SetAnimFrame(BalloonModel_, 1, 300, 1.0f);
    //}

    //�S�[���ɂ����當���\��
    if (gl.GetTransPos_X() >= gl.GetCameraGoalX() - 1.5f)
    {
        //�����\��
        StringFlg = true;
    }
    else
    {
        StringFlg = false;
    }

    //Enter�������ꂽ��^�C�}�[�J�n
    if (StagingFlg) Timer();
}

//�`��
void GoalStaging::Draw()
{
    Model::Draw(BalloonModel_);

    //�S�[�����o
    if(StringFlg)
    {
        //�����\��
        Image::Draw(EnterImage_);

        //Enter�L�[����������
        if (Input::IsKeyDown(DIK_RETURN))
        {
            Audio::Play(SoundHandle_);

            StringFlg = false;
            //�S�[�����o�X�^�[�g
            StagingFlg = true;
        }
    }

    //�Ó]����
    if (StagingFlg)
    {
        CircleTrans.scale_ = XMFLOAT3(size_, size_, size_);
        Image::SetTransform(CircleImage_, CircleTrans);

        if (size_ > 1.4f)
        {
            size_ -= 0.15f;
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
    BalloonModel_ = -1;
    SoundHandle_ = -1;
    BackImage_ = -1;
    CircleImage_ = -1;
}

//���ԊǗ�
void GoalStaging::Timer()
{
    timer++;

    if (timer >= 90)
    {
        Global::Timer = true;
        timer = 0;
    }
}
