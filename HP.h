#pragma once
#include "Engine/GameObject.h"
#include "Engine/Input.h"
#include "DrawNumber.h"
#include "Gauge.h"

//HP���Ǘ�����N���X
class HP : public GameObject
{
    DrawNumber* pNumber_; //�����`��p
    Gauge*  pGauge_;  //�Q�[�W�`��p

    //���[�h�p�ϐ�
    int NumberHandle_;   
    int GaugeHandle_;    
    int GaugeFrame_;

    Transform FrameTrans;

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