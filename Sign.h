#pragma once
#include "Engine/GameObject.h"
#include "Engine/Model.h"
#include "Engine/Image.h"
#include "Global.h"

//操作説明オブジェクトを管理するクラス
class Sign : public GameObject
{
    //モデルを入れる変数
    int TipsModel_;
    int TipsModel2_;
    int TipsModel3_;
    int TipsModel4_;
    int TipsModel5_;

    //画像を入れる変数
    int Tutorial_;
    int Tutorial2_;

    float size_;

    Global gl;

    Transform SignTrans;
    Transform SignTrans2;
    Transform SignTrans5;

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