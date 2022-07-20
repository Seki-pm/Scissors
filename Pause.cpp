#include "Pause.h"

//�R���X�g���N�^
Pause::Pause(GameObject* parent)
    :GameObject(parent, "Pause"),
     select_(0), alpha_(150)
{
    //Load ������
    for (int i = LOAD_MIN + 1; i < LOAD_MAX; i++)
    {
        LoadHandle_[i] = INITIAL_ERROR_VALUE;
    }
}

//�f�X�g���N�^
Pause::~Pause()
{
}

//������
void Pause::Initialize()
{
    //�\���ʒu�̐ݒ�
    Continue.position_ = CONTINUE_POS;
    BackMenu.position_ = BACKMENU_POS;

    //-------------------- �摜�f�[�^�̃��[�h --------------------------
    {
        //�s�����w�i
        LoadHandle_[PauseBackImage_] = Image::Load("Image/InGameMenu/BlackBack.png");
        assert(LoadHandle_[PauseBackImage_] >= 0);

        //������
        LoadHandle_[ContinueImage_] = Image::Load("Image/InGameMenu/Continue.png");
        assert(LoadHandle_[ContinueImage_] >= 0);

        //�X�e�[�W�I���ɖ߂�
        LoadHandle_[BackMenuImage_] = Image::Load("Image/InGameMenu/BackButton.png");
        assert(LoadHandle_[BackMenuImage_] >= 0);

        //�Z���N�g�t���[��
        LoadHandle_[SelectFrameImage_] = Image::Load("Image/InGameMenu/SelectFrame.png");
        assert(LoadHandle_[SelectFrameImage_] >= 0);
    }
    //------------------------------------------------------------------
}

//�X�V
void Pause::Update()
{
}

//�`��
void Pause::Draw()
{

    //�w�i
    Image::SetAlpha(LoadHandle_[PauseBackImage_], alpha_);
    Image::SetTransform(LoadHandle_[PauseBackImage_], transform_);
    Image::Draw(LoadHandle_[PauseBackImage_]);

    Image::SetTransform(LoadHandle_[ContinueImage_], Continue);
    Image::Draw(LoadHandle_[ContinueImage_]);

    Image::SetTransform(LoadHandle_[BackMenuImage_], BackMenu);
    Image::Draw(LoadHandle_[BackMenuImage_]);




    //�v���C�V�[���ɖ߂邪�I�����ꂢ��Ƃ�
    if (select_ == 0)
    {
        Image::SetTransform(LoadHandle_[SelectFrameImage_], Continue);

        if (Input::IsKeyDown(DIK_SPACE))
        {
            KillMe();
        }
    }
    //���j���[�V�[���ɖ߂邪�I������Ă���Ƃ�
    else if (select_ == 1)
    {
        Image::SetTransform(LoadHandle_[SelectFrameImage_], BackMenu);
    }

    Image::Draw(LoadHandle_[SelectFrameImage_]);
}

//�J��
void Pause::Release()
{
    //Load �J��
    for (int i = LOAD_MIN + 1; i < LOAD_MAX; i++)
    {
        LoadHandle_[i] = INITIAL_ERROR_VALUE;
    }
}
