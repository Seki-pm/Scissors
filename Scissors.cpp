#include "Scissors.h"
#include "Stage.h"

//�R���X�g���N�^
Scissors::Scissors(GameObject* parent)
    :GameObject(parent, "Scissors"), move_(XMFLOAT3(0,0,0)),
    jumpDirection_(XMFLOAT3(0,0,0)),nowPivotPoint_(XMFLOAT3(0,0,0)),
    pBlade_L(nullptr), pBlade_R(nullptr),AnglePass_(0.0f), Calc(false),
    GLAVITY(0.03f)
{
}

//�f�X�g���N�^
Scissors::~Scissors()
{
}

//������
void Scissors::Initialize()
{
    //Load��()����0������ȊO���ō��E�̐n�𔻒f
    pBlade_L = Instantiate<Blade>(this);    //���n
    pBlade_L->Load(0);

    pBlade_R = Instantiate<Blade>(this);    //�E�n
    pBlade_R->Load(1);

    //�e�X�g�p
    //pBlade_R->isPrick = true;   //�E���n�ʂɎh�����Ă�Ƃ���
    pBlade_R->SetRotateZ(45);

    //�����ʒu
    transform_.position_ = Global::InitPos;

    SphereCollider* collision =
    new SphereCollider(XMFLOAT3(transform_.position_.x, transform_.position_.y - 2, transform_.position_.z), 0.3f);
    AddCollider(collision);
}

//�X�V
void Scissors::Update()
{
 

    //�n�T�~�̊J��
    OpenClose();

    //�n�T�~�̉�]
    Rotation();

    //���E�ړ�
    Move();

    //�W�����v�Ɨ���
    JumpAndFall();

    //���W�𑗂�
    SetPosition();

    //�X�^�[�g�����蒼���i���g���C�j
    if (Input::IsKeyDown(DIK_R))  Restart();

    if (transform_.position_.y <= -5)
    {
        move_ = XMFLOAT3(0, 0, 0);
        Global::GameOver = true;
    }

}


//�n�T�~�̊J��(���S��])
void Scissors::OpenClose()
{
    int angle = 0;

    if (Input::IsKey(DIK_W))    //�J��
    {
        angle = 2;
    }
    if (Input::IsKey(DIK_S))    //����
    {
        angle = -2;
    }

    //�J��
    pBlade_L->Open(-angle);
    pBlade_R->Open(angle);


    //�p�x����
    XMVECTOR LMax = { 1,0,0,0 };
    XMVECTOR RMax = { 1,0,0,0 };
     //Z���ŉ�]����s��
    XMMATRIX rotateL = XMMatrixRotationZ(XMConvertToRadians(pBlade_L->GetRotate().z));
    XMMATRIX rotateR = XMMatrixRotationZ(XMConvertToRadians(pBlade_R->GetRotate().z));
     //�s���VECTOR��
    LMax = XMVector3TransformCoord(LMax, rotateL);
    RMax = XMVector3TransformCoord(RMax, rotateR);
     //�ŏI�I�Ȋp�x(���ς��狁�߂�)
    float ang = acos(XMVectorGetX(XMVector3Dot(LMax, RMax)));

    if (XMConvertToDegrees(ang) > 170 || XMConvertToDegrees(ang) < 2)    //170�x�ȏ�܂���2�x�����Ȃ���ǂ�
    {
        pBlade_L->Open(angle);
        pBlade_R->Open(-angle);
    }
}

