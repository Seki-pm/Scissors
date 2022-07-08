#include "Scissors.h"

#define NormalJumpPower 0.1f;
#define SinkJumpPower 0.001f;
#define SinkTimer 360;

//コンストラクタ
Scissors::Scissors(GameObject* parent)
    :GameObject(parent, "Scissors"), 
    jumpDirection_(XMFLOAT3(0,0,0)),nowPivotPoint_(XMFLOAT3(0,0,0)), move_(XMFLOAT3(0, 0, 0)),
    pBlade_L(nullptr), pBlade_R(nullptr),pStage_(nullptr),
    FallFlg(true),     CalcFlg(false),   SoundFlg(false),  IsRepel(false),    IsSink(false),
    CountDown(0),      MoveY(0),         powerX(0),        powerY(0),         TransPos_Y(0),
    AnglePass_(0.0f),  Key(0),           IsJump(true),
    Timer_(360),       JumpPower(0.1f),  GLAVITY(0.03f)
{
}

//デストラクタ
Scissors::~Scissors()
{
}

//初期化
void Scissors::Initialize()
{
    //Loadの()内が0かそれ以外かで左右の刃を判断
    pBlade_L = Instantiate<Blade>(this);    //左刃
    pBlade_L->Load(0);

    pBlade_R = Instantiate<Blade>(this);    //右刃
    pBlade_R->Load(1);

    //RBladeを45°傾ける
    pBlade_R->SetRotateZ(45);

    //初期位置
    transform_.position_ = Global::InitPos;

    //アイテム取得用のコライダーを設定
    SphereCollider* collision =
        new SphereCollider(XMFLOAT3(0, 0, 0), 0.6f);
    AddCollider(collision);

    CurrentHP = Global::MAXHP;
}

//更新
void Scissors::Update()
{

    if (!Global::GameOver && !Global::Pause)
    {
        //ハサミの開閉
        OpenClose();

        //ハサミの回転
        Rotation();

        //左右移動
        Move();

        //ジャンプと落下
        JumpAndFall();

        //座標を送る
        SetPosition();
    }
 

    //スタートからやり直し（リトライ）
    if (Input::IsKeyDown(DIK_R))
    {
        Restart();
    }



    //落下したら || 沈んだら
    if (transform_.position_.y <= -8 && FallFlg
        || 60 >= Timer_)
    {
        move_ = XMFLOAT3(0, 0, 0);
        Global::GameOver = true;
        Global::IsGameOver = true;
        FallFlg = false;
        Global::SinkFlg = false;
    }

    //床ギミック
    RepelMove();  //はじく
    SinkMove();   //沈む
}


//ハサミの開閉(中心回転)
void Scissors::OpenClose()
{
    int angle = 0;

    if (Input::IsKey(DIK_W))    //開く
    {
        angle = 2;
    }
    if (Input::IsKey(DIK_S))    //閉じる
    {
        angle = -2;
    }

    //開閉
    pBlade_L->Open(-angle);
    pBlade_R->Open(angle);


    //角度制限
    XMVECTOR LMax = { 1,0,0,0 };
    XMVECTOR RMax = { 1,0,0,0 };
     //Z軸で回転する行列
    XMMATRIX rotateL = XMMatrixRotationZ(XMConvertToRadians(pBlade_L->GetRotate().z));
    XMMATRIX rotateR = XMMatrixRotationZ(XMConvertToRadians(pBlade_R->GetRotate().z));
     //行列をVECTORへ
    LMax = XMVector3TransformCoord(LMax, rotateL);
    RMax = XMVector3TransformCoord(RMax, rotateR);
     //最終的な角度(内積から求める)
    float ang = acos(XMVectorGetX(XMVector3Dot(LMax, RMax)));

    //170度以上または2度未満ならもどす
    if (XMConvertToDegrees(ang) > 170|| XMConvertToDegrees(ang) < 2)   
    {
        pBlade_L->Open(angle);
        pBlade_R->Open(-angle);
    }
}

