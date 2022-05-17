#include "PolygonCollider.h"
#include "Global.h"


//���p�`�̒��_�̈ʒu��ǉ�
// ���p�`���������� ==�@points_.size() 
void PolygonCollider::AddPoint(float x, float y)
{
	points_.push_back(XMVectorSet(x, y, 0, 0));
}


//���p�`�Ɠ_�̓����蔻��
//
//�u�l�p�`ABCD�v�Ɓu�_�o�v�̓����蔻����l����
//�iABCD�͎��v���ɔz�u����Ă�����̂Ƃ���j
//
//�_���l�p�`�����ɂ���Ȃ�
//�_P�́A��AB�̉E���ɂ���A��BC�̉E���ɂ���A��CD�̉E���ɂ���A��DA�̉E���ɂ���͂�
// 
//�E�������͊O�ς����߂�΂킩��
//P��AB�̉E�ɂ��邩�ǂ�����AB��AP�̊O�ς����߂�΂����i���ʂ�Z���}�C�i�X��������E�ɂ���j
bool PolygonCollider::Hit(XMFLOAT3 point, XMMATRIX worldMatrix)
{
	//�������͍l���Ȃ�
	point.z = 0;

	//�_�̐��i���ӂ̐��j���[�v
	for (int i = 0; i < points_.size(); i++)
	{
		// 2���_(1��)�̈ʒu�����߂�
		XMVECTOR v1 = points_[i];
		XMVECTOR v2 = points_[(i + 1) % points_.size()];

		// ���[���h�s���������
		v1 = XMVector3TransformCoord(v1, worldMatrix);
		v2 = XMVector3TransformCoord(v2, worldMatrix);

		// point = �_�̈ʒu
		XMVECTOR p = XMLoadFloat3(&point);

		// ��̃x�N�g������O�ς����߂�
		XMVECTOR edge1 = v2 - v1;        // ���p�`�̕ӂ̃x�N�g��(���v���)
		XMVECTOR edge2 = p - v1;         // ���������_�܂ł̃x�N�g��
		XMVECTOR cross = XMVector3Cross(edge1, edge2);


		//�_���ӂ̍��ɂ���Ȃ�Ԃ����ĂȂ�
		// cross���}�C�i�X�Ȃ�Ԃ����Ă���
		if (XMVectorGetZ(cross) > 0)
		{
			return false;
		}
	}

	//�S�Ă̕ӂ̉E���ɂ��������Ԃ����Ă���
	return true;
}

// �����ƒn�`�́u��_�v�ƒn�`����́u�@���v�����߂�
bool PolygonCollider::GetNormal(XMFLOAT3 point1, XMFLOAT3 point2, XMFLOAT3* normal, XMFLOAT3* hitPoint)
{
	// z�����͍l���Ȃ�
	point1.z = 0;
	point2.z = 0;

	//�_�̐��i���ӂ̐��j���[�v
	for (int i = 0; i < points_.size(); i++)
	{
		// �n�`���̒��_�̈ʒu
		XMVECTOR v1 = points_[i];
		XMVECTOR v2 = points_[(i + 1) % points_.size()];

		// �n�T�~���̐^�񒆂Ɛn��̈ʒu
		XMVECTOR v3 = XMLoadFloat3(&point1);
		XMVECTOR v4 = XMLoadFloat3(&point2);



		//�܂����� v1-v2 �ɑ΂��āA�_v3��v4�����E�ǂ����ɂ��邩
		XMVECTOR cross1 = XMVector3Cross(v2 - v1, v3 - v1);     
		XMVECTOR cross2 = XMVector3Cross(v2 - v1, v4 - v1);     

		// �����̗L��
		if ((XMVectorGetZ(cross1) > 0 && XMVectorGetZ(cross2) > 0)			//�ǂ������� 
			|| (XMVectorGetZ(cross1) < 0 && XMVectorGetZ(cross2) < 0))		//�܂��͂ǂ������E
		{
			//�������ĂȂ�
			continue;
		}


		//���x�͒��� v3-v4 �ɑ΂��āA�_v1��v2�����E�ǂ����ɂ��邩
		cross1 = XMVector3Cross(v4 - v3, v1 - v3);
		cross2 = XMVector3Cross(v4 - v3, v2 - v3);

		// �����̗L��
		if ((XMVectorGetZ(cross1) > 0 && XMVectorGetZ(cross2) > 0)			//�ǂ������� 
			|| (XMVectorGetZ(cross1) < 0 && XMVectorGetZ(cross2) < 0))		//�܂��͂ǂ������E
		{
			//�������ĂȂ�
			continue;
		}

		//---------------�����܂ŗ�����������Ă���!!-------------------

		//�������Ă�̂����������̂ŁA��_�����߂�
		//https://qiita.com/kaityo256/items/988bf94bf7b674b8bfdc
		float det = (XMVectorGetX(v1) - XMVectorGetX(v2)) * (XMVectorGetY(v4) - XMVectorGetY(v3)) - (XMVectorGetX(v4) - XMVectorGetX(v3)) * (XMVectorGetY(v1) - XMVectorGetY(v2));
		float t = ((XMVectorGetY(v4) - XMVectorGetY(v3)) * (XMVectorGetX(v4) - XMVectorGetX(v2)) + (XMVectorGetX(v3) - XMVectorGetX(v4)) * (XMVectorGetY(v4) - XMVectorGetY(v2))) / det;
		hitPoint->x = t * XMVectorGetX(v1) + (1.0 - t) * XMVectorGetX(v2);
		hitPoint->y = t * XMVectorGetY(v1) + (1.0 - t) * XMVectorGetY(v2);
		hitPoint->z = 0;

		//�@�������߂�
		//�����������̃x�N�g���Ƃ̊O�ς����߂�Ζ@���ɂȂ�
		XMVECTOR vecNormal = XMVector3Cross(v2 - v1, XMVectorSet(0, 0, -1, 0));
		vecNormal = XMVector3Normalize(vecNormal);
		XMStoreFloat3(normal, vecNormal);

		return true;
	}

	return false;
}

//�X�e�[�W�Ƃ̓����蔻��
bool PolygonCollider::Hit(PolygonCollider* target, XMMATRIX worldMatrix)
{
	//target�̒��_�̐��i���ӂ̐��j���[�v
	for (int i = 0; i < target->points_.size(); i++)
	{
		XMVECTOR vP = XMVector3TransformCoord(target->points_[i], worldMatrix);
		XMFLOAT3 fP;
		XMStoreFloat3(&fP, vP);
		if (Hit(fP))
		{
			return true;
		}
	}

	//���_�̐����[�v
	for (int i = 0; i < points_.size(); i++)
	{
		XMFLOAT3 fP;
		XMStoreFloat3(&fP, points_[i]);

		if (target->Hit(fP, worldMatrix))
		{
			return true;
		}
	}

	return false;
}

//�͂�������ǉ�
void PolygonCollider::AddRepel(int num)
{
	Global::Repel_.push_back(num - 1);
}

//�͂������Ƃ̔�����s��
void PolygonCollider::SetRepelCheck(int search)
{
	for (int i = 0; i < Global::Repel_.size(); i++)
	{
		if (Global::Repel_[i] == search)
		{
			number = search;
		}	
	}
}

//�͂������̔ԍ��𑗂�
int PolygonCollider::GetRepelCheck()
{
	return number;
}
