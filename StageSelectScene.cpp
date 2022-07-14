#include "StageSelectScene.h"

#define St1_ItemImage_Pos XMFLOAT3(-0.4f, 0, 0); 
#define St2_ItemImage_Pos XMFLOAT3( 0.2f, 0, 0);
#define St3_ItemImage_Pos XMFLOAT3( 0.8f, 0, 0);

#define St1_Image_Pos XMFLOAT3(-0.6f, 0.2f, 0);
#define St2_Image_Pos XMFLOAT3(   0 , 0.2f, 0);
#define St3_Image_Pos XMFLOAT3( 0.6f, 0.2f, 0);

#define Easy_Position   XMFLOAT3(-0.6f, 0.5f, 0);
#define Normal_Position XMFLOAT3(   0 , 0.5f, 0);
#define Hard_Position   XMFLOAT3( 0.6f, 0.5f, 0);

#define Description_Pos XMFLOAT3(0.0f, -0.6f, 0);

#define ItemImage_Scale_Select XMFLOAT3(0.4f, 0.4f, 0.4f);

//コンストラクタ
StageSelectScene::StageSelectScene(GameObject* parent)
	: GameObject(parent, "StageSelectScene"),
	FrameImageHandle_(-1), BackImage_(-1), SelectSound_(-1),
	DeterSound_(-1), DescriptionImage_(-1), LockSound_(-1),
	Drawflg(true)
{
	//STAGE_NUMBER 初期化
	for (int i = STAGE_NUMBER_1; i < STAGE_NUMBER_MAX; i++) {
		StageHandle_[i] = -1;
	}

	//STAGE_LEVEL 初期化
	for (int i = STAGE_LEVEL_EASY; i < STAGE_LEVEL_MAX; i++)
	{
		LevelHandle_[i] = -1;
	}

	//STAGE_LOCK 初期化
	for (int i = STAGE_LOCK_2; i < STAGE_LOCK_MAX; i++)
	{
		StageLockHandle_[i] = -1;
	}
}

