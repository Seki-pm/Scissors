#include "GoalStaging.h"

#define Bal_Ent_Size XMFLOAT3(0.8f,0.8f,0.8f);
#define Enter_Pos XMFLOAT3(0.1f,0.1f,0.f);
#define BackImage_Size XMFLOAT3(1.4f,1.4f,1.4f);

const int TIME = 90;
const float Size_Min = 1.4f;
const float Scale_Down_Val = 0.15f;

//�R���X�g���N�^
GoalStaging::GoalStaging(GameObject* parent)
    :GameObject(parent, "GoalStaging"), 
    BalloonModel_(-1), BackImage_(-1), EnterImage_(-1),
    CircleImage_(-1),  GoalSound_(-1), time_(0),size_(10),
    timer_(false),StagingFlg(false), StringFlg(false)
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
    BalloonModel_ = Model::Load("Model/InGameObject/Balloon.fbx");
    assert(BalloonModel_ >= 0);
    BalloonTrans.position_ = XMFLOAT3(gl.GetCameraGoal().x, gl.GetCameraGoal().y, 0.f);
    BalloonTrans.scale_ = Bal_Ent_Size;
    Model::SetTransform(BalloonModel_, BalloonTrans);

    //Enter
    EnterImage_ = Image::Load("Image/InGameMenu/Enter.png");
    assert(EnterImage_ >= 0);
    EnterTrans.position_ = Enter_Pos;
    EnterTrans.scale_ = Bal_Ent_Size;
    Image::SetTransform(EnterImage_, EnterTrans);

    //�Ó]
    BackImage_ = Image::Load("Image/InGameMenu/Clear_Black.png");
    assert(BackImage_ >= 0);
    auto BlackTrans = Transform();
    BlackTrans.scale_ = BackImage_Size;
    Image::SetTransform(BackImage_, BlackTrans);

    //���k�p
    CircleImage_ = Image::Load("Image/InGameMenu/Clear_Effect.png");
    assert(CircleImage_ >= 0);
    CircleTrans.scale_ = XMFLOAT3(size_, size_, size_);

    //�T�E���h
    GoalSound_ = Audio::Load("Sound/InStage/Staging.wav");
    assert(GoalSound_ >= 0);
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
    if (gl.GetTransPos().x >= gl.GetCameraGoal().x - 1.5f)
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
            Audio::Play(GoalSound_);

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

        if (size_ > Size_Min)
        {
            size_ -= Scale_Down_Val;
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
    BalloonModel_ = -1;
    CircleImage_ = -1;
    EnterImage_ = -1;
    GoalSound_ = -1;
    BackImage_ = -1;
}

//���ԊǗ�
void GoalStaging::Timer()
{
    time_++;

    if (time_ >= TIME)
    {
        timer_ = true;
        time_ = 0;
    }
}
