#include "Stage1Scene.h"


//コンストラクタ
Stage1Scene::Stage1Scene(GameObject* parent)
    : GameObject(parent, "Stage1Scene"),select_(0),
    X(0),Y(0),Z(0), BackImage_(-1), pNumber_(nullptr),Itemflg(false),cnt(0)
{
}

//初期化
void Stage1Scene::Initialize()
{
    Global::HP = Global::MAXHP;
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

    //看板
    Instantiate<Sign>(this);

    //コインのゲット判定
    Instantiate<ItemImage>(this);

    //コインの表示位置
    Global::ItemPos = XMFLOAT3(46, 9, 0);


    BackImage_ = Image::Load("Image/Stage1_Back.png");
    assert(BackImage_ >= 0);
}

//更新
void Stage1Scene::Update()
{
    //trueの時アンロックをし、ステージ選択へ遷移
    if (Global::Timer)
    {
        Global::Unlock2 = true;
        Global::Timer = false;
        SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
        pSceneManager->ChangeScene(SCENE_ID_SELECT);
    }

    //ハサミ位置を取得
    X = gl.GetTransPos_X();
    Y = gl.GetTransPos_Y();
    Z = gl.GetTransPos_Z();

    //ステージのスタート&ゴール位置を入れる
    CameraMove(gl.GetCameraStartX(), gl.GetCameraGoalX());

    //GameOverSelect
    GameOverSEL();

    //Coinを表示
    if (Itemflg  && cnt == 0)
    {
        Instantiate<ItemModel>(this);
        cnt++;
    }
}

//描画
void Stage1Scene::Draw()
{
    Image::Draw(BackImage_);
}

//開放
void Stage1Scene::Release()
{
    BackImage_ = -1;
}

//GameOver Select
void Stage1Scene::GameOverSEL()
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
        Camera::SetPosition(XMFLOAT3(55, Y, -10));
        Camera::SetTarget(XMFLOAT3(55, Y, Z));
        Itemflg = true;
    }
    //そうでない場合Playerに追従する
    else
    {
        Camera::SetPosition(XMFLOAT3(X, 3 ,-10));
        Camera::SetTarget(XMFLOAT3(X, 3, Z));
    }


    //transform.y が0より小さい（穴に落ちた）場合カメラを止める
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