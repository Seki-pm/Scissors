#pragma once
#include "Engine/GameObject.h"
#include "Engine/Image.h"


//�A�C�e���̎擾�̗L���̉摜���Ǘ�����N���X
class ItemImage : public GameObject
{
    int ImageHandle_;
public:
    //�R���X�g���N�^
    ItemImage(GameObject* parent);

    //�f�X�g���N�^
    ~ItemImage();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;
};
