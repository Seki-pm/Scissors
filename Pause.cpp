#include "Pause.h"
#include "Engine/SceneManager.h"
#include "Engine/Image.h"
#include "Engine/Input.h"
#include "Global.h"

//�R���X�g���N�^
Pause::Pause(GameObject* parent)
    :GameObject(parent, "Pause"),
    PauseBackImage_(-1), ContinueImage_(-1),
    BackMenuImage_(-1), SelectFrameImage_(-1),
    select_(0), alpha_(150)
{
    Continue.position_ = XMFLOAT3(-0.3f, 0, 0);
    BackMenu.position_ = XMFLOAT3(0.3f, 0, 0);
}

//�f�X�g���N�^
Pause::~Pause()
{
}

//������
void Pause::Initialize()
{
    //�摜�f�[�^�̃��[�h
    //�s�����w�i
    PauseBackImage_ = Image::Load("Image/InGameMenu/BlackBack.png");
    assert(PauseBackImage_ >= 0);

    //������
    ContinueImage_ = Image::Load("Image/InGameMenu/Continue.png");
    assert(ContinueImage_ >= 0);

    //�X�e�[�W�I���ɖ߂�
    BackMenuImage_ = Image::Load("Image/InGameMenu/BackButton.png");
    assert(BackMenuImage_ >= 0);

    //�Z���N�g�t���[��
    SelectFrameImage_ = Image::Load("Image/InGameMenu/SelectFrame.png");
    assert(SelectFrameImage_ >= 0);

}

//�X�V
void Pause::Update()
{

    //�v���C�V�[���ɖ߂邪�I������Ă���Ƃ�
    if (Global::Pause && select_ == 0)
    {
        if (Input::IsKeyDown(DIK_SPACE))
        {
            KillMe();
            Global::Pause = false;
        }
    }
}

//�`��
void Pause::Draw()
{

    //�w�i
    Image::SetAlpha(PauseBackImage_, alpha_);
    Image::SetTransform(PauseBackImage_, transform_);
    Image::Draw(PauseBackImage_);

    Image::SetTransform(ContinueImage_, Continue);
    Image::Draw(ContinueImage_);

    Image::SetTransform(BackMenuImage_, BackMenu);
    Image::Draw(BackMenuImage_);





    //�v���C�V�[���ɖ߂邪�I�����ꂢ��Ƃ�
    if (select_ == 0)
    {
        Image::SetTransform(SelectFrameImage_, Continue);

        if (Input::IsKeyDown(DIK_SPACE))
        {
            KillMe();
        }
    }
    //���j���[�V�[���ɖ߂邪�I������Ă���Ƃ�
    else if (select_ == 1)
    {
        Image::SetTransform(SelectFrameImage_, BackMenu);
    }

    Image::Draw(SelectFrameImage_);
}

//�J��
void Pause::Release()
{
    PauseBackImage_ = -1;
    ContinueImage_ = -1;
    BackMenuImage_ = -1;

}
