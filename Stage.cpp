#include "Stage.h"
#include "Engine/Model.h"

//�R���X�g���N�^
Stage::Stage(GameObject* parent)
    :GameObject(parent, "Stage"),StageModel_(-1)
{
}

//�f�X�g���N�^
Stage::~Stage()
{
}

//������
void Stage::Initialize()
{
    //���E���]
    transform_.rotate_.y = 180;

    //�\������X�e�[�W
    switch (Global::Select)
    {
    case 0: Stage1(); break;
    case 1: Stage2(); break;
    }

}

//�X�V
void Stage::Update()
{
}

//�`��
void Stage::Draw()
{
    Model::SetTransform(StageModel_, transform_);
    Model::Draw(StageModel_);
}

//�J��
void Stage::Release()
{
    StageModel_ = -1;
}

// �����̓_�̈ʒu���X�e�[�W�ɓ������Ă邩�`�F�b�N
bool Stage::IsHit(XMFLOAT3 position)
{
    //�S�ẴR���C�_�[�ƃ`�F�b�N����
    for (int i = 0; i < colliders_.size(); i++)
    {
        //���p�`�Ɠ_�̓����蔻�肪true�Ȃ�
        if (colliders_[i].Hit(position))
        {
            //�X�e�[�W�ɓ������Ă�
            return true;
        }
    }

    //�������ĂȂ�
    return false;
}

bool Stage::IsHit(PolygonCollider target, XMMATRIX world)
{
    //�S�ẴR���C�_�[�ƃ`�F�b�N����
    for (int i = 0; i < colliders_.size(); i++)
    {
        if (colliders_[i].Hit(&target, world))
        {
            //�������Ă�
            return true;
        }
    }

    //�������ĂȂ�
    return false;
}

void Stage::GetNormal(XMFLOAT3 p1, XMFLOAT3 p2, XMFLOAT3* normal, XMFLOAT3* hitPoint)
{
    //�S�ẴR���C�_�[�ƃ`�F�b�N����
    for (int i = 0; i < colliders_.size(); i++)
    {
        if (colliders_[i].GetNormal(p1, p2, normal, hitPoint))
        {
            break;
        }
    }
}

//Stage1�̐ݒ�
void Stage::Stage1()
{
    float startX = 2;
    float startY = 0;
    float goalX  = 55;
    float goalY  = 4;

    StageModel_ = Model::Load("SuccessModel/stage1.fbx");

    //�R���C�_�[
    // ���̒n�`�̖ʂ̒��_������
    PolygonCollider pc1, pc2, pc3, pc4, pc5, pc6,
                    pc7, pc8, pc9, pc10, pc11, pc12;

    pc1.AddPoint(-5, 7);
    pc1.AddPoint(-4, 7);
    pc1.AddPoint(-4, -1);
    pc1.AddPoint(-5, -1);
    colliders_.push_back(pc1);

    pc2.AddPoint(-4, 0);
    pc2.AddPoint(15, 0);
    pc2.AddPoint(15, -1);
    pc2.AddPoint(-4, -1);
    colliders_.push_back(pc2);

    pc3.AddPoint(14.7f, 0);
    pc3.AddPoint(19.37f, 1.68f);
    pc3.AddPoint(19.71f, 0.74f);
    pc3.AddPoint(15.02, -0.97f);
    colliders_.push_back(pc3);

    pc4.AddPoint(19.37f, 1.68f);
    pc4.AddPoint(24.07f, -0.04f);
    pc4.AddPoint(23.73f, -0.98f);
    pc4.AddPoint(19.03f, 0.73f);
    colliders_.push_back(pc4);

    pc5.AddPoint(23.75f, 0);
    pc5.AddPoint(38, 0);
    pc5.AddPoint(38, -1);
    pc5.AddPoint(23.75f, -1);
    colliders_.push_back(pc5);

    pc6.AddPoint(38, 8);
    pc6.AddPoint(39, 8);
    pc6.AddPoint(39, -1);
    pc6.AddPoint(38, -1);
    colliders_.push_back(pc6);

    pc7.AddPoint(33, 12.5f);
    pc7.AddPoint(34, 12.5f);
    pc7.AddPoint(34, 3.5f);
    pc7.AddPoint(33, 3.5f);
    colliders_.push_back(pc7);

    pc8.AddPoint(39, 8);
    pc8.AddPoint(47, 8);
    pc8.AddPoint(47, 7);
    pc8.AddPoint(39, 7);
    colliders_.push_back(pc8);


    pc9.AddPoint(40, 8);
    pc9.AddPoint(47.5f, 8);
    pc9.AddPoint(47.5f, 7);
    pc9.AddPoint(47, 7);
    colliders_.push_back(pc9);

    pc10.AddPoint(52, 4);
    pc10.AddPoint(53, 4);
    pc10.AddPoint(53, 0);
    pc10.AddPoint(52, 0);
    colliders_.push_back(pc10);


    //�S�[���O
    pc11.AddPoint(49, 5.3f);
    pc11.AddPoint(60, 5.3f);
    pc11.AddPoint(60, 4);
    pc11.AddPoint(49, 4);
    colliders_.push_back(pc11);

    pc12.AddPoint(60, 14);
    pc12.AddPoint(61, 14);
    pc12.AddPoint(61, 4);
    pc12.AddPoint(60, 4);
    colliders_.push_back(pc12);


    //�X�^�[�g�ƃS�[���̐ݒ�
    gl.SetCameraStartX(startX);
    gl.SetCameraStartY(startY);
    gl.SetCameraGoalX(goalX);
    gl.SetCameraGoalY(goalY);
}

