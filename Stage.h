#pragma once
#include "Engine/GameObject.h"
#include "Global.h"
#include "PolygonCollider.h"
#include "Scissors.h"
#include <vector>

using namespace std;

//�n�T�~�̐n���Ǘ�����N���X
class Stage : public GameObject
{
    int StageModel_;
    Global gl;

    //�R���C�_�[�i�ʑ��p�`�𕡐��g�ݍ��킹��j
    vector<PolygonCollider> colliders_;


public:
    //�R���X�g���N�^
    Stage(GameObject* parent);

    //�f�X�g���N�^
    ~Stage();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

    //�w�肵���_���X�e�[�W�ƂԂ����Ă��邩���ׂ�
    //�����Fposition�@���ׂ����ʒu
    bool IsHit(XMFLOAT3 position);

    //��[�ȊO���X�e�[�W�ƂԂ����Ă��邩���ׂ�
    //
    bool IsHit(PolygonCollider target, XMMATRIX world);

    //�Փ˂����ӂ̖@���ƏՓ˓_�𒲂ׂ�
    void GetNormal(XMFLOAT3 p1, XMFLOAT3 p2, XMFLOAT3* normal, XMFLOAT3* hitPoint);

    void Stage1();
    void Stage2();

};