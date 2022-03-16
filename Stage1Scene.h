#pragma once
#include "Engine/GameObject.h"
#include "Engine/SceneManager.h"
#include "Engine/Camera.h"
#include "Engine/Input.h"
#include "DrawGauge.h"
#include "DrawNumber.h"
#include "GameOver.h"
#include "Global.h"
#include "GoalStaging.h"
#include "HP.h"
#include "Scissors.h"
#include "Sign.h"
#include "Stage.h"




//STAGE1シーンを管理するクラス
class Stage1Scene : public GameObject
{
	Scissors* pScissors;  //Scissorsのポインタ
	DrawNumber* pNumber_; //デバック用
	DrawGauge*  pGauge_;  //HPゲージ用

	float X, Y, Z;   //受け取る各座標系

	int select_; //選択用変数

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