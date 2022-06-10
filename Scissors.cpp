#include "Scissors.h"

#define NormalJumpPower 0.1f;
#define SinkJumpPower 0.001f;
#define SinkTimer 360;

//コンストラクタ
Scissors::Scissors(GameObject* parent)
    :GameObject(parent, "Scissors"), move_(XMFLOAT3(0,0,0)),
    jumpDirection_(XMFLOAT3(0,0,0)),nowPivotPoint_(XMFLOAT3(0,0,0)),
    Land_Glass(-1), Land_Wood(-1), Land_Gravel(-1), Land_Stone(-1),
    AnglePass_(0.0f), GLAVITY(0.03f), pBlade_L(nullptr), pBlade_R(nullptr),
    CalcFlg(false), FallFlg(true),SoundFlg(false),IsRepel(false),IsSink(false),
    JumpPower(0.1f),Key(0), NumberImage_(-1), Timer_(360), CountDown(0)
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

    //テスト用
    //pBlade_R->isPrick = true;   //右が地面に刺さってるとして
    pBlade_R->SetRotateZ(45);

    //初期位置
    transform_.position_ = Global::InitPos;

    //サウンドのロード
    InitSound();

    //画像の初期化
    InitImage();

    SphereCollider* collision =
        new SphereCollider(XMFLOAT3(0, 0, 0), 0.6f);
    AddCollider(collision);

}

//更新
void Scissors::Update()
{
    GameOver* pGameOver = (GameOver*)FindObject("GameOver");

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

    //GameOverの時リトライを選択しているとリスタート
    if (Global::GameOver && Input::IsKeyDown(DIK_SPACE))
    {
        if (pGameOver->GetSelect() == 0)
        {
            Restart();
        }
    }

    //落下したら
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
    RepelMove();
    SinkMove();
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
    if (XMConvertToDegrees(ang) > 170 || XMConvertToDegrees(ang) < 2)   
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
        if (AnglePass_ < 170)
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
    if (!pBlade_L->IsPrick() && !pBlade_R->IsPrick() && Global::IsJump)     //どっちも刺さってなければ
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
            //音を出す
            Landing();
            SoundFlg = false;
        }

        //壁かどうかでSPACEの入力を変える
        if (jumpDirection_.x == 1 || jumpDirection_.x == -1)
        {
            //壁なら長押しで反応なし
            if (Input::IsKeyDown(DIK_SPACE) && Global::IsJump)
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
        else if (Input::IsKey(DIK_SPACE) && Global::IsJump)
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
    if (Global::SinkFlg)
    {
        auto DengerTrans = Transform();
        DengerTrans.position_ = XMFLOAT3(0,0.8f,0);
        Image::SetTransform(DengerImage_, DengerTrans);
        Image::Draw(DengerImage_);

        pNumber_->Draw(CountDown, 0.06f, 0.8f, NumberImage_);
    }
}

//開放
void Scissors::Release()
{
    Land_Glass = -1;
    Land_Wood = -1;
    Land_Gravel = -1;
    Land_Stone = -1;
}

//反射
void Scissors::Reflection()
{
    int cnt = 0;
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

        //判定を10回行ったら強制的にはじく
        if (cnt >= 10)
        {
            if (move_.x <= 0)
            {
                move_.x = 0.1f;
            }
            if (move_.y <= 0)
            {
                move_.y = 0.1f;
            }

            move_.x *= -0.3f;
            move_.y *= -0.3f;

        }

        //ステージ外に出た場合スタート位置に戻る
        //if (transform_.position_.x < 0 ||
        //    transform_.position_.y < 0 ||
        //    cnt >= 100)
        //{
        //    Global gl;
        //    transform_.position_.x = gl.GetCameraStartX();
        //    transform_.position_.y = gl.GetCameraStartY();
        //}

        Global::HP--;
    }
}

//現在位置を送る
void Scissors::SetPosition()
{
    Global global;
    float transX = transform_.position_.x;
    float transY = transform_.position_.y;
    float transZ = transform_.position_.z;

    global.SetTransPos_X(transX);
    global.SetTransPos_Y(transY);
    global.SetTransPos_Z(transZ);
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
    XMVECTOR normal = XMLoadFloat3(&jumpDirection_);     //XMFLOAT3 → XMVECTOR
    XMMATRIX Rotmat = XMMatrixRotationZ(45.5f);          //法線回転用の回転行列
    normal = XMVector3TransformCoord(normal, Rotmat);    //normalとRotmatをかける
    normal = XMVector3Normalize(normal);                 //normalを正規化
    XMVECTOR dir = XMLoadFloat3(&data.dir);              //レイのベクトルを正規化

    //内積を使って法線とレイの角度を求める
    XMVECTOR Vdot = XMVector3Dot(normal, -dir);
    XMFLOAT3 Fdot;
    XMStoreFloat3(&Fdot, Vdot);
    float angle = acos(Fdot.y);
    AnglePass_ = XMConvertToDegrees(angle);
}

