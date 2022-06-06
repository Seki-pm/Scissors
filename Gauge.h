#pragma once
#include "Engine/Image.h"
#include "Engine/Transform.h"
#include "Global.h"


class Gauge
{
private:

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
