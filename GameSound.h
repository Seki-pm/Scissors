#pragma once
#include "Engine/GameObject.h"


//ゲームのサウンドを管理するクラス
class GameSound : public GameObject
{




public:
    //コンストラクタ
    GameSound(GameObject* parent);

    //デストラクタ
    ~GameSound();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;

    void Landing();
};