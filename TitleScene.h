#pragma once
#include "Engine/GameObject.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"
#include "Engine/Image.h"

//タイトルシーンを管理するクラス
class TitleScene : public GameObject
{
	int BackImageHandle_;
	int TitleImageHandle_;
	int SpaceKeyImageHandle_;

	float size_;

	Transform TitleTrans;
	Transform SpaceTrans;

public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	TitleScene(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
};