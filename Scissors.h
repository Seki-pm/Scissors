#pragma once
#include "Engine/GameObject.h"
#include "Engine/SphereCollider.h"
#include "Engine/Input.h"
#include "Engine/Camera.h"
#include "Engine/Fbx.h"
#include "Engine/Audio.h"
#include "Blade.h"
#include "Game.h"
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

    XMFLOAT3 move_;          //移動
    XMFLOAT3 jumpDirection_; //ジャンプ方向（刺さってる地面の法線）
    XMFLOAT3 nowPivotPoint_; //現在の刺さっている場所

    float AnglePass_;  //角度を送る
    float GLAVITY;     //重力

    bool CalcFlg;  //計算のフラグ
    bool FallFlg;  //落下フラグ
    bool SoundFlg; //音フラグ


    float JumpPower;

    //弾かれた時用
    int Key;      //方向定める
    float powerY; 
    float powerX;
    bool IsRepel;

    //沈んだ時用
    bool IsSink;
    float MoveY;
    int Timer_;
    int CountDown;
    int CountPass;

    //定数
    const int FALL_MAX = -8;        //落下限界
    
    const float JUMP_POWER = 0.2f;  //ジャンプ力
    const float NORMAL_JUMP_POWER = 0.1f; //通常のジャンプ力
    const float SINK_JUMP_POWER   = 0.001f; //沈んだ時のジャンプ力

    const int SINK_TIMER = 360;           //沈むタイマー
    const int SINK_TIMER_MIN = 60;       //タイマーの最小値

    const XMFLOAT3 INIT_POSITION = XMFLOAT3(0, 1, 0); //初期位置
    const XMFLOAT3 INIT_ROTATE = XMFLOAT3(0, 0, 0);   //初期回転角度
    
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
    bool  IsJump;    //ジャンプできるか
    int   CurrentHP; //現在HP
    float JumpStart; //ジャンプスタート位置
    float JumpEnd;   //ジャンプ着地位置


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
        Game game;
        game.SetTransPos(transform_.position_);
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