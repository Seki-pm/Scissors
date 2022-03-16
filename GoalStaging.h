#pragma once
#include "Engine/GameObject.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/Image.h"
#include "Global.h"

//�S�[�����o���Ǘ�����N���X
class GoalStaging : public GameObject
{
    Global gl; //global���g��

    int BalloonModel_;    //���f���ԍ�

    //�摜���[�h�p
    int BackImage_;
    int CircleImage_;
    int EnterImage_;

    //�eTransform
    Transform CircleTrans;
    Transform EnterTrans;
    Transform BalloonTrans;

    //�T�C�Y
    float size_;

    //�t���O
    bool StagingFlg;
    bool StringFlg;

    //���ԊǗ�
    int timer;

public:
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