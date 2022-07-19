#pragma once
#include "Engine/GameObject.h"
#include "Engine/SphereCollider.h"
#include "Engine/SceneManager.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/Audio.h"
#include "Global.h"
#include "StageSelectScene.h"

//コインを管理するクラス
class ItemModel : public GameObject
{
    int CoinModel_; //コインモデル用変数
    int CoinSound_; //コイン取得時の音

    //定数
    const float ROTATION_SPEED = 16.6f;    //回転速度
    const float UP_DISTANCE = 0.01f;       //上がる距離
    const int   ROTATION_NUMBER = 8;       //回転数

    const XMFLOAT3 ITEM_SIZE = XMFLOAT3(1.1f, 1.1f, 1.1f); //アイテムのサイズ

public:
    //コンストラクタ
    ItemModel(GameObject* parent);

    //デストラクタ
    ~ItemModel();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;

    //何かに当たった
    //引数：pTarget 当たった相手
    void OnCollision(GameObject* pTarget) override;

    //アニメーション
    void Animation();
};