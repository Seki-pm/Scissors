#pragma once
#include "Engine/GameObject.h"


//�Q�[���̃T�E���h���Ǘ�����N���X
class GameSound : public GameObject
{




public:
    //�R���X�g���N�^
    GameSound(GameObject* parent);

    //�f�X�g���N�^
    ~GameSound();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

    void Landing();
};