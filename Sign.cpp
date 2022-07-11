#include "Sign.h"


#define Sign1_Pos XMFLOAT3( 2, 0, 0)
#define Sign2_Pos XMFLOAT3( 8, 0, 0)
#define Sign3_Pos XMFLOAT3(11, 0, 0)
#define Sign4_Pos XMFLOAT3(14, 0, 0)
#define Sign5_Pos XMFLOAT3(28, 0, 0)
#define Sign6_Pos XMFLOAT3(31, 0, 0)

#define Sign_Size XMFLOAT3(1.7f,1.7f,1.7f)

#define Tutorial_Pos XMFLOAT3(0,   0.65f, 0)
#define Tutorial_Sca XMFLOAT3(0.5f, 0.5f, 0.5f)

//コンストラクタ
Sign::Sign(GameObject* parent)
    :GameObject(parent, "Sign"),
    Tutorial_(-1), Tutorial2_(-1)
{
    for (int i = 1; i < Tips_MAX; i++)
    {
        TipsModel_[i] = -1;
    }
}

//デストラクタ
Sign::~Sign()
{
}

//初期化
void Sign::Initialize()
{
    //===================== 看板モデルのロード ==============================
    //方向を決める...ジャンプ...
    TipsModel_[Tips_1] = Model::Load("Model/InGameObject/Sign1.fbx");
    assert(TipsModel_[Tips_1] >= 0);
    SignTrans.position_ = Sign1_Pos;
    SignTrans.scale_ = Sign_Size;
    Model::SetTransform(TipsModel_[Tips_1], SignTrans);

    //刃が地面に刺さってる時は,,,
    TipsModel_[Tips_2] = Model::Load("Model/InGameObject/Sign2.fbx");
    assert(TipsModel_[Tips_2] >= 0);
    SignTrans2.position_ = Sign2_Pos;
    SignTrans2.scale_ = Sign_Size;
    Model::SetTransform(TipsModel_[Tips_2], SignTrans2);

    //刃が地面に着くたびに...
    TipsModel_[Tips_3] = Model::Load("Model/InGameObject/Sign3.fbx");
    assert(TipsModel_[Tips_3] >= 0);
    auto SignTrans3 = Transform();
    SignTrans3.position_ = Sign3_Pos;
    SignTrans3.scale_ = Sign_Size;
    Model::SetTransform(TipsModel_[Tips_3], SignTrans3);

    //[Esc]を押すと...
    TipsModel_[Tips_4] = Model::Load("Model/InGameObject/Sign4.fbx");
    assert(TipsModel_[Tips_4] >= 0);
    auto SignTrans4 = Transform();
    SignTrans4.position_ = Sign4_Pos;
    SignTrans4.scale_ = Sign_Size;
    Model::SetTransform(TipsModel_[Tips_4], SignTrans4);


    //壁に刃を向けてジャンプすると...
    TipsModel_[Tips_5] = Model::Load("Model/InGameObject/Sign5.fbx");
    assert(TipsModel_[Tips_5] >= 0);
    SignTrans5.position_ = Sign5_Pos;
    SignTrans5.scale_ = Sign_Size;
    Model::SetTransform(TipsModel_[Tips_5], SignTrans5);


    //壁でも地面と同じ様に...
    TipsModel_[Tips_6] = Model::Load("Model/InGameObject/Sign6.fbx");
    assert(TipsModel_[Tips_6] >= 0);
    auto SignTrans6 = Transform();
    SignTrans6.position_ = Sign6_Pos;
    SignTrans6.scale_ = Sign_Size;
    Model::SetTransform(TipsModel_[Tips_6], SignTrans6);


    //====================  チュートリアル画像  =======================
    Tutorial_ = Image::Load("Image/StageScene/Tutorial.png");
    assert(Tutorial_ >= 0);
    auto TutorialTrans = Transform();
    TutorialTrans.position_ = Tutorial_Pos;
    TutorialTrans.scale_ = Tutorial_Sca;
    Image::SetTransform(Tutorial_, TutorialTrans);


    Tutorial2_ = Image::Load("Image/StageScene/Tutorial2.png");
    assert(Tutorial2_ >= 0);
    Image::SetTransform(Tutorial2_, TutorialTrans);


}

//更新
void Sign::Update()
{
}

//描画
void Sign::Draw()
{
    //看板の描画
    for (int i = 1; i < Tips_MAX; i++)
    {
        Model::Draw(TipsModel_[i]);
    }
    

    //条件付きでチュートリアルの描画
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

//開放
void Sign::Release()
{
    for (int i = 1; i < Tips_MAX; i++)
    {
        TipsModel_[i] = -1;
    }
    Tutorial_ = -1;
    Tutorial2_ = -1;
}