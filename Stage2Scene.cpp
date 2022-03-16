#include "Stage2Scene.h"

//コンストラクタ
Stage2Scene::Stage2Scene(GameObject* parent)
	: GameObject(parent, "Stage2Scene")
{
}

//初期化
void Stage2Scene::Initialize()
{
    Global::MAXHP = 500;
    Global::HP = Global::MAXHP;
    Global::GameOver = false;

    //ステージ
    Instantiate<Stage>(this);

    //ハサミ本体
    Instantiate<Scissors>(this);

    //ハサミのHP
    Instantiate<HP>(this);

    //アイテムの表示
    Instantiate<ItemModel>(this);

    //コインのゲット判定
    Instantiate<ItemImage>(this);
}

//更新
void Stage2Scene::Update()
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
void Stage2Scene::Draw()
{
}

//開放
void Stage2Scene::Release()
{
}

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
        Camera::SetPosition(XMFLOAT3(56, Y, -10));
        Camera::SetTarget(XMFLOAT3(56, Y, Z));
        Global::Unlock3 = true;
        if (Input::IsKeyDown(DIK_LSHIFT))
        {
            SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
            pSceneManager->ChangeScene(SCENE_ID_SELECT);
        }
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

