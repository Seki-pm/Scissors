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
    int GaugeImage_;      //�Q�[�W�摜
    int GaugeFrameImage_; //�Q�[�W�t���[���摜

    Transform FrameTrans;

    //�萔
    const XMFLOAT2 HP_IMAGE_POS = XMFLOAT2(-0.99f, 0.85f); //HP�Q�[�W�ʒu
    const XMFLOAT3 FRAME_POS = XMFLOAT3(-0.59f, 0.88f, 0); //�t���[���ʒu
    const int  NORMAL_DAMAGE = 1; //�ʏ�̃_���[�W

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