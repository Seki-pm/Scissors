#include "DrawNumber.h"

//�R���X�g���N�^
DrawNumber::DrawNumber():pNumber_(nullptr)
{
}

//�f�X�g���N�^
DrawNumber::~DrawNumber()
{
}

//������
void DrawNumber::Initialize()
{
}

//�`��
void DrawNumber::Draw(int val, float x, float y, int hPict)
{
	Transform trans;

	//��̈ʂ��o���ꏊ
	trans.position_.x = x;
	trans.position_.y = y;


	while (true)
	{
		//�����̕������炷(�����̊Ԋu)
		trans.position_.x -= 0.06f;

		//�e�s��̌v�Z
		trans.Calclation();

		//������؂蔲��
		//1�̈ʂ����`�悷��
		Image::SetRect(hPict, (val % 10) * 51, 0, 51, 130);

		Image::SetTransform(hPict, trans);
		Image::Draw(hPict);

		//val��10�łŊ���
		val /= 10;

		//0�ɂȂ�����break
		if (val <= 0) break;
	}

}

//�J��
void DrawNumber::Release()
{
}
