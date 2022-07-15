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

    SceneManager* pSceneManager_;

    //�萔
    //const XMFLOAT3 FRAME_SIZE = XMFLOAT3(0.3f, 0.3f, 0.3f);  //�t���[���̃T�C�Y
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