//�n�T�~�̉�](�n���])
void Scissors::Rotation()
{
    Blade* pPrickBlade = nullptr;   //�h�����Ă���̐n

    if (pBlade_L->IsPrick() && pBlade_R->IsPrick())     //�����h�����Ă����]�ł��Ȃ�
    {
        return;
    }
    else if (pBlade_L->IsPrick())       //�����h�����Ă�
    {
        pPrickBlade = pBlade_L;
    }
    else        
    {
        pPrickBlade = pBlade_R;       //�E���h�����Ă�
    }

    //�h�����Ă�n�̐�[�ʒu�i��]�O�j
    XMFLOAT3 prevPivotPoint = pPrickBlade->GetTipPoint();


    //��]
    int angle = 0;
    if (Input::IsKey(DIK_LEFT))
    {
        if (AnglePass_ > 10)
        {
            angle = 2;
        }
    }
    if (Input::IsKey(DIK_RIGHT))
    {
        if (AnglePass_ < 170)
        {
            angle = -2;
        }
    }
    transform_.rotate_.z += angle;


    //�h�����Ă�n�̐�[�ʒu�i��]��j
    nowPivotPoint_ = pPrickBlade->GetTipPoint();

    //��[�ʒu�����ꂽ���ړ������Ė߂�
    transform_.position_.x += prevPivotPoint.x - nowPivotPoint_.x;
    transform_.position_.y += prevPivotPoint.y - nowPivotPoint_.y;
    transform_.position_.x += prevPivotPoint.z - nowPivotPoint_.z;
}

//���E�ړ�
void Scissors::Move()
{
    if (!pBlade_L->IsPrick() && !pBlade_R->IsPrick())     //�ǂ������h�����ĂȂ����
    {
        if (Input::IsKey(DIK_D))
        {
            transform_.position_.x += 0.01f;
            move_.x += 0.01f;
        }
        if (Input::IsKey(DIK_A))
        {
            transform_.position_.x -= 0.01f;
            move_.x -= 0.01f;
        }
    }
}

//�W�����v�Ɨ���
void Scissors::JumpAndFall()
{
    HP* pHP = (HP*)FindObject("HP");

    //�ǂ������h�����ĂȂ����
    if (!pBlade_L->IsPrick() && !pBlade_R->IsPrick())
    {
        //����
        transform_.position_.x += move_.x;
        transform_.position_.y += move_.y;
        transform_.position_.z += move_.z;

        //�d��
        move_.y -= GLAVITY;

        //���n�n�_�̍���
        Global::JumpEnd = transform_.position_.y;
    }

    //�ǂ������h�����Ă���
    else
    {
        //�������~�߂�
        move_.x = 0;
        move_.y = 0;
        move_.z = 0;

        if (Calc)
        {
            //���݂�HP���v�Z
            pHP->HPCalc();
            Calc = false;
        }


        //�ǂ��ǂ�����SPACE�̓��͂�ς���
        if (jumpDirection_.x == 1 || jumpDirection_.x == -1)
        {
            //�ǂȂ璷�����Ŕ����Ȃ�
            if (Input::IsKeyDown(DIK_SPACE))
            {
                //�n�ʂ̖@����肿����Ə�����ɃW�����v
                move_.x = jumpDirection_.x * 0.2f;
                move_.y = jumpDirection_.y * 0.2f + 0.2f;
                move_.z = jumpDirection_.z * 0.2f;

                //�����łP�񓮂����Ă����Ȃ��ƁA���̃t���[���ł��h�������܂܂Ŕ�ׂȂ�
                transform_.position_.x += move_.x;
                transform_.position_.y += move_.y;
                transform_.position_.z += move_.z;

                //�������񔲂�
                pBlade_L->isPrick = false;
                pBlade_R->isPrick = false;

                //�W�����v�̏��߂̍���
                Global::JumpStart = transform_.position_.y;
                Calc = true;

            }
        }
        //�ǂł͂Ȃ��Ȃ璷�����Ői�߂�
        else if (Input::IsKey(DIK_SPACE))
        {
            //�n�ʂ̖@����肿����Ə�����ɃW�����v
            move_.x = jumpDirection_.x * 0.2f;
            move_.y = jumpDirection_.y * 0.2f + 0.1f;
            move_.z = jumpDirection_.z * 0.2f;

            //�����łP�񓮂����Ă����Ȃ��ƁA���̃t���[���ł��h�������܂܂Ŕ�ׂȂ�
            transform_.position_.x += move_.x;
            transform_.position_.y += move_.y;
            transform_.position_.z += move_.z;

            //�������񔲂�
            pBlade_L->isPrick = false;
            pBlade_R->isPrick = false;

            //�W�����v�̏��߂̍���
            Global::JumpStart = transform_.position_.y;
            Calc = true;

        }
       


        //��]���x��ݒ�
        RotateMax();
    }
}

