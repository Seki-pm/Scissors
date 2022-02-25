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
void DrawGauge::Draw(int val, float x, float y, int hPict)
{
	Transform trans;

	//出す場所
	trans.position_.x = x;
	trans.position_.y = y;
	trans.scale_ = XMFLOAT3(2.f, 1.3f, 0.96f);

	//画像の幅(%)
	float ImageWidth_ = 512;           //画像の幅
	float w = ImageWidth_ / 100;       //画像幅(1%)
	float wid = ImageWidth_ / 200;   //画像幅(0.5%)

	//現在のHP(%)
	float hp_    = Global::HP;          //現在のHP
	float Nowhp  = hp_ / Global::MAXHP * 100;   //現在のHP(%)


	//使用している画像が右半分なので減少量も半分にする
	float SubHP = 256 - wid * Nowhp;       //  減少したHP量   =  
	float X = SubHP;                       //切り取り開始位置 = 減少したHP 
	float width = ImageWidth_ - SubHP * 2; //切り取り終了位置 = 画像幅 -











	//各行列の計算
	trans.Calclation();

	//ゲージを減らす
	Image::SetRect(hPict, X, 0, width, 130);

	//描画
 	Image::SetTransform(hPict, trans);
	Image::Draw(hPict);
}

//開放
void DrawGauge::Release()
{
}
