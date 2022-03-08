#pragma once
#include "Engine/GameObject.h"
#include "Engine/SceneManager.h"
#include "Engine/Image.h"
#include "Engine/Input.h"
#include "Global.h"
#include "Scissors.h"

//ゲームオーバーを管理するクラス
class GameOver : public GameObject
{
    int GameOverBackImage_;    //GameOverの背景(不透明)
    int BackMenuImage_;     //ステージ選択シーンに戻るボタン
    int RetryImage_;        //リトライボタン
    int SelectFrameImage_;

    Scissors* pScissors;

    //メンバ変数
    int select_;    //選択
    int alpha_;

    Transform Retry;     //リトライ用
    Transform BackMenu;  //ステージ選択シーンに戻る用

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

    //メニューシーンに戻るかどうか
    void SetSelect(int select);
};

