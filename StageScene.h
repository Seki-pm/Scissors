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
	const XMFLOAT3 ITEMIMAGE_POSITION_STAGE; //アイテム画像の位置(STAGE)
	const XMFLOAT3 ITEMIMAGE_SCALE_STAGE;    //アイテム画像のサイズ(STAGE)
	const int CAMERA_SET_POS;   //カメラの位置
	const int CAMERA_FALL_POS;  //落下したときのカメラ
	const int FALL_MAX;  //落下限界

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