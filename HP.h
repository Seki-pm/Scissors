#pragma once
#include "Engine/GameObject.h"
#include "Engine/Input.h"
#include "DrawNumber.h"
#include "DrawGauge.h"

//HPを管理するクラス
class HP : public GameObject
{
    DrawNumber* pNumber_; //数字描画用
    DrawGauge*  pGauge_;  //ゲージ描画用

    //ロード用変数
    int NumberHandle_;   
    int GaugeHandle_;    
    int GaugeFrame_;

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

    //HPを計算
    void HPCalc();
};