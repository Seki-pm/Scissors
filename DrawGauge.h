#pragma once
#include "Engine/Image.h"
#include "Engine/Transform.h"
#include "Global.h"


class DrawGauge
{
private:

public:

	//�R���X�g���N�^
	DrawGauge();

	//�f�X�g���N�^
	~DrawGauge();

	//������
	void Initialize();

	//�����̕`��
	//����:�����̒l
	//     X���W
	//�@�@ Y���W
	//�@�@ ���[�h�����摜
	//     �ő�HP
	void Draw(int val, float x, float y, int hPict,int maxhp);

	//�J��
	void Release();

};