//ハサミの回転(刃先回転)
void Scissors::Rotation()
{
    Blade* pPrickBlade = nullptr;   //刺さってる方の刃

    if (pBlade_L->IsPrick() && pBlade_R->IsPrick())     //両方刺さってたら回転できない
    {
        return;
    }
    else if (pBlade_L->IsPrick())       //左が刺さってる
    {
        pPrickBlade = pBlade_L;
    }
    else        
    {
        pPrickBlade = pBlade_R;       //右が刺さってる
    }

    //刺さってる刃の先端位置（回転前）
    XMFLOAT3 prevPivotPoint = pPrickBlade->GetTipPoint();


    //回転
    int angle = 0;
    if (Input::IsKey(DIK_LEFT))
    {
        if (AnglePass_ > 10)
        {
            angle = 2;
        }
    }
    if (Input::IsKey(DIK_RIGHT))
    {
        if (AnglePass_ < 150)
        {
            angle = -2;
        }
    }
    transform_.rotate_.z += angle;


    //刺さってる刃の先端位置（回転後）
    nowPivotPoint_ = pPrickBlade->GetTipPoint();

    //先端位置がずれた分移動させて戻す
    transform_.position_.x += prevPivotPoint.x - nowPivotPoint_.x;
    transform_.position_.y += prevPivotPoint.y - nowPivotPoint_.y;
    transform_.position_.x += prevPivotPoint.z - nowPivotPoint_.z;
}

//左右移動
void Scissors::Move()
{
    if (!pBlade_L->IsPrick() && !pBlade_R->IsPrick() && IsJump)     //どっちも刺さってなければ
    {
        if (Input::IsKey(DIK_D))
        {
            Key = 1;
            transform_.position_.x += 0.01f;
            move_.x += 0.01f;
        }
        if (Input::IsKey(DIK_A))
        {
            Key = -1;
            transform_.position_.x -= 0.01f;
            move_.x -= 0.01f;
        }
    }
}

//ジャンプと落下
void Scissors::JumpAndFall()
{
    HP* pHP = (HP*)FindObject("HP");

    //どっちも刺さってなければ
    if (!pBlade_L->IsPrick() && !pBlade_R->IsPrick())
    {
        //落下
        transform_.position_.x += move_.x;
        transform_.position_.y += move_.y;
        transform_.position_.z += move_.z;

        //重力
        move_.y -= GLAVITY;

        //着地地点の高さ
        Global::JumpEnd = transform_.position_.y;

        //着地音
        SoundFlg = true;
    }

    //どっちか刺さってたら
    else
    {
        //ジャンプ方向を入れる(はじく処理の方向)
        if (move_.x < 0) Key = 1;        //右に動いている時は左へ
        else if(move_.x > 0)  Key = -1;  //左に動いている時は右へ　弾く

        //動きを止める
        move_.x = 0;
        move_.y = 0;
        move_.z = 0;

        if (CalcFlg)
        {
            //現在のHPを計算
            pHP->HPCalc();
            CalcFlg = false;
        }

        if (SoundFlg)
        {
            SoundFlg = false;
            Landing();
        }


        //壁かどうかでSPACEの入力を変える
        if (jumpDirection_.x == 1 || jumpDirection_.x == -1)
        {
            //壁なら長押しで反応なし
            if (Input::IsKeyDown(DIK_SPACE) && IsJump)
            {
                //地面の法線よりちょっと上向きにジャンプ
                move_.x = jumpDirection_.x * 0.2f;
                move_.y = jumpDirection_.y * 0.2f + 0.2f;
                move_.z = jumpDirection_.z * 0.2f;

                //ここで１回動かしておかないと、次のフレームでも刺さったままで飛べない
                transform_.position_.x += move_.x;
                transform_.position_.y += move_.y;
                transform_.position_.z += move_.z;

                //いったん抜く
                pBlade_L->isPrick = false;
                pBlade_R->isPrick = false;

                //ジャンプの初めの高さ
                Global::JumpStart = transform_.position_.y;
                CalcFlg = true;

            }
        }
        //壁ではないなら長押しで進める
        else if (Input::IsKey(DIK_SPACE) && IsJump)
        {
            //地面の法線よりちょっと上向きにジャンプ
            move_.x = jumpDirection_.x * 0.2f;
            move_.y = jumpDirection_.y * 0.2f + JumpPower;
            move_.z = jumpDirection_.z * 0.2f;

            //ここで１回動かしておかないと、次のフレームでも刺さったままで飛べない
            transform_.position_.x += move_.x;
            transform_.position_.y += move_.y;
            transform_.position_.z += move_.z;

            //いったん抜く
            pBlade_L->isPrick = false;
            pBlade_R->isPrick = false;

            //ジャンプの初めの高さ
            Global::JumpStart = transform_.position_.y;
            CalcFlg = true;

        }

        //回転限度を設定
        RotateMax();
    }
}

