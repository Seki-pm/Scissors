#pragma once
#include "Engine/Image.h"
#include "Engine/Transform.h"
#include "Global.h"


class Gauge
{
	const XMFLOAT3 TRANS_POS = XMFLOAT3(2.f, 1.3f, 0.96f); //位置
	const int SETRECT_HEIGHT = 130;   //切り取る高さ
	const int IMAGE_WIDTH = 512;      //画像幅

public:

	//コンストラクタ
	Gauge();

	//デストラクタ
	~Gauge();

	//初期化
	void Initialize();

	//数字の描画
	//引数:数字の値
	//     X座標
	//　　 Y座標
	//　　 ロードした画像
	//     最大HP
	void Draw(int val, float x, float y, int hPict);

	//開放
	void Release();

};
