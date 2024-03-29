#include "Gauge.h"

//定数
const XMFLOAT3 TRANS_SCA = XMFLOAT3(2.f, 1.3f, 0.96f); //表示サイズ
const int IMAGE_WIDTH = 512;      //画像幅
const int SETRECT_HEIGHT = 130;   //切り取る高さ

//コンストラクタ
Gauge::Gauge()
{
}

//デストラクタ
Gauge::~Gauge()
{
}

//初期化
void Gauge::Initialize()
{
}

//描画
void Gauge::Draw(int val, float x, float y, int hPict)
{
	Transform trans;

	//出す場所
	trans.position_.x = x;
	trans.position_.y = y;
	trans.scale_ = TRANS_SCA;

	//画像の幅(%)を計算
	float ImageWidth_ = IMAGE_WIDTH;      //画像の幅
	float PicWid = ImageWidth_ / 200;     //画像幅(0.5%)


	//現在のHP(%)を計算
	float hp = (float)val;                             //現在のHP(int)
	float Nowhp  = hp / Game::MAXHP * 100;    //現在のHP(%)


	//使用している画像が右半分なので減少量も半分にする
	float SubHP = ( ImageWidth_ / 2 ) - ( PicWid * Nowhp );  //  減少したHP量   = 画像幅/2 - 画像幅(0.5%)*現在HP(%)
	float X = SubHP;                                         //切り取り開始位置 = 減少したHP量 
	float width = ImageWidth_ - SubHP * 2;                   //切り取り終了位置 = 画像幅 - 減少したHP量 * 2


	//各行列の計算
	trans.Calclation();

	//切り取ってゲージを減らす
	Image::SetRect(hPict, X, 0, width, SETRECT_HEIGHT);

	//描画
 	Image::SetTransform(hPict, trans);
	Image::Draw(hPict);
}

//開放
void Gauge::Release()
{
}
