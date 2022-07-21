#include "StageSelectScene.h"


//コンストラクタ
StageSelectScene::StageSelectScene(GameObject* parent)
	: GameObject(parent, "StageSelectScene"),
	  Drawflg(true)
{
	//STAGE_NUMBER 初期化
	for (int i = STAGE_NUMBER_1; i < STAGE_NUMBER_MAX; i++) {
		StageHandle_[i] = INITIAL_ERROR_VALUE;
	}

	//STAGE_LEVEL 初期化
	for (int i = STAGE_LEVEL_EASY; i < STAGE_LEVEL_MAX; i++)
	{
		LevelHandle_[i] = INITIAL_ERROR_VALUE;
	}

	//STAGE_LOCK 初期化
	for (int i = STAGE_LOCK_2; i < STAGE_LOCK_MAX; i++)
	{
		StageLockHandle_[i] = INITIAL_ERROR_VALUE;
	}

	//SELECT_SOUND 初期化
	for (int i = SOUND_SELECT; i < SOUND_MAX; i++)
	{
		SoundHandle_[i] = INITIAL_ERROR_VALUE;
	}

	//Load 初期化
	for (int i = LOAD_MIN + 1; i < LOAD_MAX; i++)
	{
		LoadHandle_[i] = INITIAL_ERROR_VALUE;
	}
}

//初期化
void StageSelectScene::Initialize()
{
	//画像データのロード
	//---------------------- STAGE ----------------------
	{
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
	}
	//---------------------------------------------------

	//------------------- STAGE_ROCK --------------------
	{
		StageLockHandle_[STAGE_LOCK_2] = Image::Load("Image/StageSelectScene/Lock_Stage2.png");
		assert(StageLockHandle_[STAGE_LOCK_2] >= 0);
		Lock[STAGE_LOCK_2].position_ = ST2_IMAGE_POS;

		StageLockHandle_[STAGE_LOCK_3] = Image::Load("Image/StageSelectScene/Lock_Stage3.png");
		assert(StageLockHandle_[STAGE_LOCK_3] >= 0);
		Lock[STAGE_LOCK_3].position_ = ST3_IMAGE_POS;

		Image::SetTransform(StageLockHandle_[STAGE_LOCK_2], Lock[STAGE_LOCK_2]);
		Image::SetTransform(StageLockHandle_[STAGE_LOCK_3], Lock[STAGE_LOCK_3]);
	}
	//---------------------------------------------------

	//---------------------- Level ----------------------
	{
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
	}
	//---------------------------------------------------


	//-------------------- Load画像 ---------------------
	{
		//--------------- 選択用フレーム ------------
		LoadHandle_[FrameImage_] = Image::Load("Image/StageSelectScene/Frame.png");
		assert(LoadHandle_[FrameImage_] >= 0);
		FrameTransform.position_ = ST1_IMAGE_POS;
		Image::SetTransform(LoadHandle_[FrameImage_], FrameTransform);


		LoadHandle_[BackImage_] = Image::Load("Image/TitleScene/Title_Back.png");
		assert(BackImage_ >= 0);
		//---------------------------------------------

		//---------------- 説明 ----------------------
		LoadHandle_[DescriptionImage_] = Image::Load("Image/StageSelectScene/Description.png");
		assert(LoadHandle_[DescriptionImage_] >= 0);
		auto DescTrans = Transform();
		DescTrans.position_ = DESCRIPTION_POS;
		Image::SetTransform(LoadHandle_[DescriptionImage_], DescTrans);
	}
	//---------------------------------------------------


	//----------------------- 音 ------------------------
	{
		//------ Select --------------
		SoundHandle_[SOUND_SELECT] = Audio::Load("Sound/Title&Menu/Select.wav");
		assert(SoundHandle_[SOUND_SELECT] >= 0);

		//------ Determination -------------
		SoundHandle_[SOUND_DETERMINATION] = Audio::Load("Sound/Title&Menu/Determination.wav");
		assert(SoundHandle_[SOUND_DETERMINATION] >= 0);

		//------------ ロック中 -----------
		SoundHandle_[SOUND_LOCK] = Audio::Load("Sound/Title&Menu/KeyLock.wav");
		assert(SoundHandle_[SOUND_LOCK] >= 0);
	}
	//---------------------------------------------------
}

//更新
void StageSelectScene::Update()
{
	//スペースを押したときに
	if (Input::IsKeyDown(DIK_SPACE) || Input::IsMouseButtonDown(0))
	{
		//1ならSTAGE1へ
		if (Global::SelectStage == STAGE_NUMBER_1 ||
			Global::SelectStage == STAGE_NUMBER_2 && Global::stage2.UnLock ||
			Global::SelectStage == STAGE_NUMBER_3 && Global::stage3.UnLock)
		{
			Audio::Play(SoundHandle_[SOUND_DETERMINATION]); //○
			SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
			pSceneManager->ChangeScene(SCENE_ID_STAGE);
		}
		else
		{
			Audio::Play(SoundHandle_[SOUND_LOCK]); //×
		}
	}

	//隠しコマンド 全ステージアンロック
	if (Input::IsKeyDown(DIK_LSHIFT))
	{
		Global::stage2.UnLock = true;
		Global::stage3.UnLock = true;
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
		Audio::Play(SoundHandle_[SOUND_SELECT]);

		switch (Global::SelectStage)
		{
		case STAGE_NUMBER_1: Global::SelectStage = STAGE_NUMBER_2; break;
		case STAGE_NUMBER_2: Global::SelectStage = STAGE_NUMBER_3; break;
		case STAGE_NUMBER_3: Global::SelectStage = STAGE_NUMBER_1; break;
		}
	}

	if (Input::IsKeyDown(DIK_LEFT))
	{
		Audio::Play(SoundHandle_[SOUND_SELECT]);

		switch (Global::SelectStage)
		{
		case STAGE_NUMBER_1: Global::SelectStage = STAGE_NUMBER_3; break;
		case STAGE_NUMBER_2: Global::SelectStage = STAGE_NUMBER_1; break;
		case STAGE_NUMBER_3: Global::SelectStage = STAGE_NUMBER_2; break;
		}
	}

	//フレームの位置変更
	switch (Global::SelectStage)
	{
	case STAGE_NUMBER_1: FrameTransform.position_ = ST1_IMAGE_POS; break;
	case STAGE_NUMBER_2: FrameTransform.position_ = ST2_IMAGE_POS; break;
	case STAGE_NUMBER_3: FrameTransform.position_ = ST3_IMAGE_POS; break;
	}
}

