#pragma once
#include "Engine/GameObject.h"
#include "Engine/SphereCollider.h"
#include "Engine/SceneManager.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/Audio.h"
#include "Global.h"
#include "StageSelectScene.h"

//�R�C�����Ǘ�����N���X
class ItemModel : public GameObject
{
    int CoinModel_; //�R�C�����f���p�ϐ�
    int CoinSound_; //�R�C���擾���̉�

    //�萔
    const float ROTATION_SPEED = 16.6f;    //��]���x
    const float UP_DISTANCE = 0.01f;       //�オ�鋗��
    const int   ROTATION_NUMBER = 8;       //��]��

    const XMFLOAT3 ITEM_SIZE = XMFLOAT3(1.1f, 1.1f, 1.1f); //�A�C�e���̃T�C�Y

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