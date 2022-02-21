#pragma once
#include "Engine/GameObject.h"
#include "Engine/Input.h"
#include "DrawNumber.h"
#include "DrawGauge.h"

//HPを管理するクラス
class HP : public GameObject
{
    DrawNumber* pNumber_;
    DrawGauge*  pGauge_;

    int NumberHandle_;
    int GaugeHandle_;
    int GaugeFrame_;

    int MaxHp;

    Transform FrameTrans;

public:
    //コンストラクタ
    HP(GameObject* parent);

    //デストラクタ
    ~HP();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;

    void HPCalc();
};