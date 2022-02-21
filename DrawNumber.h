#pragma once
#include "Engine/Image.h"
#include "Engine/Transform.h"

class DrawNumber
{
private:
	DrawNumber* pNumber_;

public:

	//�R���X�g���N�^
	DrawNumber();

	//�f�X�g���N�^
	~DrawNumber();

	//������
	void Initialize();

	//�����̕`��
	//����:�����̒l
	//     X���W
	//�@�@ Y���W
	//�@�@ ���[�h�����摜
	void Draw(int val, float x, float y, int hPict);

	//�J��
	void Release();

};

