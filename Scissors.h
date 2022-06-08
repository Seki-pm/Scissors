#pragma once
#include "Engine/GameObject.h"
#include "Engine/SphereCollider.h"
#include "Engine/Input.h"
#include "Engine/Camera.h"
#include "Engine/Fbx.h"
#include "Engine/Audio.h"
#include "Blade.h"
#include "Global.h"
#include "HP.h"
#include "GameOver.h"
#include "Stage.h"
#include "StageSelectScene.h"
#include <vector>
#include "Number.h"


//ハサミを管理するクラス
class Scissors : public GameObject
{
    int NumberImage_;
    int DengerImage_;

    //ブレードが２つ
    Blade* pBlade_L , *pBlade_R;
    Stage* pStage_;
    Number* pNumber_;

    XMFLOAT3 move_;         //移動
    XMFLOAT3 jumpDirection_; //ジャンプ方向（刺さってる地面の法線）
    XMFLOAT3 nowPivotPoint_; //現在の刺さっている場所

    float AnglePass_;  //角度を送る
    float GLAVITY; //重力

    bool CalcFlg; //計算のフラグ
    bool FallFlg; //落下フラグ
    bool SoundFlg; //音フラグ

    float JumpPower;

    //弾かれた時用
    int Key;
    float TransPos_Y;
    float powerY;
    float powerX;
    bool IsRepel;

    //沈んだ時用
    bool IsSink;
    float MoveY;
    int CountDown;
    int Timer_;

    //SE
    int Land_Glass;     
    int Land_Wood;
      
    int Land_Gravel;   
    int Land_Stone;

    int Land_Iron;      
    int Land_Sand; 
    int Land_Volcano_Sand;
    int Land_Volcano;


    ///////////////private関数//////////////////////////////////////
    //開閉
    void OpenClose();

    //回転
    void Rotation();

    //左右移動
    void Move();

    //ジャンプと落下
    void JumpAndFall();

    ////////////////////////////////////////////////////////////////////


public:
    //コンストラクタ
    Scissors(GameObject* parent);

    //デストラクタ
    ~Scissors();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;

    void SetJumpDirection(XMFLOAT3 jumpDirection) { jumpDirection_ = jumpDirection; }

    //反射
    void Reflection();

    //位置をセットする
    void SetPosition();

    //回転限度
    void RotateMax();

    //始めに戻る
    void Restart();

    //弾かれた時の動き
    void RepelMove();

    //沈んだ時の動き
    void SinkMove();

    void InitSound();
    void Landing();

    void Input();

    //画像の初期化
    void InitImage();
};