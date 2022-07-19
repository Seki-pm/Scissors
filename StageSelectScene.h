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

	//サウンド
	enum SELECT_SOUND
	{
		SOUND_SELECT = 1,       //選択音
		SOUND_DETERMINATION = 2,//決定音
		SOUND_LOCK = 3,         //ロック音
		SOUND_MAX
	};

	//ロード用変数
	enum Load
	{
		LOAD_MIN = 0,
		FrameImage_,       //フレーム画像
		BackImage_,        //背景画像
		DescriptionImage_, //説明画像
		LOAD_MAX
	};

	//enumのものを配列にあてる
	int StageHandle_[STAGE_NUMBER_MAX];    //ステージ番号
	int StageLockHandle_[STAGE_LOCK_MAX];  //ロック画像
	int LevelHandle_[STAGE_LEVEL_MAX];     //難易度画像
	int SoundHandle_[SOUND_MAX];           //選択などの音
	int LoadHandle_[LOAD_MAX];             //その他ロード画像

	bool Drawflg; //表示させるか否か(一度だけ)

	//各transform
	Transform Stage[STAGE_NUMBER_MAX];
	Transform Lock[STAGE_LOCK_MAX];
	Transform Level[STAGE_LEVEL_MAX];
	Transform FrameTransform;

	//定数
	//各ステージのアイテム画像位置
	const XMFLOAT3 ST1_ITEMIMAGE_POS = XMFLOAT3(-0.4f, 0, 0);
	const XMFLOAT3 ST2_ITEMIMAGE_POS = XMFLOAT3( 0.2f, 0, 0);
	const XMFLOAT3 ST3_ITEMIMAGE_POS = XMFLOAT3( 0.8f, 0, 0);

	//各ステージ画像位置
	const XMFLOAT3 ST1_IMAGE_POS = XMFLOAT3(-0.6f, 0.2f, 0);
	const XMFLOAT3 ST2_IMAGE_POS = XMFLOAT3(   0 , 0.2f, 0);
	const XMFLOAT3 ST3_IMAGE_POS = XMFLOAT3( 0.6f, 0.2f, 0);

	//難易度の画像位置
	const XMFLOAT3 EASY_POSITION = XMFLOAT3(-0.6f, 0.5f, 0);
	const XMFLOAT3 NOMAL_POSITION = XMFLOAT3(   0 , 0.5f, 0);
	const XMFLOAT3 HARD_POSITION = XMFLOAT3( 0.6f, 0.5f, 0);

	const XMFLOAT3 DESCRIPTION_POS = XMFLOAT3(0.0f, -0.6f, 0);   //説明画像の位置
	const XMFLOAT3 ITEMIMAGE_SCALE_SELECT = XMFLOAT3(0.4f, 0.4f, 0.4f); //アイテム画像のサイズ

	//マウスで選択できる位置
	const XMFLOAT4 ST1_MOUSE_POS = ImagePos(128, 228); 
	const XMFLOAT4 ST2_MOUSE_POS = ImagePos(513, 228);
	const XMFLOAT4 ST3_MOUSE_POS = ImagePos(897, 228);

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

	//画像の4頂点を取得( height=256 , width=128 )
	//引数：左上の頂点座標（ X , Y ）
	XMFLOAT4 ImagePos(int x1, int y1);
};