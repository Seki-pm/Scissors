#include "PlayScene.h"
#include "Engine/Camera.h"
#include "Scissors.h"
#include "Stage.h"


//コンストラクタ
PlayScene::PlayScene(GameObject * parent)
	: GameObject(parent, "PlayScene")
{
}

//初期化
void PlayScene::Initialize()
{
	//ステージ
	Instantiate<Stage>(this);

	//ハサミ本体
	Instantiate<Scissors>(this);


	Camera::SetPosition(XMFLOAT3(5, 5, -10));
	Camera::SetTarget(XMFLOAT3(5, 3, 0));
}

//更新
void PlayScene::Update()
{
}

//描画
void PlayScene::Draw()
{
}

//開放
void PlayScene::Release()
{
}
