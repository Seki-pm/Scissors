#pragma once
#include "Engine/GameObject.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"
#include "Engine/Image.h"
#include "Engine/Transform.h"
#include "Engine/Audio.h"
#include "Global.h"
#include "ItemImage.h"

//ステージ番号
enum STAGE_NUMBER
{
	STAGE_NUMBER_1 = 1,
	STAGE_NUMBER_2 = 2,
	STAGE_NUMBER_3 = 3,
	STAGE_NUMBER_MAX
};

//ステージロック
enum STAGE_LOCK
{
	STAGE_LOCK_2 = 2,
	STAGE_LOCK_3 = 3,
	STAGE_LOCK_MAX
};

//ステージレベル
enum STAGE_LEVEL
{
	STAGE_LEVEL_EASY = 1,
	STAGE_LEVEL_NORMAL = 2,
	STAGE_LEVEL_HARD = 3,
	STAGE_LEVEL_MAX
};


//ステージ選択シーンを管理するクラス
class StageSelectScene : public GameObject
{
private:

	//enumのものを配列にあてる
	int StageHandle_[STAGE_NUMBER_MAX];       
	int StageLockHandle_[STAGE_LOCK_MAX];
	int LevelHandle_[STAGE_LEVEL_MAX];

	int FrameImageHandle_; //フレーム
	int BackImage_;        //背景
	int DescriptionImage_; //説明

	int SelectSound_;      //選択音
	int DeterSound_;       //決定音
	int LockSound_;        //ロック音

	bool Drawflg; //表示させるか否か(一度だけ)

	//各transform
	Transform Stage[STAGE_NUMBER_MAX];
	Transform Lock[STAGE_LOCK_MAX];
	Transform Level[STAGE_LEVEL_MAX];
	Transform FrameTransform;

public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	StageSelectScene(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//キー選択
	void Select();

	//マウス選択
	void MouseSelect();

	//描画
	void Draw() override;

	//開放
	void Release() override;

	//ステージアンロック
	void StageUnlock();

	//コインの取得状況
	void GetCoin();

};