//初期化
void StageSelectScene::Initialize()
{
	//画像データのロード
	//---------------------- STAGE ------------------------------

	StageHandle_[STAGE_NUMBER_1] = Image::Load("Image/StageSelectScene/STAGE1.png");
	assert(StageHandle_[STAGE_NUMBER_1] >= 0);
	Stage[STAGE_NUMBER_1].position_ = St1_Image_Pos;

	StageHandle_[STAGE_NUMBER_2] = Image::Load("Image/StageSelectScene/STAGE2.png");
	assert(StageHandle_[STAGE_NUMBER_2] >= 0);
	Stage[STAGE_NUMBER_2].position_ = St2_Image_Pos;

	StageHandle_[STAGE_NUMBER_3] = Image::Load("Image/StageSelectScene/STAGE3.png");
	assert(StageHandle_[STAGE_NUMBER_3] >= 0);
	Stage[STAGE_NUMBER_3].position_ = St3_Image_Pos;


	Image::SetTransform(StageHandle_[STAGE_NUMBER_1], Stage[STAGE_NUMBER_1]);
	Image::SetTransform(StageHandle_[STAGE_NUMBER_2], Stage[STAGE_NUMBER_2]);
	Image::SetTransform(StageHandle_[STAGE_NUMBER_3], Stage[STAGE_NUMBER_3]);

	//---------------------------------------------------

	//------------------- STAGE_ROCK --------------------------

	StageLockHandle_[STAGE_LOCK_2] = Image::Load("Image/StageSelectScene/Lock_Stage2.png");
	assert(StageLockHandle_[STAGE_LOCK_2] >= 0);
	Lock[STAGE_LOCK_2].position_ = St2_Image_Pos;

	StageLockHandle_[STAGE_LOCK_3] = Image::Load("Image/StageSelectScene/Lock_Stage3.png");
	assert(StageLockHandle_[STAGE_LOCK_3] >= 0);
	Lock[STAGE_LOCK_3].position_ = St3_Image_Pos;

	Image::SetTransform(StageLockHandle_[STAGE_LOCK_2], Lock[STAGE_LOCK_2]);
	Image::SetTransform(StageLockHandle_[STAGE_LOCK_3], Lock[STAGE_LOCK_3]);

	//--------------------------------------------------

	//-------------------- Level ---------------------------
	LevelHandle_[STAGE_LEVEL_EASY] = Image::Load("Image/StageSelectScene/Easy.png");
	assert(LevelHandle_[STAGE_LEVEL_EASY] >= 0);
	Level[STAGE_LEVEL_EASY].position_ = Easy_Position;

	LevelHandle_[STAGE_LEVEL_NORMAL] = Image::Load("Image/StageSelectScene/Normal.png");
	assert(LevelHandle_[STAGE_LEVEL_NORMAL] >= 0);
	Level[STAGE_LEVEL_NORMAL].position_ = Normal_Position;

	LevelHandle_[STAGE_LEVEL_HARD] = Image::Load("Image/StageSelectScene/Hard.png");
	assert(LevelHandle_[STAGE_LEVEL_HARD] >= 0);
	Level[STAGE_LEVEL_HARD].position_ = Hard_Position;

	Image::SetTransform(LevelHandle_[STAGE_LEVEL_EASY], Level[STAGE_LEVEL_EASY]);
	Image::SetTransform(LevelHandle_[STAGE_LEVEL_NORMAL], Level[STAGE_LEVEL_NORMAL]);
	Image::SetTransform(LevelHandle_[STAGE_LEVEL_HARD], Level[STAGE_LEVEL_HARD]);

	//---------------------------------------------------


	//--------------- 選択用フレーム ------------
	FrameImageHandle_ = Image::Load("Image/StageSelectScene/Frame.png");
	assert(FrameImageHandle_ >= 0);
	FrameTransform.position_ = St1_Image_Pos;
	Image::SetTransform(FrameImageHandle_, FrameTransform);


	BackImage_ = Image::Load("Image/TitleScene/Title_Back.png");
	assert(BackImage_ >= 0);
	//---------------------------------------------

	//---------------- 説明 ----------------------
	DescriptionImage_ = Image::Load("Image/StageSelectScene/Description.png");
	assert(DescriptionImage_ >= 0);
	auto DescTrans = Transform();
	DescTrans.position_ = Description_Pos;
	Image::SetTransform(DescriptionImage_, DescTrans);
	//--------------------------------------------


	//------------- 音 ----------------------------------

	//------ Select --------------
	SelectSound_ = Audio::Load("Sound/Title&Menu/Select.wav");
	assert(SelectSound_ >= 0);

	//------ Determination -------------
	DeterSound_ = Audio::Load("Sound/Title&Menu/Determination.wav");
	assert(DeterSound_ >= 0);

	//------------ ロック中 -----------
	LockSound_ = Audio::Load("Sound/Title&Menu/KeyLock.wav");
	assert(LockSound_ >= 0);

	//----------------------------------------------------
}

//更新
void StageSelectScene::Update()
{
	//スペースを押したときに
	if (Input::IsKeyDown(DIK_SPACE) || Input::IsMouseButtonDown(0))
	{
		//1ならSTAGE1へ
		if (Global::SelectStage == STAGE_NUMBER_1 ||
			Global::SelectStage == STAGE_NUMBER_2 && Global::Unlock2 || 
			Global::SelectStage == STAGE_NUMBER_3 && Global::Unlock3)
		{
			Audio::Play(DeterSound_); //○
			SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
			pSceneManager->ChangeScene(SCENE_ID_STAGE);
		}
		else
		{
			Audio::Play(LockSound_); //×
		}
	}

	//隠しコマンド 全ステージアンロック
	if (Input::IsKeyDown(DIK_LSHIFT))
	{
		Global::Unlock2 = true;
		Global::Unlock3 = true;
	}

	//選択
	MouseSelect();
	Select();
}

//選択
void StageSelectScene::Select()
{
	//方向キーで選択
	if (Input::IsKeyDown(DIK_RIGHT))
	{
		Audio::Play(SelectSound_);

		switch (Global::SelectStage)
		{
		case STAGE_NUMBER_1:
			Global::SelectStage = STAGE_NUMBER_2; break;
		case STAGE_NUMBER_2:
			Global::SelectStage = STAGE_NUMBER_3; break;
		case STAGE_NUMBER_3:
			Global::SelectStage = STAGE_NUMBER_1; break;
		}
	}

	if (Input::IsKeyDown(DIK_LEFT))
	{
		Audio::Play(SelectSound_);

		switch (Global::SelectStage)
		{
		case STAGE_NUMBER_1:
			Global::SelectStage = STAGE_NUMBER_3; break;
		case STAGE_NUMBER_2:
			Global::SelectStage = STAGE_NUMBER_1; break;
		case STAGE_NUMBER_3:
			Global::SelectStage = STAGE_NUMBER_2; break;
		}
	}

	//フレームの位置変更
	switch (Global::SelectStage)
	{
	case STAGE_NUMBER_1:
		FrameTransform.position_ = St1_Image_Pos;
		break;
	case STAGE_NUMBER_2:
		FrameTransform.position_ = St2_Image_Pos;
		break;
	case STAGE_NUMBER_3:
		FrameTransform.position_ = St3_Image_Pos;
		break;
	}
}

