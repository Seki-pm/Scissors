#include "DrawGauge.h"

//�R���X�g���N�^
DrawGauge::DrawGauge()
{
}

//�f�X�g���N�^
DrawGauge::~DrawGauge()
{
}

//������
void DrawGauge::Initialize()
{
}

//�`��
void DrawGauge::Draw(int val, float x, float y, int hPict, int maxhp)
{
	Transform trans;

	//�o���ꏊ
	trans.position_.x = x;
	trans.position_.y = y;
	trans.scale_ = XMFLOAT3(2.f, 1.3f, 0.96f);

	//�摜�̕�(%)
	float ImageWidth_ = 512;           //�摜�̕�
	float w = ImageWidth_ / 100;       //�摜��(1%)
	float width = ImageWidth_ / 200;   //�摜��(0.5%)
	float wid = w * 50;

	//���݂�HP(%)
	float hp_    = Global::HP;          //���݂�HP
	float Nowhp  = hp_ / maxhp * 100;   //���݂�HP(%)


	//�摜���Ɍ���HP�̊�����������
	float image = width * Nowhp + wid;
	//float image = w * Nowhp;

	float X = image - wid;

	//�e�s��̌v�Z
	trans.Calclation();

	//�Q�[�W�����炷
	Image::SetRect(hPict, X, 0, wid, 130);

	//�`��
 	Image::SetTransform(hPict, trans);
	Image::Draw(hPict);
}

//�J��
void DrawGauge::Release()
{
}
