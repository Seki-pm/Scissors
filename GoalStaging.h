#pragma once
#include "Engine/GameObject.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/Image.h"
#include "Global.h"

//ゴール演出を管理するクラス
class GoalStaging : public GameObject
{
    Global gl; //globalを使う

    int BalloonModel_;    //モデル番号

    //画像ロード用
    int BackImage_;
    int CircleImage_;
    int EnterImage_;

    //各Transform
    Transform CircleTrans;
    Transform EnterTrans;
    Transform BalloonTrans;

    //サイズ
    float size_;

    //フラグ
    bool StagingFlg;
    bool StringFlg;

    //時間管理
    int timer;

public:
    //コンストラクタ
    GoalStaging(GameObject* parent);

    //デストラクタ
    ~GoalStaging();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;

    //タイマー
    void Timer();
};