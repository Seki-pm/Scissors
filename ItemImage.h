#pragma once
#include "Engine/GameObject.h"
#include "Engine/SceneManager.h"
#include "Engine/Image.h"
#include "Global.h"


//�A�C�e���̎擾�̗L���̉摜���Ǘ�����N���X
class ItemImage : public GameObject
{
    //�摜���[�h�p
    int FrameImage_;
    int CoinImage_;

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
