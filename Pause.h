#pragma once
#include "Engine/GameObject.h"

//�ꎞ��~���Ǘ�����N���X
class Pause : public GameObject
{
    int PauseBackImage_;    //pause�̔w�i
    int ContinueImage_;     //�v���C�V�[���ɖ߂�{�^��
    int BackMenuImage_;     //���j���[�V�[���ɖ߂�{�^��
    int SelectFrameImage_;  //�I��p�t���[��

    //�����o�ϐ�
    int select_;    //�I��
    int alpha_;     //�����x

    Transform Continue;     //�v���C�V�[���ɖ߂�p
    Transform BackMenu;     //���j���[�V�[���ɖ߂�p

    const XMFLOAT3 CONTINUE_POS;
    const XMFLOAT3 BACKMENU_POS; 

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


