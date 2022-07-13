#pragma once
#include "Engine/Image.h"
#include "Engine/Transform.h"
#include "Global.h"


class Gauge
{
	const XMFLOAT3 TRANS_POS = XMFLOAT3(2.f, 1.3f, 0.96f); //�ʒu
	const int SETRECT_HEIGHT = 130;   //�؂��鍂��
	const int IMAGE_WIDTH = 512;      //�摜��

public:

	//�R���X�g���N�^
	Gauge();

	//�f�X�g���N�^
	~Gauge();

	//������
	void Initialize();

	//�����̕`��
	//����:�����̒l
	//     X���W
	//�@�@ Y���W
	//�@�@ ���[�h�����摜
	//     �ő�HP
	void Draw(int val, float x, float y, int hPict);

	//�J��
	void Release();

};
