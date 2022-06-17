#pragma once
#include "Engine/GameObject.h"
#include "Engine/Model.h"
#include "Engine/Image.h"
#include "Global.h"

//��������I�u�W�F�N�g���Ǘ�����N���X
class Sign : public GameObject
{
    //���f��������ϐ�
    int TipsHandle_;
    int TipsHandle2_;
    int TipsHandle3_;
    int TipsHandle4_;
    int TipsHandle5_;

    //�摜������ϐ�
    int Tutorial_;
    int Tutorial2_;

    float size_;

    Global gl;

    Transform SignTrans;

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