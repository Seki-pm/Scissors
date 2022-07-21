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
#include "ItemImage.h"
#include "ItemModel.h"
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

	//定数
	const float CAMERA_SET_POS = -10.f;  //カメラ位置
	const float CAMERA_FALL_MAX = -3.f;  //落下時のカメラ限界
	const int FALL_MAX = -8;             //Playerの落下限界
	const XMFLOAT3 ITEMIMAGE_SCALE_STAGE = XMFLOAT3(0.5f,0.5f,0.5f);     //アイテム画像のサイズ
	const XMFLOAT3 ITEMIMAGE_POSITION_STAGE = XMFLOAT3(0.9f, 0.8f, 0.f); //アイテム画像の位置

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

	//各ステージのコインを入手したかどうかの判定
	void GetCoinJudge();
};