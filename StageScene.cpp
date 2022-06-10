#include "StageScene.h"



//コンストラクタ
StageScene::StageScene(GameObject* parent)
	: GameObject(parent, "StageScene"),pStage_(nullptr),
    Pos_X(0),Pos_Y(0),Pos_Z(0), Gselect_(-1), Pselect_(-1),
    SelectSound_(-1), DeterSound_(-1)
{
}

//初期化
void StageScene::Initialize()
{
    Global::HP = Global::MAXHP;                             //最大体力を設定
    Global::ItemImagePos = Global::ItemImagePos_Stage;      //コインの位置をステージ用に設定
    Global::ItemImageSca = Global::ItemImageSca_Stage;      //コインの大きさをステージ用に設定
    Global::GameOver = false;                               //GameOverではない
    Global::IsGameOver = false;                             //GameOverではない
    Global::GetCoin = false;                                //コインを取得していない

    //ステージ
    pStage_ = Instantiate<Stage>(this);
    pStage_->Load(Global::SelectStage);


    //ハサミ本体
    Instantiate<Scissors>(this);

    //ハサミのHP
    Instantiate<HP>(this);

    //アイテムの表示
    Instantiate<ItemModel>(this);

    //コインのゲット判定
    Instantiate<ItemImage>(this);

    //ゴール演出
    Instantiate<GoalStaging>(this);
}

//更新
void StageScene::Update()
{
    //ハサミの位置を取得
    Pos_X = global.GetTransPos_X();
    Pos_Y = global.GetTransPos_Y();
    Pos_Z = global.GetTransPos_Z();

    //ステージのスタート&ゴール位置を入れる
    CameraMove(global.GetCameraStartX(), global.GetCameraGoalX());

    //ゲームオーバー
    GameOverSEL();

    //一時停止
    PauseSEL();

    //ゴール演出用
    Timer();

    //取得してからGameOverの場合コインを再表示する
    //取得しているものは取得してないこととする
    if (Global::GetCoin && Global::ItemReDraw)
    {
        Instantiate<ItemModel>(this);
        Global::ItemReDraw = false;
        Global::GetCoin = false;
        Global::GetCoin_1 = false;
        Global::GetCoin_2 = false;
        Global::GetCoin_3 = false;
    }
}

//描画
void StageScene::Draw()
{
}

//開放
void StageScene::Release()
{
    SelectSound_ = -1;
    DeterSound_ = -1;
    Global::Repel_.clear();
    Global::Sink_.clear();
}

//GameOver
void StageScene::GameOverSEL()
{
    GameOver* pGameOver = (GameOver*)FindObject("GameOver");

    if (Global::IsGameOver)
    {
        //GameOver表示
        Instantiate<GameOver>(this);
        Global::IsGameOver = false;
        Global::ItemReDraw = true;
    }

    //GameOverになったら
    if (Global::GameOver)
    {
        //ボタンを選択
        //選択
        if (Input::IsKeyDown(DIK_LEFT))
        {
            Gselect_ = 0;
            Audio::Play(SelectSound_);

            //GameOverクラスに渡す
            pGameOver->SetSelect(Gselect_);
        }
        if (Input::IsKeyDown(DIK_RIGHT))
        {
            Gselect_ = 1;
            Audio::Play(SelectSound_);

            //GameOverクラスに渡す
            pGameOver->SetSelect(Gselect_);
        }

        if (Input::IsKeyDown(DIK_SPACE) && Gselect_ == 1)
        {
            Audio::Play(DeterSound_);

            SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
            pSceneManager->ChangeScene(SCENE_ID_SELECT);
        }
    }
}

//Pause
void StageScene::PauseSEL()
{
    Pause* pPause = (Pause*)FindObject("Pause");

    //一時停止する(falseの時のみ)
    if (!Global::Pause) {
        if (Input::IsKeyDown(DIK_ESCAPE))
        {
            Instantiate<Pause>(this);			//一時停止
            Global::Pause = true;
        }
    }
    //一時停止されたとき
    if (Global::Pause)
    {
        //ボタンを選択
        if (Input::IsKeyDown(DIK_LEFT))
        {
            Pselect_ = 0;
            Audio::Play(SelectSound_);

            //Pauseクラスに渡す
            pPause->SetSelect(Pselect_);
        }
        if (Input::IsKeyDown(DIK_RIGHT))
        {
            Pselect_ = 1;
            Audio::Play(SelectSound_);

            //Pauseクラスに渡す
            pPause->SetSelect(Pselect_);
        }


        //メニューシーンに移動する
        if (Input::IsKeyDown(DIK_SPACE) && Pselect_ == 1)
        {
            Global::GetCoin = false;
            Global::Pause = false;

            Audio::Play(DeterSound_);

            //メニューシーンに移動
            SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
            pSceneManager->ChangeScene(SCENE_ID_SELECT);
        }
    }
}

//カメラ移動
void StageScene::CameraMove(float start, float goal)
{

    //transform.x に応じてカメラ移動を止める
    //スタート付近
    if (Pos_X < start)
    {
        Camera::SetPosition(XMFLOAT3(global.GetCameraStartX(), Pos_Y, -10));
        Camera::SetTarget(XMFLOAT3(global.GetCameraStartX(), Pos_Y, Pos_Z));
    }
    //ゴール付近
    else if (Pos_X >= goal)
    {
        Camera::SetPosition(XMFLOAT3(global.GetCameraGoalX(), Pos_Y, -10));
        Camera::SetTarget(XMFLOAT3(global.GetCameraGoalX(), Pos_Y, Pos_Z));
    }
    //そうでない場合Playerに追従する
    else
    {
        Camera::SetPosition(XMFLOAT3(Pos_X, Pos_Y, -10));
        Camera::SetTarget(XMFLOAT3(Pos_X, Pos_Y, Pos_Z));
    }


    //transform.y が0より小さい場合カメラを止める
    if (Pos_Y < -6)
    {
        Camera::SetPosition(XMFLOAT3(Pos_X, -3, -10));
        Camera::SetTarget(XMFLOAT3(Pos_X, -3, Pos_Z));
    }
}

//次のステージをアンロック
void StageScene::NextStageUnlock( int SelectStage )
{
    switch (SelectStage)
    {
    case STAGE_NUMBER_1:
        Global::Unlock2 = true;
        break;
    case STAGE_NUMBER_2:
        Global::Unlock3 = true;
        break;
    case STAGE_NUMBER_3:
        break;
    }
}

//ゴール演出用
void StageScene::Timer()
{
    //trueの時アンロックをし、ステージ選択へ遷移
    if (Global::Timer)
    {
        NextStageUnlock(Global::SelectStage);
        Global::Timer = false;
        SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
        pSceneManager->ChangeScene(SCENE_ID_SELECT);
    }
}
