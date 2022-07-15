#pragma once
#include "Engine/GameObject.h"
#include "Engine/SceneManager.h"
#include "Engine/Image.h"
#include "Engine/Input.h"
#include "StageSelectScene.h"
#include "Global.h"
#include "Scissors.h"

//ゲームオーバーを管理するクラス
class GameOver : public GameObject
{
    int GameOverBackImage_;    //GameOverの背景(不透明)
    int BackMenuImage_;     //ステージ選択シーンに戻るボタン
    int RetryImage_;        //リトライボタン
    int SelectFrameImage_;  //選択用フレーム

    //メンバ変数
    int select_;    //選択
    int alpha_;     //透明度

    Transform Retry;     //リトライ用
    Transform BackMenu;  //ステージ選択シーンに戻る用

    //定数
    const XMFLOAT3 RETRY_POS = XMFLOAT3(-0.3f, 0, 0);   //「リトライ」位置
    const XMFLOAT3 BACKMENU_POS = XMFLOAT3(0.3f, 0, 0); //「ステージ選択に戻る」位置

public:
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

