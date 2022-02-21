#include "GoalStaging.h"

//�R���X�g���N�^
GoalStaging::GoalStaging(GameObject* parent)
    :GameObject(parent, "GoalStaging"), hModel_(-1)
{
}

//�f�X�g���N�^
GoalStaging::~GoalStaging()
{
}

//������
void GoalStaging::Initialize()
{
    //���f���f�[�^�̃��[�h
    hModel_ = Model::Load("�t�@�C����");
    assert(hModel_ >= 0);
}

//�X�V
void GoalStaging::Update()
{
}

//�`��
void GoalStaging::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//�J��
void GoalStaging::Release()
{
}