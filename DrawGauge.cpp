#include "DrawGauge.h"

//コンストラクタ
DrawGauge::DrawGauge()
{
}

//デストラクタ
DrawGauge::~DrawGauge()
{
}

//初期化
void DrawGauge::Initialize()
{
}

//描画
void DrawGauge::Draw(int val, float x, float y, int hPict, int maxhp)
{
	Transform trans;

	//出す場所
	trans.position_.x = x;
	trans.position_.y = y;
	trans.scale_ = XMFLOAT3(2.f, 1.3f, 0.96f);

	//画像の幅(%)
	float ImageWidth_ = 512;           //画像の幅
	float w = ImageWidth_ / 100;       //画像幅(1%)
	float width = ImageWidth_ / 200;   //画像幅(0.5%)
	float wid = w * 50;

	//現在のHP(%)
	float hp_    = Global::HP;          //現在のHP
	float Nowhp  = hp_ / maxhp * 100;   //現在のHP(%)


	//画像幅に現在HPの割合をかける
	float image = width * Nowhp + wid;
	//float image = w * Nowhp;

	float X = image - wid;

	//各行列の計算
	trans.Calclation();

	//ゲージを減らす
	Image::SetRect(hPict, X, 0, wid, 130);

	//描画
 	Image::SetTransform(hPict, trans);
	Image::Draw(hPict);
}

//開放
void DrawGauge::Release()
{
}
