#include "Sign.h"

//コンストラクタ
Sign::Sign(GameObject* parent)
    :GameObject(parent, "Sign"),
    size_(1.7f),Tutorial_(-1), Tutorial2_(-1)
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
    SignTrans.position_ = XMFLOAT3(2, 0, 0);
    SignTrans.scale_ = XMFLOAT3(size_, size_, size_);
    Model::SetTransform(TipsModel_[Tips_1], SignTrans);

    //刃が地面に刺さってる時は,,,
    TipsModel_[Tips_2] = Model::Load("Model/InGameObject/Sign2.fbx");
    assert(TipsModel_[Tips_2] >= 0);
    SignTrans2.position_ = XMFLOAT3(8, 0, 0);
    SignTrans2.scale_ = XMFLOAT3(size_, size_, size_);
    Model::SetTransform(TipsModel_[Tips_2], SignTrans2);

    //刃が地面に着くたびに...
    TipsModel_[Tips_3] = Model::Load("Model/InGameObject/Sign3.fbx");
    assert(TipsModel_[Tips_3] >= 0);
    auto SignTrans3 = Transform();
    SignTrans3.position_ = XMFLOAT3(11, 0, 0);
    SignTrans3.scale_ = XMFLOAT3(size_, size_, size_);
    Model::SetTransform(TipsModel_[Tips_3], SignTrans3);

    //[Esc]を押すと...
    TipsModel_[Tips_4] = Model::Load("Model/InGameObject/Sign4.fbx");
    assert(TipsModel_[Tips_4] >= 0);
    auto SignTrans4 = Transform();
    SignTrans4.position_ = XMFLOAT3(14, 0, 0);
    SignTrans4.scale_ = XMFLOAT3(size_, size_, size_);
    Model::SetTransform(TipsModel_[Tips_4], SignTrans4);


    //壁に刃を向けてジャンプすると...
    TipsModel_[Tips_5] = Model::Load("Model/InGameObject/Sign5.fbx");
    assert(TipsModel_[Tips_5] >= 0);
    SignTrans5.position_ = XMFLOAT3(28, 0, 0);
    SignTrans5.scale_ = XMFLOAT3(size_, size_, size_);
    Model::SetTransform(TipsModel_[Tips_5], SignTrans5);


    //壁でも地面と同じ様に...
    TipsModel_[Tips_6] = Model::Load("Model/InGameObject/Sign6.fbx");
    assert(TipsModel_[Tips_6] >= 0);
    auto SignTrans6 = Transform();
    SignTrans6.position_ = XMFLOAT3(31, 0, 0);
    SignTrans6.scale_ = XMFLOAT3(size_, size_, size_);
    Model::SetTransform(TipsModel_[Tips_6], SignTrans6);


    //====================  チュートリアル画像  =======================
    Tutorial_ = Image::Load("Image/StageScene/Tutorial.png");
    assert(Tutorial_ >= 0);
    auto TutorialTrans = Transform();
    TutorialTrans.position_ = XMFLOAT3(0, 0.65f,0);
    TutorialTrans.scale_ = XMFLOAT3(0.5f, 0.5f, 0.5f);
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
    if (gl.GetTransPos_X() >= SignTrans.position_.x &&
        gl.GetTransPos_X() <= SignTrans2.position_.x)
    {
        Image::Draw(Tutorial_);
    }

    if (gl.GetTransPos_X() >= SignTrans5.position_.x &&
        gl.GetTransPos_X() <= 42 && 
        gl.GetTransPos_Y() <= 4.5f)
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