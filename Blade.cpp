#include "Blade.h"

//�R���X�g���N�^
Blade::Blade(GameObject* parent)
    :GameObject(parent, "Blade"),
     pStage_(nullptr),isPrick(false),
     BladeModel_(INITIAL_ERROR_VALUE)
{
}

//�f�X�g���N�^
Blade::~Blade()
{
}

//������
void Blade::Initialize()
{
    //�X�e�[�W��T���Ă����i�����蔻��ɕK�v�j
    pStage_ = (Stage*)FindObject("Stage");
}

// ���������ƂɃ��f����ǂݍ���
void Blade::Load(const int lr)
{
    // ������0�Ȃ�
    if (lr == 0)
    {
        //����ǂݍ���
        BladeModel_ = Model::Load("Model/Scissors/LBlade.fbx");
        assert(BladeModel_ >= 0);

        //�R���C�_�[���蓮�ł���
        collider.AddPoint(-0.37f, 0.73f);
        collider.AddPoint(-0.06f, 0.75f);
        collider.AddPoint(0.02f, -0.78f);
        
    }
    else  
    {
        // �E��ǂݍ���
        BladeModel_ = Model::Load("Model/Scissors/RBlade.fbx");
        assert(BladeModel_ >= 0);

        //�R���C�_�[���蓮�ł���
        collider.AddPoint(0.05f, 0.75f);
        collider.AddPoint(0.37f, 0.74f);
        collider.AddPoint(-0.02f, -0.78f);
    }
}

//�X�V
void Blade::Update()
{

    //�h�����Ă��Ȃ��Ȃ�
    if (!isPrick)
    {
        //�n�悪�n�ʂɎh�����Ă邩�`�F�b�N�i���ʂ�isPrick�t���O�ɓ����j
        isPrick = pStage_->IsHit(GetTipPoint());

        //�h�����Ă�ꍇ�A�n�T�~�ƒn�ʂ̌�_�����߁A�n�悪�����ɗ���悤�ړ�������i�߂荞��ł镪���ǂ��j
        if (isPrick && !pStage_->SinkFlg)
        {
            XMFLOAT3 hitPoint;  //��_������ϐ�
            XMFLOAT3 normal;    //�@��������ϐ�
            XMFLOAT3 center = GetParent()->GetPosition();  //�n�T�~�̈ʒu�����S�ʒu
            pStage_->GetNormal(center, GetTipPoint(), &normal, &hitPoint);
            GetParent()->SetPosition(center.x + hitPoint.x - GetTipPoint().x, center.y + hitPoint.y - GetTipPoint().y, 0);

            //�n�T�~�i�e�j�ɃW�����v�����Ƃ��Ēn�ʂ̖@����n��
            ((Scissors*)GetParent())->SetJumpDirection(normal);
        }
    }

    //��[�ȊO���n�ʂɓ������Ă�
    if (pStage_->IsHit(collider, GetWorldMatrix()) && !pStage_->SinkFlg)
    {
        // ���˂�����
        ((Scissors*)GetParent())->Reflection();
    }
}

//�`��
void Blade::Draw()
{
    Model::SetTransform(BladeModel_, transform_);
    Model::Draw(BladeModel_);
}

//�J��
void Blade::Release()
{
    BladeModel_ = INITIAL_ERROR_VALUE;
}


//�J��
void Blade::Open(int angle)
{
    //�h�����ĂȂ����
    if (!isPrick)
    {
        // Z���Œ��S��]
        transform_.rotate_.z += angle;
    }
}


//��[�ʒu���擾
XMFLOAT3 Blade::GetTipPoint()
{
    return Model::GetBonePosition(BladeModel_, "Point");
}
