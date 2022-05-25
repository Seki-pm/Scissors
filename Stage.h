#pragma once
#include "Engine/GameObject.h"
#include "Global.h"
#include "PolygonCollider.h"
#include "Scissors.h"
#include "Sign.h"
#include "Engine/Model.h"
#include "Engine/Image.h"
#include <vector>

using namespace std;

//ハサミの刃を管理するクラス
class Stage : public GameObject
{

    int StageModel_;
    int BackImage_;

    Global gl;

    //コライダー（凸多角形を複数個組み合わせる）
    vector<PolygonCollider> colliders_;

    // 一つ一つの地形の面の頂点を入れる
    PolygonCollider pc1,  pc2,  pc3,  pc4,  pc5,  pc6,
                    pc7,  pc8,  pc9,  pc10, pc11, pc12,
                    pc13, pc14, pc15, pc16, pc17, pc18,
                    pc19, pc20, pc21, pc22, pc23, pc24,
                    pc25, pc26, pc27, pc28, pc29, pc30;

public:
    //コンストラクタ
    Stage(GameObject* parent);

    //デストラクタ
    ~Stage();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //読み込み
    void Load(const int st);

    //描画
    void Draw() override;

    //開放
    void Release() override;

    //指定した点がステージとぶつかっているか調べる
    //引数：position　調べたい位置
    bool IsHit(XMFLOAT3 position);

    //先端以外がステージとぶつかっているか調べる
    //
    bool IsHit(PolygonCollider target, XMMATRIX world);

    //衝突した辺の法線と衝突点を調べる
    void GetNormal(XMFLOAT3 p1, XMFLOAT3 p2, XMFLOAT3* normal, XMFLOAT3* hitPoint);

    //Stage
    void Stage1();
    void Stage2();
    void Stage3();

    //弾く時の管理
    XMFLOAT3 Repel();

    void RepelCheck(int i);
    void SinkCheck(int i);

    //沈む時の管理
    XMFLOAT3 Sink();
};