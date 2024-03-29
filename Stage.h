#pragma once
#include "Engine/GameObject.h"
#include "Engine/Model.h"
#include "Engine/Image.h"
#include "Game.h"
#include "Number.h"
#include "PolygonCollider.h"
#include "Sign.h"
#include "StageSelectScene.h"
#include <vector>
using namespace std;

class Scissors;

enum Stage1_Sound {
    St1_Glass = 0,
    St1_Wood = 1,
    St1_Max
};

enum Stage2_Sound {
    St2_Gravel = 0,
    St2_Stone = 1,
    St2_Max 
};

enum Stage3_Sound {
    St3_Iron = 0,
    St3_Sand = 1,
    St3_Volcano_Sand = 2,
    St3_Volcano = 3,
    St3_Max
};

//ハサミの刃を管理するクラス
class Stage : public GameObject
{
    //ロード用変数
    enum Load
    {
        LOAD_MIN = 0,
        StageModel_,   //ステージモデル
        BackImage_,    //背景
        NumberImage_,  //数字画像
        DengerImage_,  //危険画像
        Sound_,        //サウンド入れる変数
        LOAD_MAX
    };

    //enumを入れる配列
    int LoadHandle_[LOAD_MAX];

    //クラスのポインタ
    Number* pNumber_;
    Game game;
    Scissors* pScissors_;

    //各ステージのstartとgoalの座標を入れる変数
    XMFLOAT4 StGo;
    float startX;
    float startY;
    float goalX;
    float goalY;


    //コライダー（凸多角形を複数個組み合わせる）
    vector<PolygonCollider> colliders_;

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


    //定数
    //各ステージのアイテムモデル位置
    const XMFLOAT3 ST1_ITEMMODEL_POS = XMFLOAT3(51, 10, 0);
    const XMFLOAT3 ST2_ITEMMODEL_POS = XMFLOAT3(-1.5f, 17, 0);
    const XMFLOAT3 ST3_ITEMMODEL_POS = XMFLOAT3(50.5f, 15.5f, 0);

    //各ステージのスタートとゴールの位置
    const XMFLOAT4 ST1_START_GOAL_POS = XMFLOAT4(2, 0, 55, 4);
    const XMFLOAT4 ST2_START_GOAL_POS = XMFLOAT4(2, 0, 125, 0.36f);
    const XMFLOAT4 ST3_START_GOAL_POS = XMFLOAT4(3, 0, 138, 16);

    const XMFLOAT3 DENGER_IMAGE_POS = XMFLOAT3(0, 0.8f, 0); //Denger画像位置

    const int REPEL_DAMAGE = 5; //弾かれたときのダメージ
    const XMFLOAT2 NUMBER_POS = XMFLOAT2(0.06f, 0.8f);      //数字位置

public:
    
    bool RepelFlg;
    bool SinkFlg;


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
};