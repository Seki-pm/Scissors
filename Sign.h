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

    //�Ŕ�enum������ϐ�
    int TipsModel_[Tips_MAX];

    //�摜������ϐ�
    int Tutorial_;   //�`���[�g���A��
    int Tutorial2_;

    Global gl;

    //�eTransform
    Transform SignTrans;
    Transform SignTrans2;
    Transform SignTrans5;

    //�萔
    //�Ŕ̈ʒu
    const XMFLOAT3 SIGN1_POS = XMFLOAT3(2, 0, 0);
    const XMFLOAT3 SIGN2_POS = XMFLOAT3(8, 0, 0);
    const XMFLOAT3 SIGN3_POS = XMFLOAT3(11, 0, 0);
    const XMFLOAT3 SIGN4_POS = XMFLOAT3(14, 0, 0);
    const XMFLOAT3 SIGN5_POS = XMFLOAT3(28, 0, 0);
    const XMFLOAT3 SIGN6_POS = XMFLOAT3(31, 0, 0);

    const XMFLOAT3 SIGN_SIZE = XMFLOAT3(1.7f,1.7f,1.7f); //�Ŕ̃T�C�Y

    const XMFLOAT3 TUTORIAL_POS = XMFLOAT3(0,   0.65f, 0);   //�`���[�g���A���̈ʒu
    const XMFLOAT3 TUTORIAL_SCA = XMFLOAT3(0.5f, 0.5f, 0.5f); //�`���[�g���A���̃T�C�Y
    
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