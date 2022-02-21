#include "Stage1Scene.h"
#include "Engine/Camera.h"
#include "Engine/Input.h"
#include "Stage.h"
#include "Sign.h"
#include "HP.h"
#include "GameOver.h"



//コンストラクタ
Stage1Scene::Stage1Scene(GameObject* parent)
    : GameObject(parent, "Stage1Scene")
{
}

//初期化
void Stage1Scene::Initialize()
{
    Global::MAXHP = 300;
    Global::GameOver = false;

    //ステージ
    Instantiate<Stage>(this);

    //看板
    Instantiate<Sign>(this);

    //ハサミ本体
    Instantiate<Scissors>(this);

    //ハサミのHP
    Instantiate<HP>(this);

}

//更新
void Stage1Scene::Update()
{
    Global gl;

    X = gl.GetTransPos_X();
    Y = gl.GetTransPos_Y();
    Z = gl.GetTransPos_Z();

    CameraMove(gl.GetCameraStart(), gl.GetCameraGoal());

    //ゲームオーバー
    if (Global::GameOver) {
        Instantiate<GameOver>(this);
    }
}

//描画
void Stage1Scene::Draw()
{
}

//開放
void Stage1Scene::Release()
{
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
        if (Input::IsKeyDown(DIK_LSHIFT))
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