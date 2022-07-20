#pragma once
#include "Engine/GameObject.h"
#include "Engine/SceneManager.h"
#include "Engine/Image.h"
#include "Engine/Input.h"
#include "Global.h"
#include "Scissors.h"
#include "StageSelectScene.h"

//ゲームオーバーを管理するクラス
class GameOver : public GameObject
{
    //ロード用変数
    enum Load
    {
        LOAD_MIN = 0,
        GameOverBackImage_,    //GameOverの背景(不透明)
        BackMenuImage_,        //ステージ選択シーンに戻るボタン
        RetryImage_,           //リトライボタン
        SelectFrameImage_,     //選択用フレーム
        LOAD_MAX
    };

    //enumを入れる配列
    int LoadHandle_[LOAD_MAX];


    //メンバ変数
    int select_;    //選択
    int alpha_;     //透明度

    Transform Retry;     //リトライ用
    Transform BackMenu;  //ステージ選択シーンに戻る用

    //定数
    const XMFLOAT3 RETRY_POS = XMFLOAT3(-0.3f, 0, 0);   //「リトライ」位置
    const XMFLOAT3 BACKMENU_POS = XMFLOAT3(0.3f, 0, 0); //「ステージ選択に戻る」位置

public:
    Scissors* pScissors_;

    //コンストラクタ
    GameOver(GameObject* parent);

    //デストラクタ
    ~GameOver();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;

    //引数をSET&GET
    void SetSelect(int select);
    int GetSelect() { return select_; }
};