//描画
void Scissors::Draw()
{
}

//開放
void Scissors::Release()
{
}

//反射
void Scissors::Reflection()
{
    int cnt = 0;
    float value = 0.1f;

    //transform_.position_.x -= move_.x;
    //transform_.position_.y -= move_.y;
    //move_.x *= -0.3f;
    //move_.y *= -0.3f;
    //move_.x = 0;
    //move_.y = 0;

    while (true)
    {
        // ① xを1フレーム前の位置に戻す
        transform_.position_.x -= move_.x;

        // ② 再度当たり判定を行う Y軸が当たっているかのチェック
        if (pBlade_L->pStage->IsHit(pBlade_L->collider, GetWorldMatrix()) ||
            pBlade_R->pStage->IsHit(pBlade_R->collider, GetWorldMatrix()))
        {
            // ③ xを移動後の状態に戻して
            //    yを1フレーム前の位置にする 
            transform_.position_.x += move_.x;
            transform_.position_.y -= move_.y;
        }
        // ぶつかっていないなら終わり
        else {
            move_.x = 0;
            move_.y = 0;
            break;
       }
        // ④ 再度当たり判定を行う  X軸が当たっているかのチェック
        if (pBlade_L->pStage->IsHit(pBlade_L->collider, GetWorldMatrix()) ||
            pBlade_R->pStage->IsHit(pBlade_R->collider, GetWorldMatrix()))
        {
            // ⑤ XもYも1フレーム前に戻す
            transform_.position_.x -= move_.x;
        }
        // ぶつかっていないなら終わり
        else{
            move_.x = 0;
            move_.y = 0;
            break;
        }
        cnt++;

        //判定が20回以上だと
        if (cnt >= 20)
        {
            //強制的に値を入れてScissorsを動かす(詰み防止対策)
            move_.x += value;
            move_.y -= value;
        }

        //ぶつかっている間HPを減らす(詰み防止対策)
        CurrentHP--;
    }
}

//回転限度を求める計算
void Scissors::RotateMax()
{
    //レイのスタート位置と方向を求める
    RayCastData data;
    data.start = transform_.position_;
    data.dir.x = nowPivotPoint_.x - transform_.position_.x;
    data.dir.y = nowPivotPoint_.y - transform_.position_.y;
    data.dir.z = nowPivotPoint_.z - transform_.position_.z;

    //回転の角度の計算をする
    XMVECTOR normal = XMLoadFloat3(&jumpDirection_);     //XMFLOAT3 → XMVECTOR(法線)
    XMMATRIX Rotmat = XMMatrixRotationZ(45.5f);          //法線回転用の回転行列
    normal = XMVector3TransformCoord(normal, Rotmat);    //normalとRotmatをかける
    normal = XMVector3Normalize(normal);                 //normalを正規化
    XMVECTOR dir = XMLoadFloat3(&data.dir);              //XMFLOAT3 → XMVECTOR(レイのベクトル)
    dir = XMVector3Normalize(dir);                       //レイのベクトルを正規化

    //内積を使って法線とレイの角度を求める
    XMVECTOR Vdot = XMVector3Dot(normal, -dir);
    XMFLOAT3 Fdot;
    XMStoreFloat3(&Fdot, Vdot);
    float angle = acos(Fdot.y);              //acosでラジアン角度を求める
    AnglePass_ = XMConvertToDegrees(angle);  //ラジアン → 度
}

