#pragma once
#include "Engine/GameObject.h"
#include "Engine/Model.h"

//ゴール演出を管理するクラス
class GoalStaging : public GameObject
{
    int hModel_;    //モデル番号
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