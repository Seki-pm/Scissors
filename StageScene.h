#pragma once
#include "Engine/GameObject.h"
#include "Engine/SceneManager.h"
#include "Engine/Audio.h"
#include "Engine/Camera.h"
#include "Engine/Input.h"
#include "Engine/Image.h"
#include "GameOver.h"
#include "Global.h"
#include "GoalStaging.h"
#include "HP.h"
#include "ItemModel.h"
#include "ItemImage.h"
#include "Pause.h"
#include "Sign.h"
#include "Stage.h"
#include "StageSelectScene.h"



//ステージシーンを管理するクラス
class StageScene : public GameObject
{
	Global gl;

	int Gselect_; //GameOver選択用変数
	int Pselect_; //Pause選択用変数

	int SelectSound_;      //選択音
	int DeterSound_;       //決定音


	//定数
	const int CAMERA_SET_POS = -10;
	const int CAMERA_FALL_MAX = -3;
	const int FALL_MAX = -6;
	const XMFLOAT3 ItemImage_Scale_Stage = XMFLOAT3(0.5f,0.5f,0.5f);
	const XMFLOAT3 ItemImage_Position_Stage = XMFLOAT3(0.9f, 0.8f, 0.f);

public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	StageScene(GameObject* parent);

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

	//次のステージをアンロック
	void NextStageUnlock(int SelectStage);

	//ゴール演出用
	void Timer();
};