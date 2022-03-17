#pragma once
#include "Engine/GameObject.h"
#include "Engine/SceneManager.h"
#include "Engine/Camera.h"
#include "Engine/Input.h"
#include "GameOver.h"
#include "Global.h"
#include "GoalStaging.h"
#include "HP.h"
#include "ItemImage.h"
#include "ItemModel.h"
#include "Scissors.h"
#include "Stage.h"


//STAGE2シーンを管理するクラス
class Stage2Scene : public GameObject
{
	Scissors* pScissors;
	float X, Y, Z;

	int select_;  //選択用変数

public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	Stage2Scene(GameObject* parent);

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