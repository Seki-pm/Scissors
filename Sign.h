#pragma once
#include "Engine/GameObject.h"
#include "Engine/Model.h"
#include "Engine/Image.h"
#include "Global.h"

//操作説明オブジェクトを管理するクラス
class Sign : public GameObject
{
    enum Tips {
        Tips_1 = 1,
        Tips_2,
        Tips_3,
        Tips_4,
        Tips_5,
        Tips_6,
        Tips_MAX
    };

    //モデルを入れる変数
    int TipsModel_[Tips_MAX];

    //画像を入れる変数
    int Tutorial_;
    int Tutorial2_;

    Global gl;

    Transform SignTrans;
    Transform SignTrans2;
    Transform SignTrans5;


    //定数
    //各看板の位置
    const XMFLOAT3 SIGN1_POS;
    const XMFLOAT3 SIGN2_POS;
    const XMFLOAT3 SIGN3_POS;
    const XMFLOAT3 SIGN4_POS;
    const XMFLOAT3 SIGN5_POS;
    const XMFLOAT3 SIGN6_POS;

    const XMFLOAT3 SIGN_SIZE; //看板のサイズ

    const XMFLOAT3 TUTORIAL_POS; //チュートリアルの位置
    const XMFLOAT3 TUTORIAL_SCA; //チュートリアルのサイズ

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