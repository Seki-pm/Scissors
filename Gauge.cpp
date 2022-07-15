#include "Gauge.h"

const XMFLOAT3 TRANS_SCA = XMFLOAT3( 2.f,1.3f,0.96f); //�\���ʒu
const int SETRECT_HEIGHT = 130;   //�؂��鍂��
const int IMAGE_WIDTH = 512;      //�摜��

//�R���X�g���N�^
Gauge::Gauge()
{
}

//�f�X�g���N�^
Gauge::~Gauge()
{
}

//������
void Gauge::Initialize()
{
}

//�`��
void Gauge::Draw(int val, float x, float y, int hPict)
{
	Transform trans;

	//�o���ꏊ
	trans.position_.x = x;
	trans.position_.y = y;
	trans.scale_ = TRANS_SCA;

	//�摜�̕�(%)���v�Z
	float ImageWidth_ = IMAGE_WIDTH;      //�摜�̕�
	float PicWid = ImageWidth_ / 200;     //�摜��(0.5%)


	//���݂�HP(%)���v�Z
	float hp = (float)val;                             //���݂�HP(int)
	float Nowhp  = hp / Global::MAXHP * 100;    //���݂�HP(%)


	//�g�p���Ă���摜���E�����Ȃ̂Ō����ʂ������ɂ���
	float SubHP = ( ImageWidth_ / 2 ) - ( PicWid * Nowhp );  //  ��������HP��   = �摜��/2 - �摜��(0.5%)*����HP(%)
	float X = SubHP;                                         //�؂���J�n�ʒu = ��������HP�� 
	float width = ImageWidth_ - SubHP * 2;                   //�؂���I���ʒu = �摜�� - ��������HP�� * 2


	//�e�s��̌v�Z
	trans.Calclation();

	//�؂����ăQ�[�W�����炷
	Image::SetRect(hPict, X, 0, width, SETRECT_HEIGHT);

	//�`��
 	Image::SetTransform(hPict, trans);
	Image::Draw(hPict);
}

//�J��
void Gauge::Release()
{
}
