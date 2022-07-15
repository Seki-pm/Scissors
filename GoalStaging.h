#pragma once
#include "Engine/GameObject.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/Image.h"
#include "Engine/Audio.h"
#include "Global.h"

//ゴール演出を管理するクラス
class GoalStaging : public GameObject
{
    Global gl; //globalを使う

    int BalloonModel_;    //モデル番号
    int GoalSound_;  //サウンド用

    //画像ロード用
    int BackImage_;
    int CircleImage_;
    int EnterImage_;

    //各Transform
    Transform CircleTrans;
    Transform EnterTrans;
    Transform BalloonTrans;

    //サイズ(暗転処理用)
    float size_;

    //フラグ
    bool StagingFlg;
    bool StringFlg;

    //時間管理
    int time_;

    //定数
    const int TIME = 90;  //シーン遷移までの時間
    const float SIZE_MIN = 1.4f; //縮小最小値
    const float SCALE_DOWN_VAL = 0.15f; //サイズ縮小の値

    const XMFLOAT3 BAL_ENT_SIZE = XMFLOAT3(0.8f, 0.8f, 0.8f);   //風船、Enterのサイズ
    const XMFLOAT3 ENTER_POS = XMFLOAT3(0.1f, 0.1f, 0.f);       //Enterの位置
    const XMFLOAT3 BACKIMAGE_SIZE = XMFLOAT3(1.4f, 1.4f, 1.4f); //背景サイズ

public:
    bool timer_;

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