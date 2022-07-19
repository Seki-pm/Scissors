#include "HP.h"
#include "Scissors.h"

//コンストラクタ
HP::HP(GameObject* parent)
    :GameObject(parent, "HP"),
     pGauge_(nullptr), pScissors_(nullptr),
     GaugeImage_(INITIAL_ERROR_VALUE), 
     GaugeFrameImage_(INITIAL_ERROR_VALUE)
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
    FrameTrans.position_ = FRAME_POS;
    Image::SetTransform(GaugeFrameImage_, FrameTrans);

    pScissors_ = (Scissors*)FindObject("Scissors");
}

//更新
void HP::Update()
{
}

//描画
void HP::Draw()
{
    pGauge_->Draw(pScissors_->CurrentHP, HP_IMAGE_POS.x, HP_IMAGE_POS.y, GaugeImage_);
    Image::Draw(GaugeFrameImage_);
}

//開放
void HP::Release()
{
    GaugeImage_ = INITIAL_ERROR_VALUE;
    GaugeFrameImage_ = INITIAL_ERROR_VALUE;
}

//HP計算
void HP::HPCalc()
{
    float JS = pScissors_->JumpStart;  //ジャンプ開始位置
    float JE = pScissors_->JumpEnd;    //ジャンプ着地位置
    float ND = NORMAL_DAMAGE;          //ダメージ量

    //高いところから降りたら
    if (JS - JE > HAS_DAMAGE)
    {
        pScissors_->CurrentHP -= (JS - JE + ND) * 2;
    }

    //平面移動or上った
    if (JS - JE <= HAS_DAMAGE)
    {
        pScissors_->CurrentHP -= ND;
    }

    //ゲームオーバー判定
    if (pScissors_->CurrentHP <= 0)
    {
        Global::IsGameOver = true;
        Global::GameOver = true;
    }
}
