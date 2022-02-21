#pragma once
#include "Engine/GameObject.h"
#include "Engine/Input.h"
#include "DrawNumber.h"
#include "DrawGauge.h"

//HP���Ǘ�����N���X
class HP : public GameObject
{
    DrawNumber* pNumber_;
    DrawGauge*  pGauge_;

    int NumberHandle_;
    int GaugeHandle_;
    int GaugeFrame_;

    int MaxHp;

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

    void HPCalc();
};