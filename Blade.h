#pragma once
#include "Engine/GameObject.h"
#include "PolygonCollider.h"

class Stage;

//ハサミの刃を管理するクラス
class Blade : public GameObject
{
    int BladeModel_;

public:
    bool isPrick;   //地面に刺さってるかどうか
    PolygonCollider collider;   //先端以外の当たり判定
    Stage* pStage_;  //ステージのアドレス

    
public:
    //コンストラクタ
    Blade(GameObject* parent);

    //デストラクタ
    ~Blade();

    //初期化
    void Initialize() override;

    // ロード
    // 引数：0かそれ以外かで左右の刃の判別を行う
    void Load(const int lr);

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;



    //ハサミの開閉
    void Open(int angle);

    //刺さってるかどうか
    bool IsPrick() { return isPrick; }

    //先端位置を取得
    XMFLOAT3 GetTipPoint();

};