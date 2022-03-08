#pragma once
#include "Engine/GameObject.h"
#include "Engine/SceneManager.h"
#include "DrawNumber.h"
#include "DrawGauge.h"
#include "Scissors.h"
#include "Global.h"
#include "GameOver.h"


//STAGE1シーンを管理するクラス
class Stage1Scene : public GameObject
{
	Scissors* pScissors;  //Scissorsのポインタ
	DrawNumber* pNumber_; //デバック用
	DrawGauge*  pGauge_;  //HPゲージ用
	float X, Y, Z;

	int ImageHandle_;
	int GaugeHandle_;

	int MaxHp;
	int select_;

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

	//GAMEOVER
	void GameOverSEL();

	//カメラ移動
	void CameraMove(float start, float goal);
};