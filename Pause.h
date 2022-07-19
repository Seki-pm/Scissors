#pragma once
#include "Engine/GameObject.h"
#include "Engine/SceneManager.h"
#include "Engine/Image.h"
#include "Engine/Input.h"
#include "Global.h"

//�ꎞ��~���Ǘ�����N���X
class Pause : public GameObject
{

    //���[�h�p�ϐ�
    enum Load
    {
        LOAD_MIN = 0,
        PauseBackImage_,    //pause�̔w�i
        ContinueImage_,     //�v���C�V�[���ɖ߂�{�^��
        BackMenuImage_,     //���j���[�V�[���ɖ߂�{�^��
        SelectFrameImage_,  //�I��p�t���[��
        LOAD_MAX
    };

    //enum������z��
    int LoadHandle_[LOAD_MAX];


    //�����o�ϐ�
    int select_;    //�I��
    int alpha_;     //�����x

    Transform Continue;     //�v���C�V�[���ɖ߂�p
    Transform BackMenu;     //���j���[�V�[���ɖ߂�p

    //�萔
    const XMFLOAT3 CONTINUE_POS = XMFLOAT3(-0.3f, 0, 0); //�u�v���C�V�[���ɖ߂�v�摜�ʒu
    const XMFLOAT3 BACKMENU_POS = XMFLOAT3(0.3f, 0, 0);  //�u���j���[�V�[���ɖ߂�v�摜�ʒu
public:
    //�R���X�g���N�^
    Pause(GameObject* parent);

    //�f�X�g���N�^
    ~Pause();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

    //���j���[�V�[���ɖ߂邩�ǂ���
    void SetSelect(int select) { select_ = select; }
    int GetSelect() { return select_; }
};


