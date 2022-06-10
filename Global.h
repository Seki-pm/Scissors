#pragma once
#include "Engine/Direct3D.h"
#include <vector>
using namespace std;

//�O���[�o���ϐ��i�V�[�����܂����ŗL���j
class Global
{
private:
	//Scissors��Position
	static float Trans_Pos_X;				
	static float Trans_Pos_Y;				
	static float Trans_Pos_Z;	

	//�J������Start & Goal
	static float Camera_StartX;
	static float Camera_StartY;
	static float Camera_GoalX;
	static float Camera_GoalY;

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
	static XMFLOAT3 ItemImageSca_Select;   //�摜(SelectScene)

	//StageUnlock�ϐ�
	static bool Unlock2;
	static bool Unlock3;

	//Player�֘A
	static int HP;              //����HP
	static int MAXHP;           //�ő�HP
	static int NORMAL_DAMAGE;   //�ʏ�̃_���[�W
	static float JumpStart;     //�W�����v�̊J�n�ʒu
	static float JumpEnd;       //�W�����v�̏I���ʒu

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

	//�n�T�~�̌��݃|�W�V������Global��ʂ��đ���
	void SetTransPos_X(float x);
	float GetTransPos_X();

	void SetTransPos_Y(float y);
	float GetTransPos_Y();

	void SetTransPos_Z(float z);
	float GetTransPos_Z();

	//�J�����̃X�^�[�g�ƃS�[���ʒu��ݒ�
	void SetCameraStartX(float start);
	void SetCameraStartY(float start);
	float GetCameraStartX();
	float GetCameraStartY();

	void SetCameraGoalX(float goal);
	void SetCameraGoalY(float goal);
	float GetCameraGoalX();
	float GetCameraGoalY();
};
