#include "Stage2Scene.h"

//コンストラクタ
Stage2Scene::Stage2Scene(GameObject* parent)
	: GameObject(parent, "Stage2Scene"),
    BackImage_(-1), SelectSound_(-1), DeterSound_(-1),
    X(0),Y(0),Z(0), Gselect_(0), Pselect_(0)
{
}

//初期化
void Stage2Scene::Initialize()
{
    Global::HP = Global::MAXHP;
    Global::ItemImagePos = Global::ItemImagePos_Stage;
    Global::ItemImageSca = Global::ItemImageSca_Stage;
    Global::GameOver = false;
    Global::IsGameOver = false;
    Global::GetCoin = false;

    //ステージ
    Instantiate<Stage>(this);

    //ハサミ本体
    Instantiate<Scissors>(this);

    //ハサミのHP
    Instantiate<HP>(this);

    //ゴール演出
    Instantiate<GoalStaging>(this);

    //アイテムの表示
    Global::ItemModelPos = XMFLOAT3(-1.5, 17, 0);
    Instantiate<ItemModel>(this);

    //コインのゲット判定
    Instantiate<ItemImage>(this);


    //------ 背景 ---------
    BackImage_ = Image::Load("Image/Stage2_Back.png");
    assert(BackImage_ >= 0);

    //------ Select --------------
    SelectSound_ = Audio::Load("Sound/Select.wav");
    assert(SelectSound_ >= 0);

    //------ Determination -------------
    DeterSound_ = Audio::Load("Sound/Determination.wav");
    assert(DeterSound_ >= 0);
}

//更新
void Stage2Scene::Update()
{
    //trueの時アンロックをし、ステージ選択へ遷移
    if (Global::Timer)
    {
        Global::Unlock3 = true;
        Global::Timer = false;
        SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
        pSceneManager->ChangeScene(SCENE_ID_SELECT);
    }

    //ハサミ位置を取得
    Global gl;

    X = gl.GetTransPos_X();
    Y = gl.GetTransPos_Y();
    Z = gl.GetTransPos_Z();

    //ステージのスタート&ゴール位置を入れる
    CameraMove(gl.GetCameraStartX(), gl.GetCameraGoalX());

    //ゲームオーバー
    GameOverSEL();

    //一時停止
    PauseSEL();
}

//描画
void Stage2Scene::Draw()
{
    Image::Draw(BackImage_);
}

//開放
void Stage2Scene::Release()
{
    BackImage_ = -1;
    SelectSound_ = -1;
    DeterSound_ = -1;
}

//GameOver Select
void Stage2Scene::GameOverSEL()
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

//一時停止
void Stage2Scene::PauseSEL()
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
void Stage2Scene::CameraMove(float start, float goal)
{

    //transform.x に応じてカメラ移動を止める
    //スタート付近
    if (X < start)
    {
        Camera::SetPosition(XMFLOAT3(2, Y, -10));
        Camera::SetTarget(XMFLOAT3(2, Y, Z));
    }
    //ゴール付近
    else if (X >= goal)
    {
        Camera::SetPosition(XMFLOAT3(125, Y, -10));
        Camera::SetTarget(XMFLOAT3(125, Y, Z));
    }
    //そうでない場合Playerに追従する
    else
    {
        Camera::SetPosition(XMFLOAT3(X, Y, -10));
        Camera::SetTarget(XMFLOAT3(X, Y, Z));
    }


    //transform.y が0より小さい場合カメラを止める
    if (Y < -5)
    {
        Camera::SetPosition(XMFLOAT3(X, 3, -10));
        Camera::SetTarget(XMFLOAT3(X, 3, Z));
    }
}