//マウスで選択
void StageSelectScene::MouseSelect()
{
	//マウスカーソルの位置を取得
	XMFLOAT3 mousePos = Input::GetMousePosition();

	//Stage1上
	if (ST1_MOUSE_POS.x < mousePos.x && mousePos.x < ST1_MOUSE_POS.z &&
		ST1_MOUSE_POS.y < mousePos.y && mousePos.y < ST1_MOUSE_POS.w)
	{
		Global::SelectStage = STAGE_NUMBER_1;
	}
	//Stage2上
	else if (ST2_MOUSE_POS.x < mousePos.x && mousePos.x < ST2_MOUSE_POS.z &&
		     ST2_MOUSE_POS.y < mousePos.y && mousePos.y < ST2_MOUSE_POS.w)
	{
		Global::SelectStage = STAGE_NUMBER_2;
	}
	//Stage3上
	else if (ST3_MOUSE_POS.x < mousePos.x && mousePos.x < ST3_MOUSE_POS.z &&
		     ST3_MOUSE_POS.y < mousePos.y && mousePos.y < ST3_MOUSE_POS.w)
	{
		Global::SelectStage = STAGE_NUMBER_3;
	}
}

//描画
void StageSelectScene::Draw()
{
	Image::Draw(LoadHandle_[BackImage_]);
	Image::Draw(LoadHandle_[DescriptionImage_]);

	//STAGE難易度の描画
	for (int i = 0; i < STAGE_LEVEL_MAX; i++)
	{
		Image::Draw(LevelHandle_[i]);
	}

	//ステージのロック解除
	StageUnlock();

	Image::SetTransform(LoadHandle_[FrameImage_], FrameTransform);
	Image::Draw(LoadHandle_[FrameImage_]);

	//コインの取得状況
	GetCoin();
}

//開放
void StageSelectScene::Release()
{
	//STAGE_NUMBER 開放
	for (int i = STAGE_NUMBER_1; i < STAGE_NUMBER_MAX; i++) {
		StageHandle_[i] = INITIAL_ERROR_VALUE;
	}

	//STAGE_LEVEL 開放
	for (int i = STAGE_LEVEL_EASY; i < STAGE_LEVEL_MAX; i++)
	{
		LevelHandle_[i] = INITIAL_ERROR_VALUE;
	}

	//STAGE_LOCK 開放
	for (int i = STAGE_LOCK_2; i < STAGE_LOCK_MAX; i++)
	{
		StageLockHandle_[i] = INITIAL_ERROR_VALUE;
	}

	//SELECT_SOUND 開放
	for (int i = SOUND_SELECT; i < SOUND_MAX; i++)
	{
		SoundHandle_[i] = INITIAL_ERROR_VALUE;
	}

	//Load 開放
	for (int i = FrameImage_; i < LOAD_MAX; i++)
	{
		LoadHandle_[i] = INITIAL_ERROR_VALUE;
	}

}

//ステージのロック解除管理
void StageSelectScene::StageUnlock()
{
	Image::Draw(StageHandle_[STAGE_NUMBER_1]);

	//アンロックフラグを基に描画の内容を変える
	if (Global::stage2.UnLock){
		Image::Draw(StageHandle_[STAGE_NUMBER_2]);
	}
	else{
		Image::Draw(StageLockHandle_[STAGE_LOCK_2]);
	}

	if (Global::stage3.UnLock){
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
		if (Global::stage1.Get_Coin)
		{
			Global::ItemImagePos = ST1_ITEMIMAGE_POS; //表示位置
			Instantiate<ItemImage>(this);            //表示
		}
		//Stage2のコイン
		if (Global::stage2.Get_Coin)
		{
			Global::ItemImagePos = ST2_ITEMIMAGE_POS;//表示位置
			Instantiate<ItemImage>(this);          //表示
		}
		//Stage3のコイン
		if (Global::stage3.Get_Coin)
		{
			Global::ItemImagePos = ST3_ITEMIMAGE_POS; //表示位置
			Instantiate<ItemImage>(this);            //表示
		}

		Drawflg = false;
	}
}

//画像の4頂点を取得
XMFLOAT4 StageSelectScene::ImagePos(int x1, int y1)
{
	//右下の座標を求める
	float x2 = (float)x1 + 256;  
	float y2 = (float)y1 + 128;

	return XMFLOAT4((float)x1, (float)y1, x2, y2);
}
