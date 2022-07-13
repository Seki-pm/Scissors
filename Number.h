#pragma once
#include "Engine/Image.h"
#include "Engine/Transform.h"

class Number
{
	const float NUMBER_INTERVAL = 0.06f;

public:

	//コンストラクタ
	Number();

	//デストラクタ
	~Number();

	//数字の描画
	//引数:数字の値
	//     X座標
	//　　 Y座標
	//　　 ロードした画像
	void Draw(int val, float x, float y, int hPict);

	//開放
	void Release();

};

