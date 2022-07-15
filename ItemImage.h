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

    SceneManager* pSceneManager_;

    //定数
    //const XMFLOAT3 FRAME_SIZE = XMFLOAT3(0.3f, 0.3f, 0.3f);  //フレームのサイズ
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