//Stage2�̐ݒ�
void Stage::Stage2()
{
    float startX = 2;
    float startY = 0;
    float goalX = 125;
    float goalY = 0.36f;

    StageModel_ = Model::Load("SuccessModel/stage2.fbx");
    assert(StageModel_ >= 0);


    //�R���C�_�[
    // ���̒n�`�̖ʂ̒��_������
    PolygonCollider pc1,  pc2,  pc3,  pc4,  pc5,  pc6,
                    pc7,  pc8,  pc9,  pc10, pc11, pc12,
                    pc13, pc14, pc15, pc16, pc17, pc18,
                    pc19, pc20, pc21, pc22, pc23, pc24,
                    pc25, pc26, pc27, pc28, pc29, pc30;

    //���̕�
    pc1.AddPoint(-10  ,   28);
    pc1.AddPoint(-3.7f  ,   28);
    pc1.AddPoint(-3.7f  , -2);
    pc1.AddPoint(-10  , -2);
    colliders_.push_back(pc1);

    //�ŏ��̏�
    pc2.AddPoint(-5 ,  0);
    pc2.AddPoint(42.5f, 0);
    pc2.AddPoint(42.5f,  -2);
    pc2.AddPoint(-5,  -2);
    colliders_.push_back(pc2);

    //����������
    pc3.AddPoint(4.4f , 1.5f);
    pc3.AddPoint(16, 1.5f);
    pc3.AddPoint(16, 0);
    pc3.AddPoint(4.4f , 0);
    colliders_.push_back(pc3);

    //��(��)
    pc4.AddPoint(15.5f,4.8f);
    pc4.AddPoint(18.8f,4.8f);
    pc4.AddPoint(18.8f,0);
    pc4.AddPoint(15.5f,0);
    colliders_.push_back(pc4);

    //�V��(�n��)
    pc5.AddPoint(4.3f, 13.8f);
    pc5.AddPoint(12,13.8f);
    pc5.AddPoint(12,4.4f);
    pc5.AddPoint(4.3f, 4.4f);
    colliders_.push_back(pc5);

    //�ǁi��j
    pc6.AddPoint(15.5f, 15.7f);
    pc6.AddPoint(18.8f, 15.7f);
    pc6.AddPoint(18.8f, 8.3f);
    pc6.AddPoint(15.5f, 8.3f);
    colliders_.push_back(pc6);

    //�󒆔�ѐ�1
    pc7.AddPoint(1.93f, 15.2f);
    pc7.AddPoint(2.38f, 15.2f);
    pc7.AddPoint(2.38f, 14.75f);
    pc7.AddPoint(1.93f, 14.75f);
    colliders_.push_back(pc7);

    //�󒆔�ѐ�2
    pc8.AddPoint(0.3f,16.1f);
    pc8.AddPoint(0.74f, 16.1f);
    pc8.AddPoint(0.74f,15.65f);
    pc8.AddPoint(0.3f, 15.65f);
    colliders_.push_back(pc8);

    //����1
    pc9.AddPoint(24.0f, 2.0f);
    pc9.AddPoint(27.45f, 2.0f);
    pc9.AddPoint(27.45f, -1.5f);
    pc9.AddPoint(24.0f, -1.5f);
    colliders_.push_back(pc9);

    //����2
    pc10.AddPoint(30.0f, 3.0f);
    pc10.AddPoint(33.45f,3.0f);
    pc10.AddPoint(33.45f, -1.5f);
    pc10.AddPoint(30.0f, -1.5f);
    colliders_.push_back(pc10);

    //��2
    pc11.AddPoint(45.5f, 0);
    pc11.AddPoint(66.5f, 0);
    pc11.AddPoint(66.5f, -2);
    pc11.AddPoint(45.5f,  -2);
    colliders_.push_back(pc11);

    //������1
    pc12.AddPoint(51.52f, 1.65f);
    pc12.AddPoint(54.22f, 1.65f);
    pc12.AddPoint(54.22f, 1.05f);
    pc12.AddPoint(51.52f, 1.05f);
    colliders_.push_back(pc12);

    //������2
    pc13.AddPoint(56.3f, 3);
    pc13.AddPoint(59.23f, 3);
    pc13.AddPoint(59.23f, 2.4f);
    pc13.AddPoint(56.3f, 2.4f);
    colliders_.push_back(pc13);

    //������3
    pc14.AddPoint(61.32f, 3.75f);
    pc14.AddPoint(63.96f, 3.75f);
    pc14.AddPoint(63.96f, 3.31f);
    pc14.AddPoint(61.32f, 3.31f);
    colliders_.push_back(pc14);
    
    //������4
    pc15.AddPoint(65.41f, 4.61f);
    pc15.AddPoint(68.05f, 4.61f);
    pc15.AddPoint(68.05f, 4.18f);
    pc15.AddPoint(65.41f, 4.61f);
    colliders_.push_back(pc15);

    //������5(��)
    pc16.AddPoint(70, 5.65f);
    pc16.AddPoint(84.58f, 5.65f);
    pc16.AddPoint(84.58f, 5.11f);
    pc16.AddPoint(70, 5.11f);
    colliders_.push_back(pc16);

    //������6
    pc17.AddPoint(86.64f, 4.56f);
    pc17.AddPoint(89.34f, 4.56f);
    pc17.AddPoint(89.34f, 3.97f);
    pc17.AddPoint(86.64f, 3.97f);
    colliders_.push_back(pc17);

    //���я�1
    pc18.AddPoint(68.13f,  0.29f);
    pc18.AddPoint(71.43f,  0.29f);
    pc18.AddPoint(71.43f, -1.96f);
    pc18.AddPoint(68.13f, -1.96f);
    colliders_.push_back(pc18);

    //���я�2
    pc19.AddPoint(73.83f,  0.29f);
    pc19.AddPoint(77.13f,  0.29f);
    pc19.AddPoint(77.13f, -1.96f);
    pc19.AddPoint(73.83f, -1.96f);
    colliders_.push_back(pc19);

    //��3
    pc20.AddPoint(80.78f,  0.14f);
    pc20.AddPoint(91.88f,  0.14f);
    pc20.AddPoint(91.88f, -2.11f);
    pc20.AddPoint(80.78f, -2.11f);
    colliders_.push_back(pc20);



    //��4
    pc21.AddPoint(94.6f,    0.36f);
    pc21.AddPoint(109.46f,  0.36f);
    pc21.AddPoint(109.46f, -2.31f);
    pc21.AddPoint(94.6f,   -2.31f);
    colliders_.push_back(pc21);

    //�o�菰1
    pc22.AddPoint(101,  2);
    pc22.AddPoint(103.4f,  2);
    pc22.AddPoint(103.4f, 1.4f);
    pc22.AddPoint(101, 1.4f);
    colliders_.push_back(pc22);

    //�o�菰2
    pc23.AddPoint(105.55f, 3);
    pc23.AddPoint(107.96f, 3);
    pc23.AddPoint(107.96f, 2.42f);
    pc23.AddPoint(105.55f, 2.42f);
    colliders_.push_back(pc23);

    //�o�菰3
    pc24.AddPoint(103.46f, 6.09f);
    pc24.AddPoint(105.81f, 5.67f);
    pc24.AddPoint(105.7f,  5.07f);
    pc24.AddPoint(103.34f, 5.51f);
    colliders_.push_back(pc24);

    //�o�菰4
    pc25.AddPoint(105.78f, 10.39f);
    pc25.AddPoint(106.41f, 10.39f);
    pc25.AddPoint(106.42f, 8.f);
    pc25.AddPoint(105.78f, 8.f);
    colliders_.push_back(pc25);

    //��1
    pc26.AddPoint(109.38f, 8.1f);
    pc26.AddPoint(111.48f, 8.1f);
    pc26.AddPoint(111.48f, -2.3f);
    pc26.AddPoint(109.38f, -2.3f);
    colliders_.push_back(pc26);

    //��2
    pc27.AddPoint(115.48f, 7);
    pc27.AddPoint(119.23f, 7);
    pc27.AddPoint(119.23f, -2.33f);
    pc27.AddPoint(115.48f, -2.33f);
    colliders_.push_back(pc27);

    //�Ǔ���
    pc28.AddPoint(111, -1.43f);
    pc28.AddPoint(116, -1.43f);
    pc28.AddPoint(116, -2.36f);
    pc28.AddPoint(111, -2.36f);
    colliders_.push_back(pc28);

    //��5
    pc29.AddPoint(119, 0.36f);
    pc29.AddPoint(133, 0.36f);
    pc29.AddPoint(133, -2.32f);
    pc29.AddPoint(119, -2.32f);
    colliders_.push_back(pc29);

    //�S�[����
    pc30.AddPoint(132.25f, 17.5f);
    pc30.AddPoint(135.8f, 17.5f);
    pc30.AddPoint(135.8f, -2.32f);
    pc30.AddPoint(132.25f, -2.32f);
    colliders_.push_back(pc30);


    //�X�^�[�g�ƃS�[���̐ݒ�
    gl.SetCameraStartX(startX);
    gl.SetCameraStartY(startY);
    gl.SetCameraGoalX(goalX);
    gl.SetCameraGoalY(goalY);
}

