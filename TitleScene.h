#pragma once
#include "Engine/GameObject.h"
#include "Engine/SceneManager.h"
#include "Engine/Audio.h"
#include "Engine/Input.h"
#include "Engine/Image.h"

//タイトルシーンを管理するクラス
class TitleScene : public GameObject
{
	//ロード用変数
	enum Load
	{
		LOAD_MIN = 0,
		BackImage_,     //背景画像
		TitleImage_,    //タイトル画像
		SpaceKeyImage_, //SPACE画像
		ScissorsSound_, //ハサミの音
		LOAD_MAX
	};

	//enumを入れる配列
	int LoadHandle_[LOAD_MAX];

	//タイムを数える
	int TimerCnt;

	//タイマーフラグ
	bool Timer_;

	//画像の動き用の変数
	float alpha_;
	float theta_;

	//Transform変数
	Transform TitleTrans;
	Transform SpaceTrans;

	//定数
	const XMFLOAT3 TITLE_POS = XMFLOAT3(0, 0.3f, 0);  //タイトル位置
	const XMFLOAT3 TITLE_SCA = XMFLOAT3(3, 3, 0);     //タイトルサイズ
	const XMFLOAT3 SPACE_POS = XMFLOAT3(0, -0.6f, 0); //SPACE位置
	const int TIMER_COUNT = 80;       //時間数える

public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	TitleScene(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	//点滅
	void Blinking();

	//時間計測
	void Timer();
};