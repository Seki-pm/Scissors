#include "Stage1Scene.h"
#include "Engine/Camera.h"
#include "Engine/Input.h"
#include "Stage.h"
#include "Sign.h"
#include "HP.h"
#include "GameOver.h"
#include "GoalStaging.h"




//コンストラクタ
Stage1Scene::Stage1Scene(GameObject* parent)
    : GameObject(parent, "Stage1Scene"),select_(0)
{
}

//初期化
void Stage1Scene::Initialize()
{
    Global::MAXHP = 300;
    Global::HP = Global::MAXHP;
    Global::GameOver = false;
    Global::IsGameOver = false;

    //ステージ
    Instantiate<Stage>(this);

    //看板
    Instantiate<Sign>(this);

    //ハサミ本体
    Instantiate<Scissors>(this);

    //ハサミのHP
    Instantiate<HP>(this);

    Instantiate<GoalStaging>(this);
}

//更新
void Stage1Scene::Update()
{
    if (Input::IsKeyDown(DIK_5))
    {
        Global::GameOver = true;
        Global::IsGameOver = true;
    }


    Global gl;

    X = gl.GetTransPos_X();
    Y = gl.GetTransPos_Y();
    Z = gl.GetTransPos_Z();

    CameraMove(gl.GetCameraStart(), gl.GetCameraGoal());

    GameOverSEL();
}

//描画
void Stage1Scene::Draw()
{
}

//開放
void Stage1Scene::Release()
{
}

void Stage1Scene::GameOverSEL()
{
    GameOver* pGameOver = (GameOver*)FindObject("GameOver");

    if (Global::IsGameOver)
    {
        //GameOver表示
        Global::IsGameOver = false;
    }

    //GameOverになったら
    if (Global::GameOver)
    {
        Instantiate<GameOver>(this);

        //ボタンを選択
        //選択
        if (Global::GameOver && Input::IsKeyDown(DIK_LEFT))
        {
            select_--;

            if (select_ < 0)
            {
                select_ = 0;
            }

            //GameOverクラスに渡す
            pGameOver->SetSelect(select_);
        }
        if (Global::GameOver && Input::IsKeyDown(DIK_RIGHT))
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

        Global::GameOver = false;
    }
}

void Stage1Scene::CameraMove(float start, float goal)
{

    //transform.x に応じてカメラ移動を止める
    //スタート付近
    if (X < start)
    {
        Camera::SetPosition(XMFLOAT3(2, 3, -10));
        Camera::SetTarget(XMFLOAT3(2, 3, Z));
    }
    //ゴール付近
    else if (X >= goal)
    {
        XMFLOAT3 CamPos = XMFLOAT3(56, Y, -10);


        Camera::SetPosition(XMFLOAT3(56, Y, -10));
        Camera::SetTarget(XMFLOAT3(56, Y, Z));
        Global::Unlock2 = true;
        if (Global::Timer)
        {
            SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
            pSceneManager->ChangeScene(SCENE_ID_SELECT);
        }
    }
    //そうでない場合Playerに追従する
    else
    {
        Camera::SetPosition(XMFLOAT3(X, 3 ,-10));
        Camera::SetTarget(XMFLOAT3(X, 3, Z));
    }


    //transform.y が0より小さい場合カメラを止める
    if (Y < -5)
    {
        Camera::SetPosition(XMFLOAT3(X, 3, -10));
        Camera::SetTarget(XMFLOAT3(X, 3, Z));
    }
    else if (Y > 5)
    {
        Camera::SetPosition(XMFLOAT3(X, 6, -10));
        Camera::SetTarget(XMFLOAT3(X, 6, Z));
    }
}