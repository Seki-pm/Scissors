#include "HP.h"

//コンストラクタ
HP::HP(GameObject* parent)
    :GameObject(parent, "HP"),
    pGauge_(nullptr),GaugeImage_(-1), GaugeFrameImage_(-1)
{
}

//デストラクタ
HP::~HP()
{
}

//初期化
void HP::Initialize()
{
    //ゲージ
    GaugeImage_ = Image::Load("Image/StageScene/HP.png");
    assert(GaugeImage_ >= 0);

    //ゲージフレーム
    GaugeFrameImage_ = Image::Load("Image/StageScene/GaugeFrame.png");
    assert(GaugeFrameImage_ >= 0);
    FrameTrans.position_ = XMFLOAT3(-0.59f, 0.88f, 0);
    Image::SetTransform(GaugeFrameImage_, FrameTrans);

}

//更新
void HP::Update()
{
}

//描画
void HP::Draw()
{
    pGauge_->Draw(Global::HP, -0.99f, 0.85f, GaugeImage_);
    Image::Draw(GaugeFrameImage_);
}

//開放
void HP::Release()
{
    GaugeImage_ = -1;
    GaugeFrameImage_ = -1;
}

//HP計算
void HP::HPCalc()
{
    float JS = Global::JumpStart;
    float JE = Global::JumpEnd;
    float ND = Global::NORMAL_DAMAGE;

    //高いところから降りたら
    if (JS - JE > 0.5f)
    {
        Global::HP -= (JS - JE + ND) * 2;
    }

    //平面移動or上った
    if (JS - JE <= 0.5f)
    {
        Global::HP -= ND;
    }

    //ゲームオーバー判定
    if (Global::HP <= 0)
    {
        Global::IsGameOver = true;
        Global::GameOver = true;
    }
}