//リスタート
void Scissors::Restart()
{
    move_ = XMFLOAT3(0, 0, 0);
    transform_.position_ = Global::InitPos;
    transform_.rotate_ = Global::InitRot;
    Global::HP = Global::MAXHP;
    Global::JumpStart = 0;
    Global::JumpEnd = 0;
    pBlade_L->SetRotateZ(0);
    pBlade_R->SetRotateZ(90);
    Global::GameOver = false;
    Global::IsGameOver = false;
    FallFlg = true;
    Global::ItemReDraw = true;
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

//音楽の初期化
void Scissors::InitSound()
{

    //--------- STAGE1 ----------------------------------
     
       //----------- 草 --------------------
    Land_Glass = Audio::Load("Sound/FootStep_Glass.wav");
    assert(Land_Glass >= 0);

      //------------ 木 --------------------
    Land_Wood = Audio::Load("Sound/FootStep_Wood.wav");
    assert(Land_Wood >= 0);

    //---------------------------------------------------


    //-------------- STAGE2 ---------------------------

      //-------------- 砂利 ----------------
    Land_Gravel = Audio::Load("Sound/FootStep_Gravel.wav");
    assert(Land_Gravel >= 0);

      //-------------- 石 ---------------------
    Land_Stone = Audio::Load("Sound/FootStep_Stone.wav");
    assert(Land_Stone >= 0);

    //-------------------------------------------------

    //-------------- STAGE3 ---------------------------

      //------------- 弾く -----------------
    Land_Iron = Audio::Load("Sound/FootStep_Iron.wav");
    assert(Land_Iron >= 0);

      //------------- 沈む -----------------
    Land_Sand = Audio::Load("Sound/FootStep_Sand.wav");
    assert(Land_Sand >= 0);

      //------------- 火山砂地帯(前半) ---------------------
    Land_Volcano_Sand = Audio::Load("Sound/FootStep_Volcano_Sand.wav");
    assert(Land_Volcano_Sand >= 0);

      //------------- 火山地帯（後半）-------------------
    Land_Volcano = Audio::Load("Sound/FootStep_Volcano.wav");
    assert(Land_Volcano >= 0);

    //-------------- STAGE3 ---------------------------
}

//音を流す
void Scissors::Landing()
{
    switch(Global::SelectStage)
    {
    case STAGE_NUMBER_1:
        //草の地面
        if (jumpDirection_.x == 0 && transform_.position_.y <= 7)
        {
            Audio::Play(Land_Glass);
        }
        //壁の時
        else if(jumpDirection_.x == 1 || jumpDirection_.x == -1)
        {
            break;
        }
        //それ以外
        else
        {
            Audio::Play(Land_Wood);
        }
        break;

    case STAGE_NUMBER_2:
        //砂利の地面
        if (transform_.position_.y >= 1.3f && transform_.position_.x >= 23 && transform_.position_.x <= 94.5f
            || transform_.position_.x > 94.5f)
        {
            Audio::Play(Land_Gravel);
        }
        //それ以外
        else
        {
            Audio::Play(Land_Stone);
        }
        break;
    case STAGE_NUMBER_3:
        //弾く地面
        if (Global::RepelFlg)
        {
            Audio::Play(Land_Iron);
        }
        //沈む地面
        else if (Global::SinkFlg)
        {
            Audio::Play(Land_Sand);
        }
        //普通の地面(前半)
        else if (transform_.position_.x <= 73)
        {
            Audio::Play(Land_Volcano_Sand);
            Audio::Stop(Land_Sand);
        }
        //普通の地面(後半)
        else
        {
            Audio::Play(Land_Volcano);
            Audio::Stop(Land_Sand);
        }

        break;
    }
}

//画像の初期化
void Scissors::InitImage()
{
    //数字   
    NumberImage_ = Image::Load("Image/Number.png");
    assert(NumberImage_ >= 0);
    
    //数字の背景
    DengerImage_ = Image::Load("Image/Denger.png");
    assert(DengerImage_ >= 0);
}

