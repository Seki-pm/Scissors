#pragma once
#include "Engine/GameObject.h"
#include "Engine/SceneManager.h"
#include "Engine/Camera.h"
#include "Engine/Input.h"
#include "Engine/Image.h"
#include "GameOver.h"
#include "Global.h"
#include "GoalStaging.h"
#include "HP.h"
#include "ItemImage.h"
#include "ItemModel.h"
#include "Pause.h"
#include "Scissors.h"
#include "Stage.h"


//STAGE2シーンを管理するクラス
class Stage2Scene : public GameObject
{
	ItemModel* pItemModel_;

	float X, Y, Z;

	int Gselect_; //GameOver選択用変数
	int Pselect_; //Pause選択用変数

	int BackImage_;

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

	//一時停止
	void PauseSEL();

	//カメラ移動
	void CameraMove(float start, float goal);

};