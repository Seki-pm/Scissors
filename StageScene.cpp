#include "StageScene.h"


//コンストラクタ
StageScene::StageScene(GameObject* parent)
	: GameObject(parent, "StageScene"), Gselect_(-1), Pselect_(-1)
{
}

//初期化
void StageScene::Initialize()
{                      
    Global::ItemImagePos = ITEMIMAGE_POSITION_STAGE;      //コインの位置をステージ用に設定
    Global::ItemImageSca = ITEMIMAGE_SCALE_STAGE;         //コインの大きさをステージ用に設定
    Global::GameOver = false;                               //GameOverではない
    Global::IsGameOver = false;                             //GameOverではない
    Global::GetCoin = false;                                //コインを取得していない

    //ステージ
    Stage* pStage_ = Instantiate<Stage>(this);
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
    //ステージのスタート&ゴール位置を入れる
    CameraMove(gl.GetCameraStart().x, gl.GetCameraGoal().x);

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

        //取得したコインを無くす
        switch (Global::SelectStage)
        {
        case STAGE_NUMBER_1:
            Global::GetCoin_1 = false; break;
        case STAGE_NUMBER_2:
            Global::GetCoin_2 = false; break;
        case STAGE_NUMBER_3:
            Global::GetCoin_3 = false; break;
        }
    }
}

//描画
void StageScene::Draw()
{
}

//開放
void StageScene::Release()
{
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

        //アイテム再表示
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
            //GameOverクラスに渡す
            pGameOver->SetSelect(Gselect_);
        }
        if (Input::IsKeyDown(DIK_RIGHT))
        {
            Gselect_ = 1;
            //GameOverクラスに渡す
            pGameOver->SetSelect(Gselect_);
        }

        if (Input::IsKeyDown(DIK_SPACE) && Gselect_ == 1)
        {
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
            //Pauseクラスに渡す
            pPause->SetSelect(Pselect_);
        }
        if (Input::IsKeyDown(DIK_RIGHT))
        {
            Pselect_ = 1;
            //Pauseクラスに渡す
            pPause->SetSelect(Pselect_);
        }


        //メニューシーンに移動する
        if (Input::IsKeyDown(DIK_SPACE) && Pselect_ == 1)
        {
            Global::GetCoin = false;
            Global::Pause = false;

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
    if (gl.GetTransPos().x < start)
    {
        Camera::SetPosition(XMFLOAT3(gl.GetCameraStart().x, gl.GetTransPos().y, CAMERA_SET_POS));
        Camera::SetTarget(XMFLOAT3(gl.GetCameraStart().x, gl.GetTransPos().y, gl.GetTransPos().z));
    }
    //ゴール付近
    else if (gl.GetTransPos().x >= goal)
    {
        Camera::SetPosition(XMFLOAT3(gl.GetCameraGoal().x, gl.GetTransPos().y, CAMERA_SET_POS));
        Camera::SetTarget(XMFLOAT3(gl.GetCameraGoal().x, gl.GetTransPos().y, gl.GetTransPos().z));
    }
    //そうでない場合Playerに追従する
    else
    {
        Camera::SetPosition(XMFLOAT3(gl.GetTransPos().x, gl.GetTransPos().y, CAMERA_SET_POS));
        Camera::SetTarget(XMFLOAT3(gl.GetTransPos().x, gl.GetTransPos().y, gl.GetTransPos().z));
    }


    //transform.y が0より小さい場合カメラを止める
    if (gl.GetTransPos().y < FALL_MAX)
    {
        Camera::SetPosition(XMFLOAT3(gl.GetTransPos().x, CAMERA_FALL_MAX, CAMERA_SET_POS));
        Camera::SetTarget(XMFLOAT3(gl.GetTransPos().x, CAMERA_FALL_MAX, gl.GetTransPos().z));
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
    GoalStaging* pGoalStaging_ = (GoalStaging*)FindObject("GoalStaging");

    //trueの時
    if (pGoalStaging_->timer_)
    {
        //次のステージをアンロックをし、ステージ選択へ遷移
        NextStageUnlock(Global::SelectStage);
        pGoalStaging_->timer_ = false;
        SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
        pSceneManager->ChangeScene(SCENE_ID_SELECT);
    }
}

