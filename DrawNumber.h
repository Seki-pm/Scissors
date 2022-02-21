#pragma once
#include "Engine/Image.h"
#include "Engine/Transform.h"

class DrawNumber
{
private:
	DrawNumber* pNumber_;

public:

	//コンストラクタ
	DrawNumber();

	//デストラクタ
	~DrawNumber();

	//初期化
	void Initialize();

	//数字の描画
	//引数:数字の値
	//     X座標
	//　　 Y座標
	//　　 ロードした画像
	void Draw(int val, float x, float y, int hPict);

	//開放
	void Release();

};

