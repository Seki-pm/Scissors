#pragma once
#include "Engine/Image.h"
#include "Engine/Transform.h"

class Number
{
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

