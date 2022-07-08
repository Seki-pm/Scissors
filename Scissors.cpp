#include "Scissors.h"

#define NormalJumpPower 0.1f;
#define SinkJumpPower 0.001f;
#define SinkTimer 360;

//�R���X�g���N�^
Scissors::Scissors(GameObject* parent)
    :GameObject(parent, "Scissors"), 
    jumpDirection_(XMFLOAT3(0,0,0)),nowPivotPoint_(XMFLOAT3(0,0,0)), move_(XMFLOAT3(0, 0, 0)),
    pBlade_L(nullptr), pBlade_R(nullptr),pStage_(nullptr),
    FallFlg(true),     CalcFlg(false),   SoundFlg(false),  IsRepel(false),    IsSink(false),
    CountDown(0),      MoveY(0),         powerX(0),        powerY(0),         TransPos_Y(0),
    AnglePass_(0.0f),  Key(0),           IsJump(true),
    Timer_(360),       JumpPower(0.1f),  GLAVITY(0.03f)
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

    //RBlade��45���X����
    pBlade_R->SetRotateZ(45);

    //�����ʒu
    transform_.position_ = Global::InitPos;

    //�A�C�e���擾�p�̃R���C�_�[��ݒ�
    SphereCollider* collision =
        new SphereCollider(XMFLOAT3(0, 0, 0), 0.6f);
    AddCollider(collision);

    CurrentHP = Global::MAXHP;
}

//�X�V
void Scissors::Update()
{

    if (!Global::GameOver && !Global::Pause)
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
    }
 

    //�X�^�[�g�����蒼���i���g���C�j
    if (Input::IsKeyDown(DIK_R))
    {
        Restart();
    }



    //���������� || ���񂾂�
    if (transform_.position_.y <= -8 && FallFlg
        || 60 >= Timer_)
    {
        move_ = XMFLOAT3(0, 0, 0);
        Global::GameOver = true;
        Global::IsGameOver = true;
        FallFlg = false;
        Global::SinkFlg = false;
    }

    //���M�~�b�N
    RepelMove();  //�͂���
    SinkMove();   //����
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

    //170�x�ȏ�܂���2�x�����Ȃ���ǂ�
    if (XMConvertToDegrees(ang) > 170|| XMConvertToDegrees(ang) < 2)   
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
        if (AnglePass_ < 150)
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
    if (!pBlade_L->IsPrick() && !pBlade_R->IsPrick() && IsJump)     //�ǂ������h�����ĂȂ����
    {
        if (Input::IsKey(DIK_D))
        {
            Key = 1;
            transform_.position_.x += 0.01f;
            move_.x += 0.01f;
        }
        if (Input::IsKey(DIK_A))
        {
            Key = -1;
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

        //���n��
        SoundFlg = true;
    }

    //�ǂ������h�����Ă���
    else
    {
        //�W�����v����������(�͂��������̕���)
        if (move_.x < 0) Key = 1;        //�E�ɓ����Ă��鎞�͍���
        else if(move_.x > 0)  Key = -1;  //���ɓ����Ă��鎞�͉E�ց@�e��

        //�������~�߂�
        move_.x = 0;
        move_.y = 0;
        move_.z = 0;

        if (CalcFlg)
        {
            //���݂�HP���v�Z
            pHP->HPCalc();
            CalcFlg = false;
        }

        if (SoundFlg)
        {
            SoundFlg = false;
            Landing();
        }


        //�ǂ��ǂ�����SPACE�̓��͂�ς���
        if (jumpDirection_.x == 1 || jumpDirection_.x == -1)
        {
            //�ǂȂ璷�����Ŕ����Ȃ�
            if (Input::IsKeyDown(DIK_SPACE) && IsJump)
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
                CalcFlg = true;

            }
        }
        //�ǂł͂Ȃ��Ȃ璷�����Ői�߂�
        else if (Input::IsKey(DIK_SPACE) && IsJump)
        {
            //�n�ʂ̖@����肿����Ə�����ɃW�����v
            move_.x = jumpDirection_.x * 0.2f;
            move_.y = jumpDirection_.y * 0.2f + JumpPower;
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
            CalcFlg = true;

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
    float value = 0.1f;

    //transform_.position_.x -= move_.x;
    //transform_.position_.y -= move_.y;
    //move_.x *= -0.3f;
    //move_.y *= -0.3f;
    //move_.x = 0;
    //move_.y = 0;

    while (true)
    {
        // �@ x��1�t���[���O�̈ʒu�ɖ߂�
        transform_.position_.x -= move_.x;

        // �A �ēx�����蔻����s�� Y�����������Ă��邩�̃`�F�b�N
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
            move_.y = 0;
            break;
       }
        // �C �ēx�����蔻����s��  X�����������Ă��邩�̃`�F�b�N
        if (pBlade_L->pStage->IsHit(pBlade_L->collider, GetWorldMatrix()) ||
            pBlade_R->pStage->IsHit(pBlade_R->collider, GetWorldMatrix()))
        {
            // �D X��Y��1�t���[���O�ɖ߂�
            transform_.position_.x -= move_.x;
        }
        // �Ԃ����Ă��Ȃ��Ȃ�I���
        else{
            move_.x = 0;
            move_.y = 0;
            break;
        }
        cnt++;

        //���肪20��ȏゾ��
        if (cnt >= 20)
        {
            //�����I�ɒl������Scissors�𓮂���(�l�ݖh�~�΍�)
            move_.x += value;
            move_.y -= value;
        }

        //�Ԃ����Ă����HP�����炷(�l�ݖh�~�΍�)
        CurrentHP--;
    }
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
    XMVECTOR normal = XMLoadFloat3(&jumpDirection_);     //XMFLOAT3 �� XMVECTOR(�@��)
    XMMATRIX Rotmat = XMMatrixRotationZ(45.5f);          //�@����]�p�̉�]�s��
    normal = XMVector3TransformCoord(normal, Rotmat);    //normal��Rotmat��������
    normal = XMVector3Normalize(normal);                 //normal�𐳋K��
    XMVECTOR dir = XMLoadFloat3(&data.dir);              //XMFLOAT3 �� XMVECTOR(���C�̃x�N�g��)
    dir = XMVector3Normalize(dir);                       //���C�̃x�N�g���𐳋K��

    //���ς��g���Ė@���ƃ��C�̊p�x�����߂�
    XMVECTOR Vdot = XMVector3Dot(normal, -dir);
    XMFLOAT3 Fdot;
    XMStoreFloat3(&Fdot, Vdot);
    float angle = acos(Fdot.y);              //acos�Ń��W�A���p�x�����߂�
    AnglePass_ = XMConvertToDegrees(angle);  //���W�A�� �� �x
}

