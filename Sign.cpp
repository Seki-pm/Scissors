#include "Sign.h"


#define SIGN1_POS XMFLOAT3( 2, 0, 0)
#define SIGN2_POS XMFLOAT3( 8, 0, 0)
#define SIGN3_POS XMFLOAT3(11, 0, 0)
#define SIGN4_POS XMFLOAT3(14, 0, 0)
#define SIGN5_POS XMFLOAT3(28, 0, 0)
#define SIGN6_POS XMFLOAT3(31, 0, 0)

#define SIGN_SIZE XMFLOAT3(1.7f,1.7f,1.7f)

#define TUTORIAL_POS XMFLOAT3(0,   0.65f, 0)
#define TUTORIAL_SCA XMFLOAT3(0.5f, 0.5f, 0.5f)

//�R���X�g���N�^
Sign::Sign(GameObject* parent)
    :GameObject(parent, "Sign"),
    Tutorial_(-1), Tutorial2_(-1)
{
    for (int i = 1; i < Tips_MAX; i++)
    {
        TipsModel_[i] = -1;
    }
}

//�f�X�g���N�^
Sign::~Sign()
{
}

//������
void Sign::Initialize()
{
    //===================== �Ŕ��f���̃��[�h ==============================
    //���������߂�...�W�����v...
    TipsModel_[Tips_1] = Model::Load("Model/InGameObject/Sign1.fbx");
    assert(TipsModel_[Tips_1] >= 0);
    SignTrans.position_ = SIGN1_POS;
    SignTrans.scale_ = SIGN_SIZE;
    Model::SetTransform(TipsModel_[Tips_1], SignTrans);

    //�n���n�ʂɎh�����Ă鎞��,,,
    TipsModel_[Tips_2] = Model::Load("Model/InGameObject/Sign2.fbx");
    assert(TipsModel_[Tips_2] >= 0);
    SignTrans2.position_ = SIGN2_POS;
    SignTrans2.scale_ = SIGN_SIZE;
    Model::SetTransform(TipsModel_[Tips_2], SignTrans2);

    //�n���n�ʂɒ������т�...
    TipsModel_[Tips_3] = Model::Load("Model/InGameObject/Sign3.fbx");
    assert(TipsModel_[Tips_3] >= 0);
    auto SignTrans3 = Transform();
    SignTrans3.position_ = SIGN3_POS;
    SignTrans3.scale_ = SIGN_SIZE;
    Model::SetTransform(TipsModel_[Tips_3], SignTrans3);

    //[Esc]��������...
    TipsModel_[Tips_4] = Model::Load("Model/InGameObject/Sign4.fbx");
    assert(TipsModel_[Tips_4] >= 0);
    auto SignTrans4 = Transform();
    SignTrans4.position_ = SIGN4_POS;
    SignTrans4.scale_ = SIGN_SIZE;
    Model::SetTransform(TipsModel_[Tips_4], SignTrans4);


    //�ǂɐn�������ăW�����v�����...
    TipsModel_[Tips_5] = Model::Load("Model/InGameObject/Sign5.fbx");
    assert(TipsModel_[Tips_5] >= 0);
    SignTrans5.position_ = SIGN5_POS;
    SignTrans5.scale_ = SIGN_SIZE;
    Model::SetTransform(TipsModel_[Tips_5], SignTrans5);


    //�ǂł��n�ʂƓ����l��...
    TipsModel_[Tips_6] = Model::Load("Model/InGameObject/Sign6.fbx");
    assert(TipsModel_[Tips_6] >= 0);
    auto SignTrans6 = Transform();
    SignTrans6.position_ = SIGN6_POS;
    SignTrans6.scale_ = SIGN_SIZE;
    Model::SetTransform(TipsModel_[Tips_6], SignTrans6);


    //====================  �`���[�g���A���摜  =======================
    Tutorial_ = Image::Load("Image/StageScene/Tutorial.png");
    assert(Tutorial_ >= 0);
    auto TutorialTrans = Transform();
    TutorialTrans.position_ = TUTORIAL_POS;
    TutorialTrans.scale_ = TUTORIAL_SCA;
    Image::SetTransform(Tutorial_, TutorialTrans);


    Tutorial2_ = Image::Load("Image/StageScene/Tutorial2.png");
    assert(Tutorial2_ >= 0);
    Image::SetTransform(Tutorial2_, TutorialTrans);


}

//�X�V
void Sign::Update()
{
}

//�`��
void Sign::Draw()
{
    //�Ŕ̕`��
    for (int i = 1; i < Tips_MAX; i++)
    {
        Model::Draw(TipsModel_[i]);
    }
    

    //�����t���Ń`���[�g���A���̕`��
    if (gl.GetTransPos().x >= SignTrans.position_.x &&
        gl.GetTransPos().x <= SignTrans2.position_.x)
    {
        Image::Draw(Tutorial_);
    }

    if (gl.GetTransPos().x >= SignTrans5.position_.x &&
        gl.GetTransPos().x <= 42 &&
        gl.GetTransPos().y <= 4.5f)
    {
        Image::Draw(Tutorial2_);
    }
}

//�J��
void Sign::Release()
{
    for (int i = 1; i < Tips_MAX; i++)
    {
        TipsModel_[i] = -1;
    }
    Tutorial_ = -1;
    Tutorial2_ = -1;
}