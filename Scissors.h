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
#include "Stage.h"
#include "StageSelectScene.h"
#include <vector>

//ハサミを管理するクラス
class Scissors : public GameObject
{
    //ブレードが２つ
    Blade* pBlade_L , *pBlade_R;
    Stage* pStage_;

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
    int Timer_;
    int CountDown;
    int CountPass;


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
    bool IsJump;
    int CurrentHP;


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

    //地面の法線をセット
    void SetJumpDirection(XMFLOAT3 jumpDirection) { jumpDirection_ = jumpDirection; }
    XMFLOAT3 GetJumpDirection() { return jumpDirection_; }

    //反射
    void Reflection();

    //位置をセットする
    void SetPosition()
    {
        Global gl;
        gl.SetTransPos(transform_.position_);
    }

    //回転限度
    void RotateMax();

    //始めに戻る
    void Restart();

    //弾かれた時の動き
    void RepelMove();

    //沈んだ時の動き
    void SinkMove();

    //足音を鳴らす
    void Landing();

    //カウントダウンを送る
    void SetCountDown(int countdown) { CountPass = countdown; }
    int GetCountDown() { return CountPass; };
};