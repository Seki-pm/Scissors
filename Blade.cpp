#include "Blade.h"
#include "Engine/Model.h"
#include "Stage.h"
#include "Scissors.h"

//コンストラクタ
Blade::Blade(GameObject* parent)
    :GameObject(parent, "Blade"),
    isPrick(false),BladeModel_(-1)
{
}

//デストラクタ
Blade::~Blade()
{
}

//初期化
void Blade::Initialize()
{
    //ステージを探しておく（当たり判定に必要）
    pStage = (Stage*)FindObject("Stage");
}

// 引数をもとにモデルを読み込む
void Blade::Load(const int lr)
{
    // 引数が0なら
    if (lr == 0)
    {
        //左を読み込む
        BladeModel_ = Model::Load("Model/Scissors/LBlade.fbx");
        assert(BladeModel_ >= 0);

        //コライダーを手動でつける
        //collider.AddPoint(-0.4f, 0.7f);
        //collider.AddPoint(0.2f, 0.8f);
        //collider.AddPoint(0.0f, -0.8f);

        collider.AddPoint(-0.37f, 0.74f);
        collider.AddPoint(-0.05f, 0.75f);
        collider.AddPoint(-0.0f, -0.8f);
    }
    else  
    {
        // 右を読み込む
        BladeModel_ = Model::Load("Model/Scissors/RBlade.fbx");
        assert(BladeModel_ >= 0);

        //コライダーを手動でつける
        //collider.AddPoint(-0.2f, 0.8f);
        //collider.AddPoint(0.4f, 0.7f);
        //collider.AddPoint(-0.0f, -0.8f);
         
        collider.AddPoint(0.5f, 0.75f);
        collider.AddPoint(0.37f, 0.74f);
        collider.AddPoint(-0.0f, -0.8f);
    }
}

//更新
void Blade::Update()
{

    //刺さっていないなら
    if (!isPrick)
    {
        //刃先が地面に刺さってるかチェック（結果はisPrickフラグに入れる）
        isPrick = pStage->IsHit(GetTipPoint());

        //刺さってる場合、ハサミと地面の交点を求め、刃先がそこに来るよう移動させる（めり込んでる分もどす）
        if (isPrick && !Global::SinkFlg)
        {
            XMFLOAT3 hitPoint;  //交点を入れる変数
            XMFLOAT3 normal;    //法線を入れる変数
            XMFLOAT3 center = GetParent()->GetPosition();  //ハサミの位置が中心位置
            pStage->GetNormal(center, GetTipPoint(), &normal, &hitPoint);
            GetParent()->SetPosition(center.x + hitPoint.x - GetTipPoint().x, center.y + hitPoint.y - GetTipPoint().y, 0);

            //ハサミ（親）にジャンプ方向として地面の法線を渡す
            ((Scissors*)GetParent())->SetJumpDirection(normal);
        }
    }

    //先端以外が地面に当たってる
    if (pStage->IsHit(collider, GetWorldMatrix()) && !Global::SinkFlg)
    {
        // 反射させる
        ((Scissors*)GetParent())->Reflection();
    }
}

//描画
void Blade::Draw()
{
    Model::SetTransform(BladeModel_, transform_);
    Model::Draw(BladeModel_);
}

//開放
void Blade::Release()
{
    BladeModel_ = -1;
}


//開閉
void Blade::Open(int angle)
{
    //刺さってなければ
    if (!isPrick)
    {
        // Z軸で中心回転
        transform_.rotate_.z += angle;
    }
}


//先端位置を取得
XMFLOAT3 Blade::GetTipPoint()
{
    return Model::GetBonePosition(BladeModel_, "Point");
}
