#pragma once
#include "Engine/GameObject.h"
#include "Engine/Model.h"
#include "Engine/Image.h"
#include "Global.h"
#include "PolygonCollider.h"
#include "Sign.h"
#include "Scissors.h"
#include "StageSelectScene.h"
#include <vector>
using namespace std;

class Scissors;

enum Stage1_Sound {
    St1_Glass = 1,
    St1_Wood = 2,
    St1_Max
};

//�n�T�~�̐n���Ǘ�����N���X
class Stage : public GameObject
{
    int StageModel_; //�X�e�[�W���f��
    int BackImage_;  //�w�i
    int Sound_;

    Global gl;
    Scissors* pScissors_;

    //�R���C�_�[�i�ʑ��p�`�𕡐��g�ݍ��킹��j
    vector<PolygonCollider> colliders_;

    //�T�E���h(Stage���Ƃ̃T�E���h������)
    vector<int> sounds_;

    // ���̒n�`�̖ʂ̒��_������
    PolygonCollider pc1, pc2, pc3, pc4, pc5, pc6,
                    pc7, pc8, pc9, pc10, pc11, pc12,
                    pc13, pc14, pc15, pc16, pc17, pc18,
                    pc19, pc20, pc21, pc22, pc23, pc24,
                    pc25, pc26, pc27, pc28, pc29, pc30,
                    pc31, pc32, pc33, pc34, pc35, pc36,
                    pc37, pc38, pc39, pc40, pc41, pc42,
                    pc43, pc44, pc45, pc46, pc47, pc48,
                    pc49, pc50;

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
    void Load(const int stage);

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

    //�w�肵���_���X�e�[�W�ƂԂ����Ă��邩���ׂ�
    //�����Fposition�@���ׂ����ʒu
    bool IsHit(XMFLOAT3 position);

    //��[�ȊO���X�e�[�W�ƂԂ����Ă��邩���ׂ�
    //�����F�Ԃ����Ă���R���C�_
    //�@�@�@���[���h���W
    bool IsHit(PolygonCollider target, XMMATRIX world);

    //�Փ˂����ӂ̖@���ƏՓ˓_�𒲂ׂ�
    void GetNormal(XMFLOAT3 p1, XMFLOAT3 p2, XMFLOAT3* normal, XMFLOAT3* hitPoint);

    //�X�e�[�W�̃R���C�_�ݒ�
    void Stage1();
    void Stage2();
    void Stage3();

    //�X�e�[�W�̓ǂݍ���
    void Stage1Load();
    void Stage2Load();
    void Stage3Load();

    //�e�����̒l
    XMFLOAT3 Repel(){ return XMFLOAT3(0.1f,0.3f,0); }

    //�e�������`�F�b�N
    //�����F�`�F�b�N����ԍ�
    void RepelCheck(int i);

    //���ގ��̒l
    XMFLOAT3 Sink() { return XMFLOAT3(0,-0.01f,0); }

    //���ޏ����`�F�b�N
    //�����F�`�F�b�N����ԍ�
    void SinkCheck(int i);

    //����炷
    void Landing();
};