//���X�^�[�g
void Scissors::Restart()
{
    move_ = XMFLOAT3(0, 0, 0);
    transform_.position_ = Global::InitPos;
    transform_.rotate_ = Global::InitRot;

    Global::JumpStart = 0;
    Global::JumpEnd = 0;
    Global::GameOver = false;
    Global::IsGameOver = false;
    Global::ItemReDraw = true;
    CurrentHP = Global::MAXHP;
    pBlade_L->SetRotateZ(0);
    pBlade_R->SetRotateZ(90);
    pBlade_L->isPrick = false;
    pBlade_R->isPrick = false;
    FallFlg = true;
}

//�e���ꂽ���̓���
void Scissors::RepelMove()
{
    //�t���O����������
    if (Global::RepelFlg)
    {
        if (!IsRepel)
        { 
            //�e���l������
            powerX = pStage_->Repel().x;
            powerY = pStage_->Repel().y;

            IsRepel = true;
        }
        else
        {
            //�ǂ��������Ă��邱�Ƃɂ���(���������邽��)
            pBlade_L->isPrick = false;
            pBlade_R->isPrick = false;

            if (jumpDirection_.x == 1 || jumpDirection_.x == -1)
            {
                transform_.position_.x += powerX * jumpDirection_.x;       //�e��
                transform_.position_.y -= powerY;             //powerY������
            }
            else
            {
                transform_.position_.x += powerX * Key;       //Key�̕����֒e��
                transform_.position_.y += powerY;             //powerY�����
            }

        }
    }
    else
    {
        IsRepel = false;
    }
}

//���ޓ���
void Scissors::SinkMove()
{
    SetCountDown(CountDown);

    //�t���O����������
    if (Global::SinkFlg)
    {
        Timer_--;
        CountDown = Timer_ / 60;

        if (!IsSink)
        {
            //���ޒl������
            MoveY = pStage_->Sink().y;
            IsSink = true;
        }
        else
        {
            //MoveY�̒l������ł���
            transform_.position_.y += MoveY;
            JumpPower = SinkJumpPower;
        }

    }
    else
    {
        //�ŏ��ɖ߂�
        JumpPower = NormalJumpPower;
        IsSink = false;
        Timer_ = SinkTimer;
    }
}

//�����𗬂�
void Scissors::Landing()
{
    switch(Global::SelectStage)
    {
    case STAGE_NUMBER_1:
        //���̒n��
        if (jumpDirection_.x == 0 && nowPivotPoint_.y <= 7)
        {
            Audio::Play(Stage1_Sound::St1_Glass);
        }
        //�ǂ̎�
        else if(jumpDirection_.x == 1 || jumpDirection_.x == -1)
        {
            break;
        }
        //����ȊO
        else
        {
            Audio::Play(Stage1_Sound::St1_Wood);
        }
        break;

    case STAGE_NUMBER_2:
        //�����̒n��
        if (nowPivotPoint_.y >= 1.3f && nowPivotPoint_.x >= 23 && nowPivotPoint_.x <= 94.5f
            || nowPivotPoint_.x > 94.5f)
        {
            Audio::Play(Stage2_Sound::St2_Gravel);
        }
        //����ȊO
        else
        {
            Audio::Play(Stage2_Sound::St2_Stone);
        }
        break;
    case STAGE_NUMBER_3:
        //�e���n��
        if (Global::RepelFlg)
        {
            Audio::Play(Stage3_Sound::St3_Iron);
        }
        //���ޒn��
        else if (Global::SinkFlg)
        {
            Audio::Play(Stage3_Sound::St3_Sand);
        }
        //���ʂ̒n��(�O��)
        else if (nowPivotPoint_.x <= 74)
        {
            Audio::Play(Stage3_Sound::St3_Volcano_Sand);
            Audio::Stop(Stage3_Sound::St3_Sand);
        }
        //���ʂ̒n��(�㔼)
        else
        {
            Audio::Play(Stage3_Sound::St3_Volcano);
            Audio::Stop(Stage3_Sound::St3_Sand);
        }

        break;
    }
}
