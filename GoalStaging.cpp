#include "GoalStaging.h"
#include "StageSelectScene.h"

//�R���X�g���N�^
GoalStaging::GoalStaging(GameObject* parent)
    :GameObject(parent, "GoalStaging"), 
    timer_(false),StagingFlg(false), StringFlg(false),
    time_(0), size_(10)
{
    //Load ������
    for (int i = LOAD_MIN + 1; i < LOAD_MAX; i++)
    {
        LoadHandle_[i] = INITIAL_ERROR_VALUE;
    }
}

//�f�X�g���N�^
GoalStaging::~GoalStaging()
{
}

//������
void GoalStaging::Initialize()
{
    //------------------------  �f�[�^�̓ǂݍ���  ---------------------------------
    {
        //���f���f�[�^�̃��[�h
        LoadHandle_[BalloonModel_] = Model::Load("Model/InGameObject/Balloon.fbx");
        assert(LoadHandle_[BalloonModel_] >= 0);
        BalloonTrans.position_ = XMFLOAT3(game.GetCameraGoal().x, game.GetCameraGoal().y, 0.f);
        BalloonTrans.scale_ = BAL_ENT_SIZE;
        Model::SetTransform(LoadHandle_[BalloonModel_], BalloonTrans);

        //Enter
        LoadHandle_[EnterImage_] = Image::Load("Image/InGameMenu/Enter.png");
        assert(LoadHandle_[EnterImage_] >= 0);
        EnterTrans.position_ = ENTER_POS;
        EnterTrans.scale_ = BAL_ENT_SIZE;
        Image::SetTransform(LoadHandle_[EnterImage_], EnterTrans);

        //�Ó]
        LoadHandle_[BackImage_] = Image::Load("Image/InGameMenu/Clear_Black.png");
        assert(LoadHandle_[BackImage_] >= 0);
        auto BlackTrans = Transform();
        BlackTrans.scale_ = BACKIMAGE_SIZE;
        Image::SetTransform(LoadHandle_[BackImage_], BlackTrans);

        //���k�p
        LoadHandle_[CircleImage_] = Image::Load("Image/InGameMenu/Clear_Effect.png");
        assert(LoadHandle_[CircleImage_] >= 0);
        CircleTrans.scale_ = XMFLOAT3(size_, size_, size_);

        //�T�E���h
        LoadHandle_[GoalSound_] = Audio::Load("Sound/InStage/Staging.wav");
        assert(LoadHandle_[GoalSound_] >= 0);
    }
    //-----------------------------------------------------------------------------
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
    if (game.GetTransPos().x >= game.GetCameraGoal().x - 1.5f)
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
    Model::Draw(LoadHandle_[BalloonModel_]);

    //�S�[�����o
    if(StringFlg)
    {
        //�����\��
        Image::Draw(LoadHandle_[EnterImage_]);

        //Enter�L�[����������
        if (Input::IsKeyDown(DIK_RETURN))
        {
            ClearJudge(); //�N���A����

            Audio::Play(LoadHandle_[GoalSound_]);

            StringFlg = false;
            //�S�[�����o�X�^�[�g
            StagingFlg = true;
        }
    }

    //�Ó]����
    if (StagingFlg)
    {
        CircleTrans.scale_ = XMFLOAT3(size_, size_, size_);
        Image::SetTransform(LoadHandle_[CircleImage_], CircleTrans);

        //size_�̑傫���ŕ\���摜��ς���
        if (size_ > SIZE_MIN)
        {
            //�T�C�Y���k��������
            size_ -= SCALE_DOWN_VAL;
            Image::Draw(LoadHandle_[CircleImage_]);
        }
        else
        {
            Image::Draw(LoadHandle_[BackImage_]);
        }
    }

}

//�J��
void GoalStaging::Release()
{
    //Load �J��
    for (int i = LOAD_MIN + 1; i < LOAD_MAX; i++)
    {
        LoadHandle_[i] = INITIAL_ERROR_VALUE;
    }
}

//���ԊǗ�
void GoalStaging::Timer()
{
    time_++;

    //TIME�܂ŃJ�E���g
    if (time_ >= TIME)
    {
        timer_ = true;
        time_ = 0;
    }
}

//�N���A����
void GoalStaging::ClearJudge()
{
    //�R�C������肵�ăN���A��������t���O�𗧂Ă�
    switch (Game::SelectStage)
    {
    case STAGE_NUMBER_1:
        if (game.getState(Game::stage1.GetCoin)) game.setState(Game::stage1.Clear); break;
    case STAGE_NUMBER_2:
        if (game.getState(Game::stage2.GetCoin)) game.setState(Game::stage2.Clear); break;
    case STAGE_NUMBER_3:
        if (game.getState(Game::stage3.GetCoin)) game.setState(Game::stage3.Clear); break;
    }
}
