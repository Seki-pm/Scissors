#pragma once
#include <vector>
#include <DirectXMath.h>

using namespace DirectX;
using namespace std;

//���p�`�̓����蔻��
class PolygonCollider
{
	//���p�`�̊e���_������z��
	//���p�`�ł��������A�ʑ��p�`����Ȃ��ƃ_��
	vector<XMVECTOR> points_;

public:

	//���p�`�̒��_�̈ʒu��ǉ�
	//���ʑ��p�`����Ȃ��ƃ_��
	//�����v���ɐݒ肵�Ă�������
	//�����Fx,y	�ǉ��������ʒu
	void AddPoint(float x, float z);


	//���p�`�Ɠ_�̓����蔻��
	//�����Fpoint�@�_�̈ʒu
	//�ߒl�F�Ԃ����Ă���true
	bool Hit(XMFLOAT3 point, XMMATRIX worldMatrix = XMMatrixIdentity());


	//�����Ƒ��p�`�́u��_�v�ƁA�������Ă�ʂ́u�@���v�����߂�
	//�i�u�n�T�~�̒��S����n��܂ł̐����v�ƒn�ʂƂ̌�_�A�y�т��̒n�ʂ̖@�������߂�̂Ɏg�p�j
	//�����F�����̒[�̈ʒu�i�n�T�~�̒��S�j
	//�����F�����̂�����[�̈ʒu�i�n�T�~�̐�[�j
	//�����F�@��������ϐ��̃A�h���X
	//�����F��_������ϐ��̃A�h���X
	//�ߒl�F���������������Ă邩�ǂ���
	bool GetNormal(XMFLOAT3 p1, XMFLOAT3 p2, XMFLOAT3* normal, XMFLOAT3* hitPoint);


	bool Hit(PolygonCollider* target, XMMATRIX worldMatrix);
};
