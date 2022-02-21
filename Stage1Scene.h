#pragma once
#include "Engine/GameObject.h"
#include "Engine/SceneManager.h"
#include "DrawNumber.h"
#include "DrawGauge.h"
#include "Scissors.h"
#include "Global.h"


//STAGE1シーンを管理するクラス
class Stage1Scene : public GameObject
{
	Scissors* pScissors;
	DrawNumber* pNumber_;
	DrawGauge*  pGauge_;
	float X, Y, Z;

	int ImageHandle_;
	int GaugeHandle_;

	int MaxHp;

public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	Stage1Scene(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;


	//カメラ移動
	void CameraMove(float start, float goal);
};