#include "GameOver.h"

//�R���X�g���N�^
GameOver::GameOver(GameObject* parent)
    :GameObject(parent, "GameOver"),
     alpha_(150), select_(0)
{
    //Load ������
    for (int i = LOAD_MIN + 1; i < LOAD_MAX; i++)
    {
        LoadHandle_[i] = INITIAL_ERROR_VALUE;
    }

}

//�f�X�g���N�^
GameOver::~GameOver()
{
}

//������
void GameOver::Initialize()
{
    //�\���ʒu�ݒ�
    Retry.position_ = RETRY_POS;
    BackMenu.position_ = BACKMENU_POS;

    //--------------------  �摜�f�[�^�̃��[�h  ---------------------
    {
        //�Q�[���I�[�o�[
        LoadHandle_[GameOverBackImage_] = Image::Load("Image/InGameMenu/BlackBack.png");
        assert(LoadHandle_[GameOverBackImage_] >= 0);

        //���g���C
        LoadHandle_[RetryImage_] = Image::Load("Image/InGameMenu/Retry.png");
        assert(LoadHandle_[RetryImage_] >= 0);

        //�Z���N�g�t���[��
        LoadHandle_[SelectFrameImage_] = Image::Load("Image/InGameMenu/SelectFrame.png");
        assert(LoadHandle_[SelectFrameImage_] >= 0);

        //�X�e�[�W�I���ɖ߂�
        LoadHandle_[BackMenuImage_] = Image::Load("Image/InGameMenu/BackButton.png");
        assert(LoadHandle_[BackMenuImage_] >= 0);
    }
    //---------------------------------------------------------------
}

//�X�V
void GameOver::Update()
{
}

//�`��
void GameOver::Draw()
{
    pScissors_ = (Scissors*)FindObject("Scissors");

    //�w�i�`��
    Image::SetAlpha(LoadHandle_[GameOverBackImage_], alpha_);
    Image::SetTransform(LoadHandle_[GameOverBackImage_], transform_);
    Image::Draw(LoadHandle_[GameOverBackImage_]);

    Image::SetTransform(LoadHandle_[RetryImage_], Retry);
    Image::Draw(LoadHandle_[RetryImage_]);

    Image::SetTransform(LoadHandle_[BackMenuImage_], BackMenu);
    Image::Draw(LoadHandle_[BackMenuImage_]);


    //���g���C���I������Ă��鎞
    if (select_ == 0)
    {
        Image::SetTransform(LoadHandle_[SelectFrameImage_], Retry);
    }
    //�X�e�[�W�I�����I������Ă��鎞
    else if(select_ == 1)
    {
        Image::SetTransform(LoadHandle_[SelectFrameImage_], BackMenu);
    }

    Image::Draw(LoadHandle_[SelectFrameImage_]);
}

//�J��
void GameOver::Release()
{
    //Load �J��
    for (int i = LOAD_MIN + 1; i < LOAD_MAX; i++)
    {
        LoadHandle_[i] = INITIAL_ERROR_VALUE;
    }
}

//�Z�b�g
void GameOver::SetSelect(int select)
{
    select_ = select;
}

