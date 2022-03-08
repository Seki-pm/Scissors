#pragma once
#include "Engine/GameObject.h"
#include "Engine/SceneManager.h"
#include "Engine/Image.h"
#include "Engine/Input.h"
#include "Global.h"
#include "Scissors.h"

//�Q�[���I�[�o�[���Ǘ�����N���X
class GameOver : public GameObject
{
    int GameOverBackImage_;    //GameOver�̔w�i(�s����)
    int BackMenuImage_;     //�X�e�[�W�I���V�[���ɖ߂�{�^��
    int RetryImage_;        //���g���C�{�^��
    int SelectFrameImage_;

    Scissors* pScissors;

    //�����o�ϐ�
    int select_;    //�I��
    int alpha_;

    Transform Retry;     //���g���C�p
    Transform BackMenu;  //�X�e�[�W�I���V�[���ɖ߂�p

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

    //���j���[�V�[���ɖ߂邩�ǂ���
    void SetSelect(int select);
};

