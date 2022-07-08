#pragma once
#include "Engine/GameObject.h"
#include "Engine/SphereCollider.h"
#include "Engine/Input.h"
#include "Engine/Camera.h"
#include "Engine/Fbx.h"
#include "Engine/Audio.h"
#include "Blade.h"
#include "Global.h"
#include "HP.h"
#include "Stage.h"
#include "StageSelectScene.h"
#include <vector>

//�n�T�~���Ǘ�����N���X
class Scissors : public GameObject
{
    //�u���[�h���Q��
    Blade* pBlade_L , *pBlade_R;
    Stage* pStage_;

    XMFLOAT3 move_;         //�ړ�
    XMFLOAT3 jumpDirection_; //�W�����v�����i�h�����Ă�n�ʂ̖@���j
    XMFLOAT3 nowPivotPoint_; //���݂̎h�����Ă���ꏊ

    float AnglePass_;  //�p�x�𑗂�
    float GLAVITY; //�d��

    bool CalcFlg; //�v�Z�̃t���O
    bool FallFlg; //�����t���O
    bool SoundFlg; //���t���O


    float JumpPower;

    //�e���ꂽ���p
    int Key;
    float TransPos_Y;
    float powerY;
    float powerX;
    bool IsRepel;

    //���񂾎��p
    bool IsSink;
    float MoveY;
    int Timer_;
    int CountDown;
    int CountPass;


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
    bool IsJump;
    int CurrentHP;


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

    //�n�ʂ̖@�����Z�b�g
    void SetJumpDirection(XMFLOAT3 jumpDirection) { jumpDirection_ = jumpDirection; }
    XMFLOAT3 GetJumpDirection() { return jumpDirection_; }

    //����
    void Reflection();

    //�ʒu���Z�b�g����
    void SetPosition()
    {
        Global gl;
        gl.SetTransPos(transform_.position_);
    }

    //��]���x
    void RotateMax();

    //�n�߂ɖ߂�
    void Restart();

    //�e���ꂽ���̓���
    void RepelMove();

    //���񂾎��̓���
    void SinkMove();

    //������炷
    void Landing();

    //�J�E���g�_�E���𑗂�
    void SetCountDown(int countdown) { CountPass = countdown; }
    int GetCountDown() { return CountPass; };
};