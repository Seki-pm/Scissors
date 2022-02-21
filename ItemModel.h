#pragma once
#include "Engine/GameObject.h"
#include "Engine/SphereCollider.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Global.h"


//���������Ǘ�����N���X
class ItemModel : public GameObject
{
    int hModel_;
    int rotate; //��]��

 
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