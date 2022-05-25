#pragma once
#include "Engine/GameObject.h"
#include "Global.h"
#include "PolygonCollider.h"
#include "Scissors.h"
#include "Sign.h"
#include "Engine/Model.h"
#include "Engine/Image.h"
#include <vector>

using namespace std;

//�n�T�~�̐n���Ǘ�����N���X
class Stage : public GameObject
{

    int StageModel_;
    int BackImage_;

    Global gl;

    //�R���C�_�[�i�ʑ��p�`�𕡐��g�ݍ��킹��j
    vector<PolygonCollider> colliders_;

    // ���̒n�`�̖ʂ̒��_������
    PolygonCollider pc1,  pc2,  pc3,  pc4,  pc5,  pc6,
                    pc7,  pc8,  pc9,  pc10, pc11, pc12,
                    pc13, pc14, pc15, pc16, pc17, pc18,
                    pc19, pc20, pc21, pc22, pc23, pc24,
                    pc25, pc26, pc27, pc28, pc29, pc30;

public:
    //�R���X�g���N�^
    Stage(GameObject* parent);

    //�f�X�g���N�^
    ~Stage();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�ǂݍ���
    void Load(const int st);

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

    //Stage
    void Stage1();
    void Stage2();
    void Stage3();

    //�e�����̊Ǘ�
    XMFLOAT3 Repel();

    void RepelCheck(int i);
    void SinkCheck(int i);

    //���ގ��̊Ǘ�
    XMFLOAT3 Sink();
};