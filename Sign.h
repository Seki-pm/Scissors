#pragma once
#include "Engine/GameObject.h"
#include "Engine/Model.h"

//操作説明オブジェクトを管理するクラス
class Sign : public GameObject
{
    int TipsHandle_;
    int TipsHandle2_;
    int TipsHandle3_;
    int TipsHandle4_;
    int TipsHandle5_;

    float size_;

public:
    //コンストラクタ
    Sign(GameObject* parent);

    //デストラクタ
    ~Sign();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;
};