#pragma once
#include "Engine/GameObject.h"
#include "Engine/Input.h"
#include "Gauge.h"

class Scissors;

//HPを管理するクラス
class HP : public GameObject
{
    //アクセス用ポインタ
    Gauge*  pGauge_; 
    Scissors* pScissors_;


    //ロード用変数
    int GaugeImage_;      //ゲージ画像
    int GaugeFrameImage_; //ゲージフレーム画像

    Transform FrameTrans;

    //定数
    const XMFLOAT2 HP_IMAGE_POS = XMFLOAT2(-0.99f, 0.85f); //HPゲージ位置
    const XMFLOAT3 FRAME_POS = XMFLOAT3(-0.59f, 0.88f, 0); //フレーム位置
    const float    HAS_DAMAGE = 0.5f; //ダメージを食らう高さ
    const int      NORMAL_DAMAGE = 1; //通常のダメージ

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