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
    float powerY;
    float powerX;
    bool IsRepel;

    //���񂾎��p
    bool IsSink;
    float MoveY;
    int Timer_;
    int CountDown;
    int CountPass;

    //�萔
    const int FALL_MAX = -8;        //�������E
    
    const float JUMP_POWER = 0.2f;  //�W�����v��
    const float NORMAL_JUMP_POWER = 0.1f; //�ʏ�̃W�����v��
    const float SINK_JUMP_POWER = 0.001f; //���񂾎��̃W�����v��

    const int SINK_TIMER = 360;           //���ރ^�C�}�[
    const int SINK_TIMER_MIN = 60;       //�^�C�}�[�̍ŏ��l

    const XMFLOAT3 INIT_POSITION = XMFLOAT3(0, 1, 0); //�����ʒu
    const XMFLOAT3 INIT_ROTATE = XMFLOAT3(0, 0, 0);   //������]�p�x
    
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
    float JumpStart;
    float JumpEnd;


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