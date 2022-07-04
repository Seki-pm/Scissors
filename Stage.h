#pragma once
#include "Engine/GameObject.h"
#include "Engine/Model.h"
#include "Engine/Image.h"
#include "Global.h"
#include "PolygonCollider.h"
#include "Sign.h"
#include "Scissors.h"
#include "StageSelectScene.h"
#include <vector>
using namespace std;

class Scissors;

enum Stage1_Sound {
    St1_Glass = 1,
    St1_Wood = 2,
    St1_Max
};

//ハサミの刃を管理するクラス
class Stage : public GameObject
{
    int StageModel_; //ステージモデル
    int BackImage_;  //背景
    int Sound_;

    Global gl;
    Scissors* pScissors_;

    //コライダー（凸多角形を複数個組み合わせる）
    vector<PolygonCollider> colliders_;

    //サウンド(Stageごとのサウンドを入れる)
    vector<int> sounds_;

    // 一つ一つの地形の面の頂点を入れる
    PolygonCollider pc1, pc2, pc3, pc4, pc5, pc6,
                    pc7, pc8, pc9, pc10, pc11, pc12,
                    pc13, pc14, pc15, pc16, pc17, pc18,
                    pc19, pc20, pc21, pc22, pc23, pc24,
                    pc25, pc26, pc27, pc28, pc29, pc30,
                    pc31, pc32, pc33, pc34, pc35, pc36,
                    pc37, pc38, pc39, pc40, pc41, pc42,
                    pc43, pc44, pc45, pc46, pc47, pc48,
                    pc49, pc50;

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
    void Load(const int stage);

    //描画
    void Draw() override;

    //開放
    void Release() override;

    //指定した点がステージとぶつかっているか調べる
    //引数：position　調べたい位置
    bool IsHit(XMFLOAT3 position);

    //先端以外がステージとぶつかっているか調べる
    //引数：ぶつかっているコライダ
    //　　　ワールド座標
    bool IsHit(PolygonCollider target, XMMATRIX world);

    //衝突した辺の法線と衝突点を調べる
    void GetNormal(XMFLOAT3 p1, XMFLOAT3 p2, XMFLOAT3* normal, XMFLOAT3* hitPoint);

    //ステージのコライダ設定
    void Stage1();
    void Stage2();
    void Stage3();

    //ステージの読み込み
    void Stage1Load();
    void Stage2Load();
    void Stage3Load();

    //弾く時の値
    XMFLOAT3 Repel(){ return XMFLOAT3(0.1f,0.3f,0); }

    //弾く床をチェック
    //引数：チェックする番号
    void RepelCheck(int i);

    //沈む時の値
    XMFLOAT3 Sink() { return XMFLOAT3(0,-0.01f,0); }

    //沈む床をチェック
    //引数：チェックする番号
    void SinkCheck(int i);

    //音を鳴らす
    void Landing();
};