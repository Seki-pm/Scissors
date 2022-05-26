#pragma once
#include "Engine/GameObject.h"
#include "Engine/SceneManager.h"
#include "Engine/Image.h"
#include "Global.h"


//アイテムの取得の有無の画像を管理するクラス
class ItemImage : public GameObject
{
    //画像ロード用
    int FrameImage_;
    int CoinImage_;

public:
    //コンストラクタ
    ItemImage(GameObject* parent);

    //デストラクタ
    ~ItemImage();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;
};
