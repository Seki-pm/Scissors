#pragma once
#include "Engine/GameObject.h"
#include "Engine/SceneManager.h"
#include "Engine/Image.h"
#include "Engine/Input.h"
#include "StageSelectScene.h"
#include "Global.h"
#include "Scissors.h"

//�Q�[���I�[�o�[���Ǘ�����N���X
class GameOver : public GameObject
{
    int GameOverBackImage_;    //GameOver�̔w�i(�s����)
    int BackMenuImage_;     //�X�e�[�W�I���V�[���ɖ߂�{�^��
    int RetryImage_;        //���g���C�{�^��
    int SelectFrameImage_;  //�I��p�t���[��

    //�����o�ϐ�
    int select_;    //�I��
    int alpha_;     //�����x

    Transform Retry;     //���g���C�p
    Transform BackMenu;  //�X�e�[�W�I���V�[���ɖ߂�p

    //�萔
    const XMFLOAT3 RETRY_POS;
    const XMFLOAT3 BACKMENU_POS;

public:
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

