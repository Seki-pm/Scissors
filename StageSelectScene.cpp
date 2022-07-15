#include "StageSelectScene.h"


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
	Stage[STAGE_NUMBER_1].position_ = ST1_IMAGE_POS;

	StageHandle_[STAGE_NUMBER_2] = Image::Load("Image/StageSelectScene/STAGE2.png");
	assert(StageHandle_[STAGE_NUMBER_2] >= 0);
	Stage[STAGE_NUMBER_2].position_ = ST2_IMAGE_POS;

	StageHandle_[STAGE_NUMBER_3] = Image::Load("Image/StageSelectScene/STAGE3.png");
	assert(StageHandle_[STAGE_NUMBER_3] >= 0);
	Stage[STAGE_NUMBER_3].position_ = ST3_IMAGE_POS;


	Image::SetTransform(StageHandle_[STAGE_NUMBER_1], Stage[STAGE_NUMBER_1]);
	Image::SetTransform(StageHandle_[STAGE_NUMBER_2], Stage[STAGE_NUMBER_2]);
	Image::SetTransform(StageHandle_[STAGE_NUMBER_3], Stage[STAGE_NUMBER_3]);

	//---------------------------------------------------

	//------------------- STAGE_ROCK --------------------------

	StageLockHandle_[STAGE_LOCK_2] = Image::Load("Image/StageSelectScene/Lock_Stage2.png");
	assert(StageLockHandle_[STAGE_LOCK_2] >= 0);
	Lock[STAGE_LOCK_2].position_ = ST2_IMAGE_POS;

	StageLockHandle_[STAGE_LOCK_3] = Image::Load("Image/StageSelectScene/Lock_Stage3.png");
	assert(StageLockHandle_[STAGE_LOCK_3] >= 0);
	Lock[STAGE_LOCK_3].position_ = ST3_IMAGE_POS;

	Image::SetTransform(StageLockHandle_[STAGE_LOCK_2], Lock[STAGE_LOCK_2]);
	Image::SetTransform(StageLockHandle_[STAGE_LOCK_3], Lock[STAGE_LOCK_3]);

	//--------------------------------------------------

	//-------------------- Level ---------------------------
	LevelHandle_[STAGE_LEVEL_EASY] = Image::Load("Image/StageSelectScene/Easy.png");
	assert(LevelHandle_[STAGE_LEVEL_EASY] >= 0);
	Level[STAGE_LEVEL_EASY].position_ = EASY_POSITION;

	LevelHandle_[STAGE_LEVEL_NORMAL] = Image::Load("Image/StageSelectScene/Normal.png");
	assert(LevelHandle_[STAGE_LEVEL_NORMAL] >= 0);
	Level[STAGE_LEVEL_NORMAL].position_ = NOMAL_POSITION;

	LevelHandle_[STAGE_LEVEL_HARD] = Image::Load("Image/StageSelectScene/Hard.png");
	assert(LevelHandle_[STAGE_LEVEL_HARD] >= 0);
	Level[STAGE_LEVEL_HARD].position_ = HARD_POSITION;

	Image::SetTransform(LevelHandle_[STAGE_LEVEL_EASY], Level[STAGE_LEVEL_EASY]);
	Image::SetTransform(LevelHandle_[STAGE_LEVEL_NORMAL], Level[STAGE_LEVEL_NORMAL]);
	Image::SetTransform(LevelHandle_[STAGE_LEVEL_HARD], Level[STAGE_LEVEL_HARD]);

	//---------------------------------------------------


	//--------------- 選択用フレーム ------------
	FrameImageHandle_ = Image::Load("Image/StageSelectScene/Frame.png");
	assert(FrameImageHandle_ >= 0);
	FrameTransform.position_ = ST1_IMAGE_POS;
	Image::SetTransform(FrameImageHandle_, FrameTransform);


	BackImage_ = Image::Load("Image/TitleScene/Title_Back.png");
	assert(BackImage_ >= 0);
	//---------------------------------------------

	//---------------- 説明 ----------------------
	DescriptionImage_ = Image::Load("Image/StageSelectScene/Description.png");
	assert(DescriptionImage_ >= 0);
	auto DescTrans = Transform();
	DescTrans.position_ = DESCRIPTION_POS;
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
		FrameTransform.position_ = ST1_IMAGE_POS;
		break;
	case STAGE_NUMBER_2:
		FrameTransform.position_ = ST2_IMAGE_POS;
		break;
	case STAGE_NUMBER_3:
		FrameTransform.position_ = ST3_IMAGE_POS;
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
		Global::ItemImageSca = ITEMIMAGE_SCALE_SELECT; //表示サイズ

		//Stage1のコイン
		if (Global::GetCoin_1)
		{
			Global::ItemImagePos = ST1_ITEMIMAGE_POS; //表示位置
			Instantiate<ItemImage>(this);            //表示
		}
		//Stage2のコイン
		if (Global::GetCoin_2)
		{
			Global::ItemImagePos = ST2_ITEMIMAGE_POS;//表示位置
			Instantiate<ItemImage>(this);          //表示
		}
		//Stage3のコイン
		if (Global::GetCoin_3)
		{
			Global::ItemImagePos = ST3_ITEMIMAGE_POS; //表示位置
			Instantiate<ItemImage>(this);            //表示
		}

		Drawflg = false;
	}
}

XMFLOAT4 StageSelectScene::ImagePos(int x1, int y1)
{
	int x2 = x1 + 256;
	int y2 = y1 + 128;

	return XMFLOAT4(x1, y1, x2, y2);
}
