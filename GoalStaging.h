#pragma once
#include "Engine/GameObject.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/Image.h"
#include "Global.h"

//�S�[�����o���Ǘ�����N���X
class GoalStaging : public GameObject
{
    Global gl;

    int hModel_;    //���f���ԍ�

    int BackImage_;
    int CircleImage_;

    int EnterImage_;

    Transform CircleTrans;
    Transform EnterTrans;

    float size_;
    bool flg;
    bool Sflg;
    bool Aflg;

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
};