//マウスで選択
void StageSelectScene::MouseSelect()
{
	//マウスカーソルの位置を取得
	XMFLOAT3 mousePos = Input::GetMousePosition();

	//Stage1上
	if ( 132 < mousePos.x && mousePos.x < 388 && 
		 228 < mousePos.y && mousePos.y < 356)
	{
		Global::SelectStage = STAGE_NUMBER_1;
	}
	//Stage2上
	else if (513 < mousePos.x && mousePos.x < 765 &&
		     226 < mousePos.y && mousePos.y < 351)
	{
		Global::SelectStage = STAGE_NUMBER_2;
	}
	//Stage3上
	else if (897 < mousePos.x && mousePos.x < 1148 &&
		     224 < mousePos.y && mousePos.y < 347)
	{
		Global::SelectStage = STAGE_NUMBER_3;
	}
}

//描画
void StageSelectScene::Draw()
{
	Image::Draw(BackImage_);
	Image::Draw(DescriptionImage_);

	//STAGE難易度の描画
	for (int i = 0; i < STAGE_LEVEL_MAX; i++)
	{
		Image::Draw(LevelHandle_[i]);
	}

	//ステージのロック解除
	StageUnlock();

	Image::SetTransform(FrameImageHandle_, FrameTransform);
	Image::Draw(FrameImageHandle_);

	//コインの取得状況
	GetCoin();
}

//開放
void StageSelectScene::Release()
{
	//STAGE_NUMBER 開放
	for (int i = STAGE_NUMBER_1; i < STAGE_NUMBER_MAX; i++) {
		StageHandle_[i] = -1;
	}

	//STAGE_LEVEL 開放
	for (int i = STAGE_LEVEL_EASY; i < STAGE_LEVEL_MAX; i++)
	{
		LevelHandle_[i] = -1;
	}

	//STAGE_LOCK 開放
	for (int i = STAGE_LOCK_2; i < STAGE_LOCK_MAX; i++)
	{
		StageLockHandle_[i] = -1;
	}

	FrameImageHandle_ = -1;
	DescriptionImage_ = -1;
	SelectSound_ = -1;
	DeterSound_ = -1;
	BackImage_ = -1;
	LockSound_ = -1;
}

//ステージのロック解除管理
void StageSelectScene::StageUnlock()
{
	Image::Draw(StageHandle_[STAGE_NUMBER_1]);

	//アンロックフラグを基に描画の内容を変える
	if (Global::Unlock2){
		Image::Draw(StageHandle_[STAGE_NUMBER_2]);
	}
	else{
		Image::Draw(StageLockHandle_[STAGE_LOCK_2]);
	}

	if (Global::Unlock3){
		Image::Draw(StageHandle_[STAGE_NUMBER_3]);
	}
	else{
		Image::Draw(StageLockHandle_[STAGE_LOCK_3]);
	}
}

//コインの取得状況
void StageSelectScene::GetCoin()
{
	//一度だけ描画
	if (Drawflg)
	{
		Global::ItemImageSca = ItemImage_Scale_Select; //表示サイズ

		//Stage1のコイン
		if (Global::GetCoin_1)
		{
			Global::ItemImagePos = St1_ItemImage_Pos //表示位置
			Instantiate<ItemImage>(this);            //表示
		}
		//Stage2のコイン
		if (Global::GetCoin_2)
		{
			Global::ItemImagePos = St2_ItemImage_Pos//表示位置
			Instantiate<ItemImage>(this);          //表示
		}
		//Stage3のコイン
		if (Global::GetCoin_3)
		{
			Global::ItemImagePos = St3_ItemImage_Pos //表示位置
			Instantiate<ItemImage>(this);            //表示
		}

		Drawflg = false;
	}
}

XMFLOAT4 StageSelectScene::ImagePos(int x, int y)
{
	int x2 = x + 256;
	int y2 = y + 128;

	return XMFLOAT4(x,y,x2,y2);
}
