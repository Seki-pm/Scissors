#pragma once
#include "Engine/Image.h"
#include "Engine/Transform.h"

class Number
{
	const float NUMBER_INTERVAL = 0.06f;

public:

	//�R���X�g���N�^
	Number();

	//�f�X�g���N�^
	~Number();

	//�����̕`��
	//����:�����̒l
	//     X���W
	//�@�@ Y���W
	//�@�@ ���[�h�����摜
	void Draw(int val, float x, float y, int hPict);

	//�J��
	void Release();

};

