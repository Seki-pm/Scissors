#include "GameOver.h"

//�R���X�g���N�^
GameOver::GameOver(GameObject* parent)
    :GameObject(parent, "GameOver"),
    GameOverBackImage_(-1), BackMenuImage_(-1),
    RetryImage_(-1),SelectFrameImage_(-1),
    alpha_(150), select_(0),
    RETRY_POS(XMFLOAT3(-0.3f, 0, 0)), BACKMENU_POS(XMFLOAT3(0.3f, 0, 0))
{
    Retry.position_ = RETRY_POS;
    BackMenu.position_ = BACKMENU_POS;
}

//�f�X�g���N�^
GameOver::~GameOver()
{
}

//������
void GameOver::Initialize()
{
    //�摜�f�[�^�̃��[�h
    //�Q�[���I�[�o�[
    GameOverBackImage_ = Image::Load("Image/InGameMenu/BlackBack.png");
    assert(GameOverBackImage_ >= 0);

    //���g���C
    RetryImage_ = Image::Load("Image/InGameMenu/Retry.png");
    assert(RetryImage_ >= 0);

    //�Z���N�g�t���[��
    SelectFrameImage_ = Image::Load("Image/InGameMenu/SelectFrame.png");
    assert(SelectFrameImage_ >= 0);

    //�X�e�[�W�I���ɖ߂�
    BackMenuImage_ = Image::Load("Image/InGameMenu/BackButton.png");
    assert(BackMenuImage_ >= 0);

}

//�X�V
void GameOver::Update()
{
}

//�`��
void GameOver::Draw()
{
    Scissors* pScissors_ = (Scissors*)FindObject("Scissors");

    //�w�i�`��
    Image::SetAlpha(GameOverBackImage_, alpha_);
    Image::SetTransform(GameOverBackImage_, transform_);
    Image::Draw(GameOverBackImage_);

    Image::SetTransform(RetryImage_, Retry);
    Image::Draw(RetryImage_);

    Image::SetTransform(BackMenuImage_, BackMenu);
    Image::Draw(BackMenuImage_);


    //���g���C���I������Ă��鎞
    if (select_ == 0)
    {
        Image::SetTransform(SelectFrameImage_, Retry);
        
        if (Input::IsKeyDown(DIK_SPACE))
        {
            KillMe();
            pScissors_->Restart();
        }
    }
    //�X�e�[�W�I�����I������Ă��鎞
    else if(select_ == 1)
    {
        Image::SetTransform(SelectFrameImage_, BackMenu);
    }

    Image::Draw(SelectFrameImage_);
}

//�J��
void GameOver::Release()
{
    GameOverBackImage_ = -1;
    BackMenuImage_     = -1;
    RetryImage_        = -1;
    SelectFrameImage_  = -1;
}

//�Z�b�g
void GameOver::SetSelect(int select)
{
    select_ = select;
}

