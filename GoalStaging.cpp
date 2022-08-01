#include "GoalStaging.h"
#include "StageSelectScene.h"

//コンストラクタ
GoalStaging::GoalStaging(GameObject* parent)
    :GameObject(parent, "GoalStaging"), 
    timer_(false),StagingFlg(false), StringFlg(false),
    time_(0), size_(10)
{
    //Load 初期化
    for (int i = LOAD_MIN + 1; i < LOAD_MAX; i++)
    {
        LoadHandle_[i] = INITIAL_ERROR_VALUE;
    }
}

//デストラクタ
GoalStaging::~GoalStaging()
{
}

//初期化
void GoalStaging::Initialize()
{
    //------------------------  データの読み込み  ---------------------------------
    {
        //モデルデータのロード
        LoadHandle_[BalloonModel_] = Model::Load("Model/InGameObject/Balloon.fbx");
        assert(LoadHandle_[BalloonModel_] >= 0);
        BalloonTrans.position_ = XMFLOAT3(game.GetCameraGoal().x, game.GetCameraGoal().y, 0.f);
        BalloonTrans.scale_ = BAL_ENT_SIZE;
        Model::SetTransform(LoadHandle_[BalloonModel_], BalloonTrans);

        //Enter
        LoadHandle_[EnterImage_] = Image::Load("Image/InGameMenu/Enter.png");
        assert(LoadHandle_[EnterImage_] >= 0);
        EnterTrans.position_ = ENTER_POS;
        EnterTrans.scale_ = BAL_ENT_SIZE;
        Image::SetTransform(LoadHandle_[EnterImage_], EnterTrans);

        //暗転
        LoadHandle_[BackImage_] = Image::Load("Image/InGameMenu/Clear_Black.png");
        assert(LoadHandle_[BackImage_] >= 0);
        auto BlackTrans = Transform();
        BlackTrans.scale_ = BACKIMAGE_SIZE;
        Image::SetTransform(LoadHandle_[BackImage_], BlackTrans);

        //収縮用
        LoadHandle_[CircleImage_] = Image::Load("Image/InGameMenu/Clear_Effect.png");
        assert(LoadHandle_[CircleImage_] >= 0);
        CircleTrans.scale_ = XMFLOAT3(size_, size_, size_);

        //サウンド
        LoadHandle_[GoalSound_] = Audio::Load("Sound/InStage/Staging.wav");
        assert(LoadHandle_[GoalSound_] >= 0);
    }
    //-----------------------------------------------------------------------------
}

//更新
void GoalStaging::Update()
{
    //風船のアニメーション開始
    //if (Input::IsKeyDown(DIK_I))
    //{
    //    Model::SetAnimFrame(BalloonModel_, 1, 300, 1.0f);
    //}

    //ゴールについたら文字表示
    if (game.GetTransPos().x >= game.GetCameraGoal().x - 1.5f)
    {
        //文字表示
        StringFlg = true;
    }
    else
    {
        StringFlg = false;
    }

    //Enterが押されたらタイマー開始
    if (StagingFlg) Timer();
}

//描画
void GoalStaging::Draw()
{
    Model::Draw(LoadHandle_[BalloonModel_]);

    //ゴール演出
    if(StringFlg)
    {
        //文字表示
        Image::Draw(LoadHandle_[EnterImage_]);

        //Enterキーを押したら
        if (Input::IsKeyDown(DIK_RETURN))
        {
            ClearJudge(); //クリア判定

            Audio::Play(LoadHandle_[GoalSound_]);

            StringFlg = false;
            //ゴール演出スタート
            StagingFlg = true;
        }
    }

    //暗転処理
    if (StagingFlg)
    {
        CircleTrans.scale_ = XMFLOAT3(size_, size_, size_);
        Image::SetTransform(LoadHandle_[CircleImage_], CircleTrans);

        //size_の大きさで表示画像を変える
        if (size_ > SIZE_MIN)
        {
            //サイズを縮小させる
            size_ -= SCALE_DOWN_VAL;
            Image::Draw(LoadHandle_[CircleImage_]);
        }
        else
        {
            Image::Draw(LoadHandle_[BackImage_]);
        }
    }

}

//開放
void GoalStaging::Release()
{
    //Load 開放
    for (int i = LOAD_MIN + 1; i < LOAD_MAX; i++)
    {
        LoadHandle_[i] = INITIAL_ERROR_VALUE;
    }
}

//時間管理
void GoalStaging::Timer()
{
    time_++;

    //TIMEまでカウント
    if (time_ >= TIME)
    {
        timer_ = true;
        time_ = 0;
    }
}

//クリア判定
void GoalStaging::ClearJudge()
{
    //コインを入手してクリアをしたらフラグを立てる
    switch (Game::SelectStage)
    {
    case STAGE_NUMBER_1:
        if (game.getState(Game::stage1.GetCoin)) game.setState(Game::stage1.Clear); break;
    case STAGE_NUMBER_2:
        if (game.getState(Game::stage2.GetCoin)) game.setState(Game::stage2.Clear); break;
    case STAGE_NUMBER_3:
        if (game.getState(Game::stage3.GetCoin)) game.setState(Game::stage3.Clear); break;
    }
}
