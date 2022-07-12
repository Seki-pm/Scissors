#pragma once
#include "Engine/GameObject.h"
#include "PolygonCollider.h"

class Stage;

//�n�T�~�̐n���Ǘ�����N���X
class Blade : public GameObject
{
    int BladeModel_;

public:
    bool isPrick;   //�n�ʂɎh�����Ă邩�ǂ���
    PolygonCollider collider;   //��[�ȊO�̓����蔻��
    Stage* pStage_;  //�X�e�[�W�̃A�h���X

    
public:
    //�R���X�g���N�^
    Blade(GameObject* parent);

    //�f�X�g���N�^
    ~Blade();

    //������
    void Initialize() override;

    // ���[�h
    // �����F0������ȊO���ō��E�̐n�̔��ʂ��s��
    void Load(const int lr);

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;



    //�n�T�~�̊J��
    void Open(int angle);

    //�h�����Ă邩�ǂ���
    bool IsPrick() { return isPrick; }

    //��[�ʒu���擾
    XMFLOAT3 GetTipPoint();

};