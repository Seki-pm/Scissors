#pragma once
#include "Engine/Image.h"
#include "Engine/Transform.h"
#include "Global.h"


class Gauge
{
private:

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
