#include "HP.h"

//コンストラクタ
HP::HP(GameObject* parent)
    :GameObject(parent, "HP"),
    pGauge_(nullptr),GaugeHandle_(-1), GaugeFrame_(-1)
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
    GaugeHandle_ = Image::Load("Image/StageScene/HP.png");
    assert(GaugeHandle_ >= 0);

    //ゲージフレーム
    GaugeFrame_ = Image::Load("Image/StageScene/GaugeFrame.png");
    assert(GaugeFrame_ >= 0);
    FrameTrans.position_ = XMFLOAT3(-0.58f, 0.8f, 0);
    Image::SetTransform(GaugeFrame_, FrameTrans);

}

//更新
void HP::Update()
{
}

//描画
void HP::Draw()
{
    pGauge_->Draw(Global::HP, -0.978f, 0.77f, GaugeHandle_);
    Image::Draw(GaugeFrame_);
}

//開放
void HP::Release()
{
    GaugeHandle_ = -1;
    GaugeFrame_ = -1;
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
