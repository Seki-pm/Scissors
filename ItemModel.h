#pragma once
#include "Engine/GameObject.h"
#include "Engine/SphereCollider.h"
#include "Engine/SceneManager.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/Audio.h"
#include "StageSelectScene.h"
#include "Global.h"


//�R�C�����Ǘ�����N���X
class ItemModel : public GameObject
{
    int CoinModel_; //�R�C�����f���p�ϐ�
    int CoinSound_; //�R�C���擾���̉�

    int rotate; //��]��

    const float Rotation_Speed;
    const float Up_Distance;
    const int   Rotation_Number;

public:
    //�R���X�g���N�^
    ItemModel(GameObject* parent);

    //�f�X�g���N�^
    ~ItemModel();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

    //�����ɓ�������
    //�����FpTarget ������������
    void OnCollision(GameObject* pTarget) override;

    //�A�j���[�V����
    void Animation();
};