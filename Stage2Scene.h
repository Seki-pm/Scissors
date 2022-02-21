#pragma once
#include "Engine/GameObject.h"
#include "Engine/SceneManager.h"
#include "Engine/Camera.h"
#include "Engine/Input.h"
#include "Engine/Model.h"
#include "PolygonCollider.h"
#include "Stage.h"
#include "Scissors.h"
#include "Global.h"
#include "HP.h"
#include "ItemModel.h"
#include "GameOver.h"

//ステージ2シーンを管理するクラス
class Stage2Scene : public GameObject
{
	Scissors* pScissors;
	float X, Y, Z;

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

	//カメラ移動
	void CameraMove(float start, float goal);

	void Collider();

};