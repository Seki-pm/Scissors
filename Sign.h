#pragma once
#include "Engine/GameObject.h"
#include "Engine/Model.h"

//��������I�u�W�F�N�g���Ǘ�����N���X
class Sign : public GameObject
{
    int TipsHandle_;
    int TipsHandle2_;
    int TipsHandle3_;
    int TipsHandle4_;
    int TipsHandle5_;

    float size_;

public:
    //�R���X�g���N�^
    Sign(GameObject* parent);

    //�f�X�g���N�^
    ~Sign();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;
};