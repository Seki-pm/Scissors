#pragma once
#include "Engine/GameObject.h"
#include "Engine/Input.h"
#include "Gauge.h"

class Scissors;

//HPを管理するクラス
class HP : public GameObject
{
    Gauge*  pGauge_;  //ゲージ描画用
    Scissors* pScissors_;


    //ロード用変数
    int GaugeImage_;    
    int GaugeFrameImage_;

    Transform FrameTrans;

    const XMFLOAT3 FRAME_POS;
    const int NORMAL_DAMAGE;
    const XMFLOAT2 HP_IMAGE_POS;


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