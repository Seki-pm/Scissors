#pragma once
#include "Engine/Direct3D.h"
#include <vector>
#include <bitset>
using namespace std;

//�O���[�o���ϐ��i�V�[�����܂����ŗL���j
class Game
{
private:
	//�n�T�~�̈ʒu������ϐ�
	static XMFLOAT3 Position_;

	//�J������Start & Goal
	static XMFLOAT2 Camera_Start;
	static XMFLOAT2 Camera_Goal;

public:

	//�R�C���̕\���ʒu�E�傫��
	static XMFLOAT3 ItemModelPos;  //���f���ʒu
	static XMFLOAT3 ItemImagePos;  //�摜�ʒu
	static XMFLOAT3 ItemImageSca;  //�摜�T�C�Y

	//StageSelectScene�̑I������Ă���ԍ�
	static int SelectStage;

	//Player�̍ő�HP
	static int MAXHP; 

	//Game�̃t���O
	static bool GetCoin;        //�R�C����Get������
	static bool GameOver;       //GameOver�̏���
	static bool IsGameOver;     //GameOver����񂾂��\��
	static bool Pause;          //Pause�p
	static bool ItemReDraw;     //�A�C�e���̍ĕ\��

	//�n�ʃM�~�b�N�p���I�z��
	static vector<int> Repel_;
	static vector<int> Sink_;


	//�X�e�[�W�̏�Ԃ�\���\����
	static struct Stage_Status {
		const unsigned char UnLock;   //���̃X�e�[�W�̃A�����b�N
		const unsigned char GetCoin;  //�X�e�[�W�̃R�C�����Q�b�g�������ǂ���
		const unsigned char Clear;    //�R�C��������ăN���A�������ǂ���
	};

	//�X�e�[�W�̏�Ԃ�����ϐ�
	static unsigned int Status;


	//�\���̂ɃA�N�Z�X���邽�߂̕ϐ�
	static Game::Stage_Status stage1;
	static Game::Stage_Status stage2;
	static Game::Stage_Status stage3;

	//�r�b�g�t���O�Ǘ�
	void setState(const unsigned char sstate );   //�t���O�𗧂Ă�
	void unsetState(const unsigned char sstate);  //�t���O��������
	bool getState(const unsigned char sstate);    //�t���O���m�F����

	//�n�T�~�̈ʒu��ݒ�&����
	void SetTransPos(XMFLOAT3 position);
	XMFLOAT3 GetTransPos();

	//�J�����̃X�^�[�g�ƃS�[���ʒu��ݒ�i X , Y �j
	void SetCameraStart(float startX, float startY);
    void SetCameraGoal(float goalX, float goalY);

	//�J�����̃X�^�[�g�ƃS�[���ʒu���擾�i X , Y �j
	XMFLOAT2 GetCameraStart();
	XMFLOAT2 GetCameraGoal();
};
