#pragma once
#include "Engine/GameObject.h"
#include "Engine/SceneManager.h"
#include "Engine/Camera.h"
#include "Engine/Input.h"
#include "Engine/Image.h"
#include "DrawNumber.h"
#include "GameOver.h"
#include "Global.h"
#include "GoalStaging.h"
#include "ItemImage.h"
#include "ItemModel.h"
#include "HP.h"
#include "Pause.h"
#include "Scissors.h"
#include "Sign.h"
#include "Stage.h"


//STAGE1シーンを管理するクラス
class Stage1Scene : public GameObject
{
	Global gl;

	DrawNumber* pNumber_; //デバック用

	float X, Y, Z;   //受け取る各座標系

	int Gselect_; //GameOver選択用変数
	int Pselect_; //Pause選択用変数

	int BackImage_;

	bool Itemflg;
	int cnt;

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

	//一時停止
	void PauseSEL();

	//カメラ移動
	void CameraMove(float start, float goal);
};