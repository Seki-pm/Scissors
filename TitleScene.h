#pragma once
#include "Engine/GameObject.h"
#include "Engine/SceneManager.h"
#include "Engine/Audio.h"
#include "Engine/Input.h"
#include "Engine/Image.h"


//タイトルシーンを管理するクラス
class TitleScene : public GameObject
{
	//画像用変数
	int BackImage_;
	int TitleImage_;
	int SpaceKeyImage_;

	//音用変数
	int ScissorsSound_;

	//タイムを数える
	int TimerCnt;

	//
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