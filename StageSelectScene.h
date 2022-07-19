#pragma once
#include "Engine/GameObject.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"
#include "Engine/Image.h"
#include "Engine/Transform.h"
#include "Engine/Audio.h"
#include "Global.h"
#include "ItemImage.h"

//�X�e�[�W�ԍ�
enum STAGE_NUMBER
{
	STAGE_NUMBER_1 = 1,
	STAGE_NUMBER_2 = 2,
	STAGE_NUMBER_3 = 3,
	STAGE_NUMBER_MAX
};

//�X�e�[�W���b�N
enum STAGE_LOCK
{
	STAGE_LOCK_2 = 2,
	STAGE_LOCK_3 = 3,
	STAGE_LOCK_MAX
};

//�X�e�[�W���x��
enum STAGE_LEVEL
{
	STAGE_LEVEL_EASY = 1,
	STAGE_LEVEL_NORMAL = 2,
	STAGE_LEVEL_HARD = 3,
	STAGE_LEVEL_MAX
};



//�X�e�[�W�I���V�[�����Ǘ�����N���X
class StageSelectScene : public GameObject
{
private:

	//�T�E���h
	enum SELECT_SOUND
	{
		SOUND_SELECT = 1,       //�I����
		SOUND_DETERMINATION = 2,//���艹
		SOUND_LOCK = 3,         //���b�N��
		SOUND_MAX
	};

	//���[�h�p�ϐ�
	enum Load
	{
		LOAD_MIN = 0,
		FrameImage_,       //�t���[���摜
		BackImage_,        //�w�i�摜
		DescriptionImage_, //�����摜
		LOAD_MAX
	};

	//enum�̂��̂�z��ɂ��Ă�
	int StageHandle_[STAGE_NUMBER_MAX];    //�X�e�[�W�ԍ�
	int StageLockHandle_[STAGE_LOCK_MAX];  //���b�N�摜
	int LevelHandle_[STAGE_LEVEL_MAX];     //��Փx�摜
	int SoundHandle_[SOUND_MAX];           //�I���Ȃǂ̉�
	int LoadHandle_[LOAD_MAX];             //���̑����[�h�摜

	bool Drawflg; //�\�������邩�ۂ�(��x����)

	//�etransform
	Transform Stage[STAGE_NUMBER_MAX];
	Transform Lock[STAGE_LOCK_MAX];
	Transform Level[STAGE_LEVEL_MAX];
	Transform FrameTransform;

	//�萔
	//�e�X�e�[�W�̃A�C�e���摜�ʒu
	const XMFLOAT3 ST1_ITEMIMAGE_POS = XMFLOAT3(-0.4f, 0, 0);
	const XMFLOAT3 ST2_ITEMIMAGE_POS = XMFLOAT3( 0.2f, 0, 0);
	const XMFLOAT3 ST3_ITEMIMAGE_POS = XMFLOAT3( 0.8f, 0, 0);

	//�e�X�e�[�W�摜�ʒu
	const XMFLOAT3 ST1_IMAGE_POS = XMFLOAT3(-0.6f, 0.2f, 0);
	const XMFLOAT3 ST2_IMAGE_POS = XMFLOAT3(   0 , 0.2f, 0);
	const XMFLOAT3 ST3_IMAGE_POS = XMFLOAT3( 0.6f, 0.2f, 0);

	//��Փx�̉摜�ʒu
	const XMFLOAT3 EASY_POSITION = XMFLOAT3(-0.6f, 0.5f, 0);
	const XMFLOAT3 NOMAL_POSITION = XMFLOAT3(   0 , 0.5f, 0);
	const XMFLOAT3 HARD_POSITION = XMFLOAT3( 0.6f, 0.5f, 0);

	const XMFLOAT3 DESCRIPTION_POS = XMFLOAT3(0.0f, -0.6f, 0);   //�����摜�̈ʒu
	const XMFLOAT3 ITEMIMAGE_SCALE_SELECT = XMFLOAT3(0.4f, 0.4f, 0.4f); //�A�C�e���摜�̃T�C�Y

	//�}�E�X�őI���ł���ʒu
	const XMFLOAT4 ST1_MOUSE_POS = ImagePos(128, 228); 
	const XMFLOAT4 ST2_MOUSE_POS = ImagePos(513, 228);
	const XMFLOAT4 ST3_MOUSE_POS = ImagePos(897, 228);

public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	StageSelectScene(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�L�[�I��
	void Select();

	//�}�E�X�I��
	void MouseSelect();

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	//�X�e�[�W�A�����b�N
	void StageUnlock();

	//�R�C���̎擾��
	void GetCoin();

	//�摜��4���_���擾( height=256 , width=128 )
	//�����F����̒��_���W�i X , Y �j
	XMFLOAT4 ImagePos(int x1, int y1);
};