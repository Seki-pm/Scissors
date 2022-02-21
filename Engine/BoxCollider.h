#pragma once
#include "Collider.h"


//-----------------------------------------------------------
//���^�̓����蔻��
//-----------------------------------------------------------
class BoxCollider :	public Collider
{
	//Collider�N���X��private�����o�ɃA�N�Z�X�ł���悤�ɂ���
	friend class Collider;

public:
	//�R���X�g���N�^�i�����蔻��̍쐬�j
	//�����FbasePos	�����蔻��̒��S�ʒu�i�Q�[���I�u�W�F�N�g�̌��_���猩���ʒu�j
	//�����Fsize	�����蔻��̃T�C�Y�i���A�����A���s���j
	BoxCollider(XMFLOAT3 basePos, XMFLOAT3 size);


	//�_�Ƃ̓����蔻��
	//�����Fposition�@�_�̈ʒu
	//�ߒl�F�������Ă邩�ǂ���
	bool IsHitBoxVsPoint(XMFLOAT3 position);


private:
	//�ڐG����
	//�����Ftarget	����̓����蔻��
	//�ߒl�F�ڐG���Ă��true
	bool IsHit(Collider* target) override;
};

