#include "StageScene.h"


//コンストラクタ
StageScene::StageScene(GameObject* parent)
	: GameObject(parent, "StageScene"),
      Gselect_(INITIAL_ERROR_VALUE), Pselect_(INITIAL_ERROR_VALUE)
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

    //取得してからリスタートの場合コインを再表示する
    //取得しているものは取得してない様にする
    if (Global::GetCoin && Global::ItemReDraw)
    {
        Instantiate<ItemModel>(this);
        Global::ItemReDraw = false;
        CoinDelete();  //コインの取得を無くす
    }


}

//描画
void StageScene::Draw()
{
}

//開放
void StageScene::Release()
{
}

//ゲームオーバー
void StageScene::GameOverSEL()
{
    GameOver* pGameOver_ = (GameOver*)FindObject("GameOver");

    if (Global::IsGameOver)
    {
        //GameOver表示
        Instantiate<GameOver>(this);
        Global::IsGameOver = false;

    }

    //GameOverになったら
    if (Global::GameOver)
    {
        //ボタンを選択
        {
            if (Input::IsKeyDown(DIK_LEFT))
            {
                Gselect_ = 0;
                //GameOverクラスに渡す
                pGameOver_->SetSelect(Gselect_);
            }
            if (Input::IsKeyDown(DIK_RIGHT))
            {
                Gselect_ = 1;
                //GameOverクラスに渡す
                pGameOver_->SetSelect(Gselect_);
            }
        }

        //SPACEを押したとき
        if (Input::IsKeyDown(DIK_SPACE))
        {
            if (Gselect_ == 0)
            {
                pGameOver_->KillMe();     //GameOverを消す
                pGameOver_->pScissors_->Restart(); //スタートに戻る
            }
            else if (Gselect_ == 1)
            {
                //ステージ選択シーンに移動
                SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
                pSceneManager->ChangeScene(SCENE_ID_SELECT);
            }
        }
    }
}

//ポーズ
void StageScene::PauseSEL()
{
    Pause* pPause_ = (Pause*)FindObject("Pause");

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
        {
            if (Input::IsKeyDown(DIK_LEFT))
            {
                Pselect_ = 0;
                //Pauseクラスに渡す
                pPause_->SetSelect(Pselect_);
            }
            if (Input::IsKeyDown(DIK_RIGHT))
            {
                Pselect_ = 1;
                //Pauseクラスに渡す
                pPause_->SetSelect(Pselect_);
            }
        }

        //SPACEを押したとき
        if (Input::IsKeyDown(DIK_SPACE))
        {
            Global::Pause = false;

            if (Pselect_ == 0)
            {
                pPause_->KillMe(); //Pauseを消す
            }
            else if (Pselect_ == 1)
            {
                CoinDelete(); //コインの取得を無くす
                //GetCoinSave();

                //ステージ選択シーンに移動
                SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
                pSceneManager->ChangeScene(SCENE_ID_SELECT);
            }
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


    //transform.y が0より小さい（落下した）場合カメラを止める
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
    case STAGE_NUMBER_1: Global::Unlock2 = true; break;
    case STAGE_NUMBER_2: Global::Unlock3 = true; break;
    case STAGE_NUMBER_3: break;
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

//取得コインの削除
void StageScene::CoinDelete()
{
    Global::GetCoin = false;

    //取得したコインを無くす
    switch (Global::SelectStage)
    {
    case STAGE_NUMBER_1:   Global::GetCoin_1 = false; break;
    case STAGE_NUMBER_2:   Global::GetCoin_2 = false; break;
    case STAGE_NUMBER_3:   Global::GetCoin_3 = false; break;
    }
}

void StageScene::GetCoinSave()
{
    switch (Global::SelectStage)
    {
    case STAGE_NUMBER_1:
        if (Global::GetCoin_1) Global::GetCoin = true; break;
    case STAGE_NUMBER_2:
        if (Global::GetCoin_2) Global::GetCoin = true; break;
    case STAGE_NUMBER_3:
        if (Global::GetCoin_3) Global::GetCoin = true; break;
    }
}
