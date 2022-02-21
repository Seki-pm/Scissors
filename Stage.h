#pragma once
#include "Engine/GameObject.h"
#include "Global.h"
#include "PolygonCollider.h"
#include "Scissors.h"
#include <vector>

using namespace std;

//ハサミの刃を管理するクラス
class Stage : public GameObject
{
    int StageModel_;
    Global gl;

    //コライダー（凸多角形を複数個組み合わせる）
    vector<PolygonCollider> colliders_;


public:
    //コンストラクタ
    Stage(GameObject* parent);

    //デストラクタ
    ~Stage();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

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

    void Stage1();
    void Stage2();

};