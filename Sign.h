#pragma once
#include "Engine/GameObject.h"
#include "Engine/Model.h"
#include "Engine/Image.h"
#include "Global.h"



//��������I�u�W�F�N�g���Ǘ�����N���X
class Sign : public GameObject
{
    enum Tips {
        Tips_1 = 1,
        Tips_2,
        Tips_3,
        Tips_4,
        Tips_5,
        Tips_6,
        Tips_MAX
    };

    //���f��������ϐ�
    int TipsModel_[Tips_MAX];

    //�摜������ϐ�
    int Tutorial_;
    int Tutorial2_;

    float size_;

    Global gl;

    Transform SignTrans;
    Transform SignTrans2;
    Transform SignTrans5;

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