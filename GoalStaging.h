#pragma once
#include "Engine/GameObject.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/Image.h"
#include "Global.h"

//ゴール演出を管理するクラス
class GoalStaging : public GameObject
{
    Global gl;

    int hModel_;    //モデル番号

    int BackImage_;
    int CircleImage_;

    int EnterImage_;

    Transform CircleTrans;
    Transform EnterTrans;

    float size_;
    bool flg;
    bool Sflg;
    bool Aflg;

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
};