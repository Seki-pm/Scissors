#pragma once
#include "Engine/GameObject.h"
#include "Engine/SceneManager.h"
#include "Engine/Image.h"
#include "Engine/Input.h"
#include "Global.h"
#include "Scissors.h"
#include "StageSelectScene.h"

//�Q�[���I�[�o�[���Ǘ�����N���X
class GameOver : public GameObject
{
    //���[�h�p�ϐ�
    enum Load
    {
        LOAD_MIN = 0,
        GameOverBackImage_,    //GameOver�̔w�i(�s����)
        BackMenuImage_,        //�X�e�[�W�I���V�[���ɖ߂�{�^��
        RetryImage_,           //���g���C�{�^��
        SelectFrameImage_,     //�I��p�t���[��
        LOAD_MAX
    };

    //enum������z��
    int LoadHandle_[LOAD_MAX];


    //�����o�ϐ�
    int select_;    //�I��
    int alpha_;     //�����x

    Transform Retry;     //���g���C�p
    Transform BackMenu;  //�X�e�[�W�I���V�[���ɖ߂�p

    //�萔
    const XMFLOAT3 RETRY_POS = XMFLOAT3(-0.3f, 0, 0);   //�u���g���C�v�ʒu
    const XMFLOAT3 BACKMENU_POS = XMFLOAT3(0.3f, 0, 0); //�u�X�e�[�W�I���ɖ߂�v�ʒu

public:
    Scissors* pScissors_;

    //�R���X�g���N�^
    GameOver(GameObject* parent);

    //�f�X�g���N�^
    ~GameOver();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

    //������SET&GET
    void SetSelect(int select);
    int GetSelect() { return select_; }
};

