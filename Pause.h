#pragma once
#include "Engine/GameObject.h"
#include "Engine/SceneManager.h"
#include "Engine/Image.h"
#include "Engine/Input.h"

//一時停止を管理するクラス
class Pause : public GameObject
{

    //ロード用変数
    enum Load
    {
        LOAD_MIN = 0,
        PauseBackImage_,    //pauseの背景
        ContinueImage_,     //プレイシーンに戻るボタン
        BackMenuImage_,     //メニューシーンに戻るボタン
        SelectFrameImage_,  //選択用フレーム
        LOAD_MAX
    };

    //enumを入れる配列
    int LoadHandle_[LOAD_MAX];


    //メンバ変数
    int select_;    //選択
    int alpha_;     //透明度

    Transform Continue;     //プレイシーンに戻る用
    Transform BackMenu;     //メニューシーンに戻る用

    //定数
    const XMFLOAT3 CONTINUE_POS = XMFLOAT3(-0.3f, 0, 0); //「プレイシーンに戻る」画像位置
    const XMFLOAT3 BACKMENU_POS = XMFLOAT3(0.3f, 0, 0);  //「メニューシーンに戻る」画像位置
public:
    //コンストラクタ
    Pause(GameObject* parent);

    //デストラクタ
    ~Pause();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;

    //メニューシーンに戻るかどうか
    void SetSelect(int select) { select_ = select; }
    int GetSelect() { return select_; }
};


