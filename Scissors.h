#pragma once
#include "Engine/GameObject.h"
#include "Engine/Input.h"
#include "Engine/Camera.h"
#include "Engine/Fbx.h"
#include "Engine/SphereCollider.h"
#include "Blade.h"
#include "Global.h"
#include "HP.h"
#include <vector>


//�n�T�~���Ǘ�����N���X
class Scissors : public GameObject
{
    //�u���[�h���Q��
    Blade* pBlade_L , *pBlade_R;

    vector<XMFLOAT3> vec_;

    //float deltaY;   //Y�����̈ړ���
    XMFLOAT3 move_;         //�ړ�
    XMFLOAT3 jumpDirection_; //�W�����v�����i�h�����Ă�n�ʂ̖@���j
    XMFLOAT3 nowPivotPoint_; //���݂̎h�����Ă���ꏊ

    float AnglePass_;  //�p�x�𑗂�

    bool Calc; //�v�Z�̃t���O

    float GLAVITY;

    ///////////////private�֐�//////////////////////////////////////
    //�J��
    void OpenClose();

    //��]
    void Rotation();

    //���E�ړ�
    void Move();

    //�W�����v�Ɨ���
    void JumpAndFall();

    ////////////////////////////////////////////////////////////////////


public:
    //�R���X�g���N�^
    Scissors(GameObject* parent);

    //�f�X�g���N�^
    ~Scissors();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

    void SetJumpDirection(XMFLOAT3 jumpDirection) { jumpDirection_ = jumpDirection; }

    //����
    void Reflection();

    void SetPosition();

    //��]���x
    void RotateMax();

    void Restart();
};