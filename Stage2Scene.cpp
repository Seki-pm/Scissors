#include "Stage2Scene.h"

//コンストラクタ
Stage2Scene::Stage2Scene(GameObject* parent)
	: GameObject(parent, "Stage2Scene"), select_(0), BackImage_(-1)
{
}

//初期化
void Stage2Scene::Initialize()
{
    Global::HP = Global::MAXHP;
    Global::GameOver = false;
    Global::IsGameOver = false;

    //ステージ
    Instantiate<Stage>(this);

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

    BackImage_ = Image::Load("Image/Stage2_Back.png");
    assert(BackImage_ >= 0);
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
            select_--;

            if (select_ < 0)
            {
                select_ = 0;
            }

            //GameOverクラスに渡す
            pGameOver->SetSelect(select_);
        }
        if (Input::IsKeyDown(DIK_RIGHT))
        {
            select_++;

            if (select_ > 1)
            {
                select_ = 1;
            }

            //GameOverクラスに渡す
            pGameOver->SetSelect(select_);
        }

        if (Input::IsKeyDown(DIK_SPACE) && select_ == 1)
        {
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

