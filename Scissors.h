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
#include "GameOver.h"
#include "Stage.h"
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

    bool Calc; //�v�Z�̃t���O
    bool FallFlg; //�����t���O
    bool SoundFlg; //���t���O



    //�e���ꂽ���p
    int Key = 0;
    float TransPos_Y;
    float powerY;
    float powerX;
    bool IsRepel;

    //SE
    int Land_Glass;
    int Land_Wood;
    int Land_Gravel;
    int Land_Stone;

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

    //�ʒu���Z�b�g����
    void SetPosition();

    //��]���x
    void RotateMax();

    //�n�߂ɖ߂�
    void Restart();

    //�e���ꂽ���̓���
    void RepelMove(float moveX);

    void InitSound();
    void Landing();
};