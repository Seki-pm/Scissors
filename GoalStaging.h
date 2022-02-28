#pragma once
#include "Engine/GameObject.h"
#include "Engine/Model.h"

//�S�[�����o���Ǘ�����N���X
class GoalStaging : public GameObject
{
    int hModel_;    //���f���ԍ�

    int BackImage_;
    int CircleImage_;

    Transform CircleTrans;

    float size_;
    bool flg;

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