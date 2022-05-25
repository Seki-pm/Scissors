#include "StageScene.h"

//コンストラクタ
StageScene::StageScene(GameObject* parent)
	: GameObject(parent, "StageScene"),pStage_(nullptr),
    Pos_X(0),Pos_Y(0),Pos_Z(0)
{
}

//初期化
void StageScene::Initialize()
{
    Global::HP = Global::MAXHP;
    Global::ItemImagePos = Global::ItemImagePos_Stage;
    Global::ItemImageSca = Global::ItemImageSca_Stage;
    Global::GameOver = false;
    Global::IsGameOver = false;
    Global::GetCoin = false;

    //ステージ
    pStage_ = Instantiate<Stage>(this); 
    pStage_->Load(Global::Select);

    //ハサミ本体
    Instantiate<Scissors>(this);

    //ハサミのHP
    Instantiate<HP>(this);

    //ゴール演出
    Instantiate<GoalStaging>(this);

    //アイテムの表示
    Instantiate<ItemModel>(this);

    //コインのゲット判定
    Instantiate<ItemImage>(this);
}

//更新
void StageScene::Update()
{
    //trueの時アンロックをし、ステージ選択へ遷移
    if (Global::Timer)
    {
        //Global::Unlock3 = true;
        Global::Timer = false;
        SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
        pSceneManager->ChangeScene(SCENE_ID_SELECT);
    }

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

}

//描画
void StageScene::Draw()
{
    Image::Draw(BackImage_);
}

//開放
void StageScene::Release()
{
    BackImage_ = -1;
    SelectSound_ = -1;
    DeterSound_ = -1;
    Global::Repel_.clear();
    Global::Sink_.clear();
}

void StageScene::GameOverSEL()
{
    GameOver* pGameOver = (GameOver*)FindObject("GameOver");

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
        //選択
        if (Input::IsKeyDown(DIK_LEFT))
        {
            Gselect_--;
            Audio::Play(SelectSound_);

            if (Gselect_ < 0)
            {
                Gselect_ = 0;
            }

            //GameOverクラスに渡す
            pGameOver->SetSelect(Gselect_);
        }
        if (Input::IsKeyDown(DIK_RIGHT))
        {
            Gselect_++;
            Audio::Play(SelectSound_);

            if (Gselect_ > 1)
            {
                Gselect_ = 1;
            }

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
            Pselect_--;
            Audio::Play(SelectSound_);

            if (Pselect_ < 0)
            {
                Pselect_ = 0;
            }

            //Pauseクラスに渡す
            pPause->SetSelect(Pselect_);
        }
        if (Input::IsKeyDown(DIK_RIGHT))
        {
            Pselect_++;
            Audio::Play(SelectSound_);

            if (Pselect_ > 1)
            {
                Pselect_ = 1;
            }

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
        Camera::SetPosition(XMFLOAT3(global.GetCameraGoalX()-2, Pos_Y, -10));
        Camera::SetTarget(XMFLOAT3(global.GetCameraGoalX()-2, Pos_Y, Pos_Z));
    }
    //そうでない場合Playerに追従する
    else
    {
        Camera::SetPosition(XMFLOAT3(Pos_X, Pos_Y, -10));
        Camera::SetTarget(XMFLOAT3(Pos_X, Pos_Y, Pos_Z));
    }


    //transform.y が0より小さい場合カメラを止める
    if (Pos_Y < -5)
    {
        Camera::SetPosition(XMFLOAT3(Pos_X, 3, -10));
        Camera::SetTarget(XMFLOAT3(Pos_X, 3, Pos_Z));
    }
}
