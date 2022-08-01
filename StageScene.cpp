#include "StageScene.h"


//コンストラクタ
StageScene::StageScene(GameObject* parent)
	: GameObject(parent, "StageScene"),
      Gselect_(0), Pselect_(0)
{
}

//初期化
void StageScene::Initialize()
{                      
    Game::ItemImagePos = ITEMIMAGE_POSITION_STAGE;      //コインの位置をステージ用に設定
    Game::ItemImageSca = ITEMIMAGE_SCALE_STAGE;         //コインの大きさをステージ用に設定
    Game::GameOver = false;                             //GameOverではない
    Game::IsGameOver = false;                           //GameOverではない
    GetCoinJudge();                                       //コイン入手判定

    //ステージ
    Stage* pStage_ = Instantiate<Stage>(this);
    pStage_->Load(Game::SelectStage);

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
    CameraMove(game.GetCameraStart().x, game.GetCameraGoal().x);

    //ゲームオーバー
    GameOverSEL();

    //一時停止
    PauseSEL();

    //ゴール演出用
    Timer();

    //取得してからリスタートの場合コインを再表示する
    //取得しているものは取得してない様にする
    if (Game::GetCoin && Game::ItemReDraw)
    {
        Instantiate<ItemModel>(this);
        Game::ItemReDraw = false;
        GetCoinJudge(); //コイン入手判定
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

    if (Game::IsGameOver)
    {
        //GameOver表示
        Instantiate<GameOver>(this);
        Game::IsGameOver = false;

    }

    //GameOverになったら
    if (Game::GameOver)
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
    if (!Game::Pause) {
        if (Input::IsKeyDown(DIK_ESCAPE))
        {
            Instantiate<Pause>(this);			//一時停止
            Game::Pause = true;
        }
    }

    //一時停止されたとき
    if (Game::Pause)
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
            Game::Pause = false;

            if (Pselect_ == 0)
            {
                pPause_->KillMe(); //Pauseを消す
            }
            else if (Pselect_ == 1)
            {
                
                GetCoinJudge(); //コイン入手判定

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
    if (game.GetTransPos().x < start)
    {
        Camera::SetPosition(XMFLOAT3(game.GetCameraStart().x, game.GetTransPos().y, CAMERA_SET_POS));
        Camera::SetTarget(XMFLOAT3(game.GetCameraStart().x, game.GetTransPos().y, game.GetTransPos().z));
    }
    //ゴール付近
    else if (game.GetTransPos().x >= goal)
    {
        Camera::SetPosition(XMFLOAT3(game.GetCameraGoal().x, game.GetTransPos().y, CAMERA_SET_POS));
        Camera::SetTarget(XMFLOAT3(game.GetCameraGoal().x, game.GetTransPos().y, game.GetTransPos().z));
    }
    //そうでない場合Playerに追従する
    else
    {
        Camera::SetPosition(XMFLOAT3(game.GetTransPos().x, game.GetTransPos().y, CAMERA_SET_POS));
        Camera::SetTarget(XMFLOAT3(game.GetTransPos().x, game.GetTransPos().y, game.GetTransPos().z));
    }


    //transform.y が0より小さい（落下した）場合カメラを止める
    if (game.GetTransPos().y < FALL_MAX)
    {
        Camera::SetPosition(XMFLOAT3(game.GetTransPos().x, CAMERA_FALL_MAX, CAMERA_SET_POS));
        Camera::SetTarget(XMFLOAT3(game.GetTransPos().x, CAMERA_FALL_MAX, game.GetTransPos().z));
    }
}

//次のステージをアンロック
void StageScene::NextStageUnlock( int SelectStage )
{
    switch (SelectStage)
    {
    case STAGE_NUMBER_1: game.setState(Game::stage2.UnLock); break;
    case STAGE_NUMBER_2: game.setState(Game::stage3.UnLock); break;
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
        NextStageUnlock(Game::SelectStage);
        pGoalStaging_->timer_ = false;
        SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
        pSceneManager->ChangeScene(SCENE_ID_SELECT);
    }
}

//各ステージのコインを入手したかどうかの判定
void StageScene::GetCoinJudge()
{
    Game::GetCoin = false;

    //現在のステージのコインを取得しているか
    switch (Game::SelectStage)
    {
    case STAGE_NUMBER_1:
        //クリアフラグがtrueなら
        if (game.getState(Game::stage1.Clear)) {
            Game::GetCoin = true;
            game.setState(Game::stage1.GetCoin);
        }
        else
        {
            Game::GetCoin = false;
            game.unsetState(Game::stage1.GetCoin);
        }
        break;
    case STAGE_NUMBER_2:
        if (game.getState(Game::stage2.Clear)) {
            Game::GetCoin = true;
            game.setState(Game::stage2.GetCoin);
        }
        else
        {
            Game::GetCoin = false;
            game.unsetState(Game::stage2.GetCoin);
        }
        break;
    case STAGE_NUMBER_3:
        if (game.getState(Game::stage3.Clear)) {
            Game::GetCoin = true;
            game.setState(Game::stage3.GetCoin);
        }
        else
        {
            Game::GetCoin = false;
            game.unsetState(Game::stage3.GetCoin);
        }
        break;
    }
}
