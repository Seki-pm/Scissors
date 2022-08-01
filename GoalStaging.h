#pragma once
#include "Engine/GameObject.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/Image.h"
#include "Engine/Audio.h"
#include "Game.h"

//�S�[�����o���Ǘ�����N���X
class GoalStaging : public GameObject
{
    Game game; //global���g��

    //���[�h�p�ϐ�
    enum Load
    {
        LOAD_MIN = 0,
        BackImage_,    //�w�i�摜
        CircleImage_,  //���k�p�摜
        EnterImage_,   //Enter�摜
        BalloonModel_, //���f���ԍ�
        GoalSound_,    //�T�E���h�p
        LOAD_MAX
    };

    //enum������z��
    int LoadHandle_[LOAD_MAX];

    //�eTransform
    Transform CircleTrans;
    Transform EnterTrans;
    Transform BalloonTrans;

    //�T�C�Y(�Ó]�����p)
    float size_;

    //�t���O
    bool StagingFlg;
    bool StringFlg;

    //���ԊǗ�
    int time_;

    //�萔
    const int TIME = 90;  //�V�[���J�ڂ܂ł̎���
    const float SIZE_MIN = 1.4f; //�k���ŏ��l
    const float SCALE_DOWN_VAL = 0.15f; //�T�C�Y�k���̒l

    const XMFLOAT3 BAL_ENT_SIZE = XMFLOAT3(0.8f, 0.8f, 0.8f);   //���D�AEnter�̃T�C�Y
    const XMFLOAT3 ENTER_POS = XMFLOAT3(0.1f, 0.1f, 0.f);       //Enter�̈ʒu
    const XMFLOAT3 BACKIMAGE_SIZE = XMFLOAT3(1.4f, 1.4f, 1.4f); //�w�i�T�C�Y

public:
    bool timer_; //�^�C�}�[�t���O

    //�R���X�g���N�^
    GoalStaging(GameObject* parent);

    //�f�X�g���N�^
    ~GoalStaging();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

    //�^�C�}�[
    void Timer();

    //�N���A����
    void ClearJudge();
};