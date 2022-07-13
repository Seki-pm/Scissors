#pragma once
#include "Engine/GameObject.h"
#include "Engine/Input.h"
#include "Gauge.h"

class Scissors;

//HP���Ǘ�����N���X
class HP : public GameObject
{
    Gauge*  pGauge_;  //�Q�[�W�`��p
    Scissors* pScissors_;


    //���[�h�p�ϐ�
    int GaugeImage_;    
    int GaugeFrameImage_;

    Transform FrameTrans;

    const XMFLOAT3 FRAME_POS;
    const int NORMAL_DAMAGE;
    const XMFLOAT2 HP_IMAGE_POS;


public:
    //�R���X�g���N�^
    HP(GameObject* parent);

    //�f�X�g���N�^
    ~HP();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

    //HP���v�Z
    void HPCalc();
};