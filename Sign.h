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

    //看板のenumを入れる変数
    int TipsModel_[Tips_MAX];

    //画像を入れる変数
    int Tutorial_;   //チュートリアル
    int Tutorial2_;

    Global gl;

    //各Transform
    Transform SignTrans;
    Transform SignTrans2;
    Transform SignTrans5;

    //定数
    //看板の位置
    const XMFLOAT3 SIGN1_POS = XMFLOAT3(2, 0, 0);
    const XMFLOAT3 SIGN2_POS = XMFLOAT3(8, 0, 0);
    const XMFLOAT3 SIGN3_POS = XMFLOAT3(11, 0, 0);
    const XMFLOAT3 SIGN4_POS = XMFLOAT3(14, 0, 0);
    const XMFLOAT3 SIGN5_POS = XMFLOAT3(28, 0, 0);
    const XMFLOAT3 SIGN6_POS = XMFLOAT3(31, 0, 0);

    const XMFLOAT3 SIGN_SIZE = XMFLOAT3(1.7f,1.7f,1.7f); //看板のサイズ

    const XMFLOAT3 TUTORIAL_POS = XMFLOAT3(0,   0.65f, 0);   //チュートリアルの位置
    const XMFLOAT3 TUTORIAL_SCA = XMFLOAT3(0.5f, 0.5f, 0.5f); //チュートリアルのサイズ
    
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