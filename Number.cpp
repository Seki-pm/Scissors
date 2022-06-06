#include "Number.h"

//コンストラクタ
Number::Number()
{
}

//デストラクタ
Number::~Number()
{
}

//描画
void Number::Draw(int val, float x, float y, int hPict)
{
	Transform trans;

	//一の位を出す場所
	trans.position_.x = x;
	trans.position_.y = y;


	while (true)
	{
		//数字の幅分ずらす(数字の間隔)
		trans.position_.x -= 0.06f;

		//各行列の計算
		trans.Calclation();

		//数字を切り抜く
		//1の位だけ描画する
		Image::SetRect(hPict, (val % 10) * 51, 0, 51, 130);

		Image::SetTransform(hPict, trans);
		Image::Draw(hPict);

		//valを10でで割る
		val /= 10;

		//0になったらbreak
		if (val <= 0) break;
	}

}

//開放
void Number::Release()
{
}
