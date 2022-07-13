#pragma once
#include "Engine/GameObject.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/Image.h"
#include "Engine/Audio.h"
#include "Global.h"

//�S�[�����o���Ǘ�����N���X
class GoalStaging : public GameObject
{
    Global gl; //global���g��

    int BalloonModel_;    //���f���ԍ�
    int GoalSound_;  //�T�E���h�p

    //�摜���[�h�p
    int BackImage_;
    int CircleImage_;
    int EnterImage_;

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
    const XMFLOAT3 BAL_ENT_SIZE;   //���D&ENTER �̃T�C�Y
    const XMFLOAT3 ENTER_POS;      //ENTER�ʒu
    const XMFLOAT3 BACKIMAGE_SIZE; //�w�i�T�C�Y

    const int TIME;          //����
    const float SIZE_MIN;    //�ŏ��T�C�Y
    const float SCALE_DOWN_VAL; //�k���l

public:
    bool timer_;

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
};