//�`��
void Scissors::Draw()
{
}

//�J��
void Scissors::Release()
{
}

//����
void Scissors::Reflection()
{
    int cnt = 0;

    while (true)
    {
        //if (cnt >= 3) break;

        // �@ x��1�t���[���O�̈ʒu�ɖ߂�
        transform_.position_.x -= move_.x;

        // �A �ēx�����蔻����s�� Y�̃`�F�b�N
        if (pBlade_L->pStage->IsHit(pBlade_L->collider, GetWorldMatrix()) ||
            pBlade_R->pStage->IsHit(pBlade_R->collider, GetWorldMatrix()))
        {
            // �B x���ړ���̏�Ԃɖ߂���
            //    y��1�t���[���O�̈ʒu�ɂ��� 
            transform_.position_.x += move_.x;
            transform_.position_.y -= move_.y;
        }
        // �Ԃ����Ă��Ȃ��Ȃ�I���
        else {
            move_.x = 0;
            break;
        }

        // �C �ēx�����蔻����s��
        if (pBlade_L->pStage->IsHit(pBlade_L->collider, GetWorldMatrix()) ||
            pBlade_R->pStage->IsHit(pBlade_R->collider, GetWorldMatrix()))
        {
            // �D X��Y��1�t���[���O�ɖ߂�
            transform_.position_.x -= move_.x;

            move_.x = 0;
            move_.y = 0;
        }
        // �Ԃ����Ă��Ȃ��Ȃ�I���
        else{
            move_.y = 0;
            break;
        }
        cnt++;
    }
}

//���݈ʒu�𑗂�
void Scissors::SetPosition()
{
    Global global;
    float transX = transform_.position_.x;
    float transY = transform_.position_.y;
    float transZ = transform_.position_.z;

    global.SetTransPos_X(transX);
    global.SetTransPos_Y(transY);
    global.SetTransPos_Z(transZ);
}

//��]���x�����߂�v�Z
void Scissors::RotateMax()
{
    //���C�̃X�^�[�g�ʒu�ƕ��������߂�
    RayCastData data;
    data.start = transform_.position_;
    data.dir.x = nowPivotPoint_.x - transform_.position_.x;
    data.dir.y = nowPivotPoint_.y - transform_.position_.y;
    data.dir.z = nowPivotPoint_.z - transform_.position_.z;

    //��]�̊p�x�̌v�Z������
    XMVECTOR normal = XMLoadFloat3(&jumpDirection_);     //XMFLOAT3 �� XMVECTOR
    XMMATRIX Rotmat = XMMatrixRotationZ(45.5f);          //�@����]�p�̉�]�s��
    normal = XMVector3TransformCoord(normal, Rotmat);    //normal��Rotmat��������
    normal = XMVector3Normalize(normal);                 //normal�𐳋K��
    XMVECTOR dir = XMLoadFloat3(&data.dir);              //���C�̃x�N�g���𐳋K��

    //���ς��g���Ė@���ƃ��C�̊p�x�����߂�
    XMVECTOR Vdot = XMVector3Dot(normal, -dir);
    XMFLOAT3 Fdot;
    XMStoreFloat3(&Fdot, Vdot);
    float angle = acos(Fdot.y);
    AnglePass_ = XMConvertToDegrees(angle);
}

//���X�^�[�g
void Scissors::Restart()
{
    move_ = XMFLOAT3(0, 0, 0);
    transform_.position_ = Global::InitPos;
    transform_.rotate_ = Global::InitRot;
    Global::HP = Global::MAXHP;
    pBlade_L->SetRotateZ(0);
    pBlade_R->SetRotateZ(90);
}



