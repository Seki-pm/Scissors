#pragma once
#include "Engine/GameObject.h"
#include "Engine/SphereCollider.h"
#include "Engine/SceneManager.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/Audio.h"
#include "StageSelectScene.h"
#include "Global.h"


//コインを管理するクラス
class ItemModel : public GameObject
{
    int Coin_;
    int rotate; //回転数

    int Coin_Sound;

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