//リスタート
void Scissors::Restart()
{
    move_ = XMFLOAT3(0, 0, 0);
    transform_.position_ = Global::InitPos;
    transform_.rotate_ = Global::InitRot;

    Global::JumpStart = 0;
    Global::JumpEnd = 0;
    Global::GameOver = false;
    Global::IsGameOver = false;
    Global::ItemReDraw = true;
    CurrentHP = Global::MAXHP;
    pBlade_L->SetRotateZ(0);
    pBlade_R->SetRotateZ(90);
    pBlade_L->isPrick = false;
    pBlade_R->isPrick = false;
    FallFlg = true;
}

//弾かれた時の動き
void Scissors::RepelMove()
{
    //フラグがたったら
    if (Global::RepelFlg)
    {
        if (!IsRepel)
        { 
            //弾く値を入れる
            powerX = pStage_->Repel().x;
            powerY = pStage_->Repel().y;

            IsRepel = true;
        }
        else
        {
            //どちらも離れていることにする(落下させるため)
            pBlade_L->isPrick = false;
            pBlade_R->isPrick = false;

            if (jumpDirection_.x == 1 || jumpDirection_.x == -1)
            {
                transform_.position_.x += powerX * jumpDirection_.x;       //弾く
                transform_.position_.y -= powerY;             //powerY分下へ
            }
            else
            {
                transform_.position_.x += powerX * Key;       //Keyの方向へ弾く
                transform_.position_.y += powerY;             //powerY分上へ
            }

        }
    }
    else
    {
        IsRepel = false;
    }
}

//沈む動き
void Scissors::SinkMove()
{
    SetCountDown(CountDown);

    //フラグが立ったら
    if (Global::SinkFlg)
    {
        Timer_--;
        CountDown = Timer_ / 60;

        if (!IsSink)
        {
            //沈む値を入れる
            MoveY = pStage_->Sink().y;
            IsSink = true;
        }
        else
        {
            //MoveYの値分沈んでいく
            transform_.position_.y += MoveY;
            JumpPower = SinkJumpPower;
        }

    }
    else
    {
        //最初に戻す
        JumpPower = NormalJumpPower;
        IsSink = false;
        Timer_ = SinkTimer;
    }
}

//足音を流す
void Scissors::Landing()
{
    switch(Global::SelectStage)
    {
    case STAGE_NUMBER_1:
        //草の地面
        if (jumpDirection_.x == 0 && nowPivotPoint_.y <= 7)
        {
            Audio::Play(Stage1_Sound::St1_Glass);
        }
        //壁の時
        else if(jumpDirection_.x == 1 || jumpDirection_.x == -1)
        {
            break;
        }
        //それ以外
        else
        {
            Audio::Play(Stage1_Sound::St1_Wood);
        }
        break;

    case STAGE_NUMBER_2:
        //砂利の地面
        if (nowPivotPoint_.y >= 1.3f && nowPivotPoint_.x >= 23 && nowPivotPoint_.x <= 94.5f
            || nowPivotPoint_.x > 94.5f)
        {
            Audio::Play(Stage2_Sound::St2_Gravel);
        }
        //それ以外
        else
        {
            Audio::Play(Stage2_Sound::St2_Stone);
        }
        break;
    case STAGE_NUMBER_3:
        //弾く地面
        if (Global::RepelFlg)
        {
            Audio::Play(Stage3_Sound::St3_Iron);
        }
        //沈む地面
        else if (Global::SinkFlg)
        {
            Audio::Play(Stage3_Sound::St3_Sand);
        }
        //普通の地面(前半)
        else if (nowPivotPoint_.x <= 74)
        {
            Audio::Play(Stage3_Sound::St3_Volcano_Sand);
            Audio::Stop(Stage3_Sound::St3_Sand);
        }
        //普通の地面(後半)
        else
        {
            Audio::Play(Stage3_Sound::St3_Volcano);
            Audio::Stop(Stage3_Sound::St3_Sand);
        }

        break;
    }
}
