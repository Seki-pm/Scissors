#pragma once
#include "Engine/GameObject.h"
#include "Engine/SceneManager.h"
#include "Engine/Camera.h"
#include "Engine/Input.h"
#include "Engine/Image.h"
#include "Engine/Audio.h"
#include "GameOver.h"
#include "Global.h"
#include "HP.h"
#include "ItemModel.h"
#include "ItemImage.h"
#include "Pause.h"
#include "Scissors.h"
#include "Stage.h"
#include "StageSelectScene.h"
#include "GoalStaging.h"
#include "Sign.h"


//ステージシーンを管理するクラス
class StageScene : public GameObject
{
	Stage* pStage_;
	Global global;


	int Gselect_; //GameOver選択用変数
	int Pselect_; //Pause選択用変数

	int BackImage_;

	//Scissorsの位置を取得
	float Pos_X, Pos_Y, Pos_Z;

	int SelectSound_;      //選択音
	int DeterSound_;       //決定音

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
};