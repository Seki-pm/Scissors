#pragma once
#include "Engine/Direct3D.h"
#include <vector>
using namespace std;

//�O���[�o���ϐ��i�V�[�����܂����ŗL���j
class Global
{
private:
	//Scissors��Position
	static XMFLOAT3 Position_;

	//�J������Start & Goal
	static XMFLOAT2 Camera_Start;
	static XMFLOAT2 Camera_Goal;

public:

	//Player�̏����ʒu & ������]�p�x
	static XMFLOAT3 InitPos;
	static XMFLOAT3 InitRot;

	//StageSelectScene�̑I������Ă���ԍ�
	static int SelectStage;

	//�R�C���̕\���ʒu
	static XMFLOAT3 ItemModelPos;  //���f��
	static XMFLOAT3 ItemImagePos;  //�摜�ʒu
	static XMFLOAT3 ItemImageSca;  //�摜�T�C�Y
	static XMFLOAT3 ItemImagePos_Stage;   //�摜(StageScene)
	static XMFLOAT3 ItemImageSca_Stage;   //�摜(StageScene)
	static XMFLOAT3 ItemImageSca_Select;  //�摜(SelectScene)

	//StageUnlock�ϐ�
	static bool Unlock2;
	static bool Unlock3;

	//Player�֘A
	static int HP;              //����HP
	static int MAXHP;           //�ő�HP
	static int NORMAL_DAMAGE;   //�ʏ�̃_���[�W
	static float JumpStart;     //�W�����v�̊J�n�ʒu
	static float JumpEnd;       //�W�����v�̏I���ʒu
	static bool Soundflg;

	//Global�̃t���O
	static bool Timer;          //GoalStaging�p�̃^�C�}�[
	static bool GetCoin;        //�R�C����Get������
	static bool GetCoin_1;      //Stage1�̃R�C����Get
	static bool GetCoin_2;      //Stage2�̃R�C����Get
	static bool GetCoin_3;      //Stage3�̃R�C����Get
	static bool GameOver;       //GameOver�̏���
	static bool IsGameOver;     //GameOver����񂾂��\��
	static bool Pause;          //Pause�p
	static bool RepelFlg;       //�e����鎞�p
	static bool SinkFlg;        //���ގ��p
	static bool IsJump;         //�W�����v���ł��邩�ۂ�
	static bool ItemReDraw;     //�A�C�e���̍ĕ\��

	//Scene�Ǘ��p
	static int SCENE_ID;

	//�n�ʃM�~�b�N�p���I�z��
	static vector<int> Repel_;
	static vector<int> Sink_;

	//�n�T�~�̈ʒu��ݒ�&����
	void SetTransPos(XMFLOAT3 position);
	XMFLOAT3 GetTransPos();

	//�J�����̃X�^�[�g�ƃS�[���ʒu��ݒ�i X �� Y �j
	void SetCameraStart(float startX, float startY);
    void SetCameraGoal(float goalX, float goalY);

	XMFLOAT2 GetCameraStart();
	XMFLOAT2 GetCameraGoal();
};
