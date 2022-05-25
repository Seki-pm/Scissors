#include "Stage.h"

//コンストラクタ
Stage::Stage(GameObject* parent)
    :GameObject(parent, "Stage"),StageModel_(-1), BackImage_(-1)
{
}

//デストラクタ
Stage::~Stage()
{
}

//初期化
void Stage::Initialize()
{
    //左右反転
    transform_.rotate_.y = 180;

    //表示するステージ
    switch (Global::Select)
    {
    case 0: Stage1(); break;
    case 1: Stage2(); break;
    case 2: Stage3(); break;
    }

}

//更新
void Stage::Update()
{
}

//読み込み
void Stage::Load(const int st)
{
    switch (st)
    {
    case 0: StageModel_ = Model::Load("SuccessModel/stage1.fbx");
            assert(StageModel_ >= 0);
            BackImage_ = Image::Load("Image/Stage1_Back.png");
            assert(BackImage_ >= 0);
            Global::ItemModelPos = XMFLOAT3(47, 9, 0);
            //看板
            Instantiate<Sign>(this);
            break;

    case 1: StageModel_ = Model::Load("SuccessModel/stage2.fbx");
            BackImage_ = Image::Load("Image/Stage2_Back.png");
            assert(BackImage_ >= 0);
            Global::ItemModelPos = XMFLOAT3(-1.5f, 17, 0);
            break;
    }

}

//描画
void Stage::Draw()
{
    Model::SetTransform(StageModel_, transform_);
    Model::Draw(StageModel_);
}

//開放
void Stage::Release()
{
    StageModel_ = -1;
}

// 引数の点の位置がステージに当たってるかチェック
bool Stage::IsHit(XMFLOAT3 position)
{
    //全てのコライダーとチェックする
    for (int i = 0; i < colliders_.size(); i++)
    {
        //多角形と点の当たり判定がtrueなら
        if (colliders_[i].Hit(position))
        {
            //はじく判定
            RepelCheck(i);

            //沈む判定
            SinkCheck(i);

            //ステージに当たってる
            return true;
        }
    }

    //当たってない
    return false;
}

bool Stage::IsHit(PolygonCollider target, XMMATRIX world)
{
    //全てのコライダーとチェックする
    for (int i = 0; i < colliders_.size(); i++)
    {
        if (colliders_[i].Hit(&target, world))
        {
            //当たってる
            return true;
        }
    }

    //当たってない
    return false;
}

void Stage::GetNormal(XMFLOAT3 p1, XMFLOAT3 p2, XMFLOAT3* normal, XMFLOAT3* hitPoint)
{
    //全てのコライダーとチェックする
    for (int i = 0; i < colliders_.size(); i++)
    {
        if (colliders_[i].GetNormal(p1, p2, normal, hitPoint))
        {
            break;
        }
    }
}

//Stage1の設定
void Stage::Stage1()
{
    float startX = 2;
    float startY = 0;
    float goalX  = 55;
    float goalY  = 4;

    //StageModel_ = Model::Load("SuccessModel/stage1.fbx");


    pc1.AddPoint(-5, 7);
    pc1.AddPoint(-4, 7);
    pc1.AddPoint(-4, -1);
    pc1.AddPoint(-5, -1);
    colliders_.push_back(pc1);

    pc2.AddPoint(-4, 0);
    pc2.AddPoint(15, 0);
    pc2.AddPoint(15, -1);
    pc2.AddPoint(-4, -1);
    colliders_.push_back(pc2);

    pc3.AddPoint(14.7f, 0);
    pc3.AddPoint(19.37f, 1.68f);
    pc3.AddPoint(19.71f, 0.74f);
    pc3.AddPoint(15.02, -0.97f);
    colliders_.push_back(pc3);

    pc4.AddPoint(19.37f, 1.68f);
    pc4.AddPoint(24.07f, -0.04f);
    pc4.AddPoint(23.73f, -0.98f);
    pc4.AddPoint(19.03f, 0.73f);
    colliders_.push_back(pc4);

    pc5.AddPoint(23.75f, 0);
    pc5.AddPoint(38, 0);
    pc5.AddPoint(38, -1);
    pc5.AddPoint(23.75f, -1);
    colliders_.push_back(pc5);

    pc6.AddPoint(38, 8);
    pc6.AddPoint(39, 8);
    pc6.AddPoint(39, -1);
    pc6.AddPoint(38, -1);
    colliders_.push_back(pc6);

    pc7.AddPoint(33, 12.5f);
    pc7.AddPoint(34, 12.5f);
    pc7.AddPoint(34, 3.5f);
    pc7.AddPoint(33, 3.5f);
    colliders_.push_back(pc7);

    pc8.AddPoint(39, 8);
    pc8.AddPoint(47, 8);
    pc8.AddPoint(47, 7);
    pc8.AddPoint(39, 7);
    colliders_.push_back(pc8);


    pc9.AddPoint(40, 8);
    pc9.AddPoint(47.5f, 8);
    pc9.AddPoint(47.5f, 7);
    pc9.AddPoint(47, 7);
    colliders_.push_back(pc9);

    pc10.AddPoint(52, 4);
    pc10.AddPoint(53, 4);
    pc10.AddPoint(53, 0);
    pc10.AddPoint(52, 0);
    colliders_.push_back(pc10);


    //ゴール前
    pc11.AddPoint(49, 5.3f);
    pc11.AddPoint(60, 5.3f);
    pc11.AddPoint(60, 4);
    pc11.AddPoint(49, 4);
    colliders_.push_back(pc11);

    pc12.AddPoint(60, 14);
    pc12.AddPoint(61, 14);
    pc12.AddPoint(61, 4);
    pc12.AddPoint(60, 4);
    colliders_.push_back(pc12);


    //スタートとゴールの設定
    gl.SetCameraStartX(startX);
    gl.SetCameraStartY(startY);
    gl.SetCameraGoalX(goalX);
    gl.SetCameraGoalY(goalY);
}

//Stage2の設定
void Stage::Stage2()
{
    float startX = 2;
    float startY = 0;
    float goalX = 125;
    float goalY = 0.36f;



    //左の壁
    pc1.AddPoint(-10  ,   28);
    pc1.AddPoint(-3.7f  ,   28);
    pc1.AddPoint(-3.7f  , -2);
    pc1.AddPoint(-10  , -2);
    colliders_.push_back(pc1);

    //最初の床
    pc2.AddPoint(-5 ,  0);
    pc2.AddPoint(42.5f, 0);
    pc2.AddPoint(42.5f,  -2);
    pc2.AddPoint(-5,  -2);
    colliders_.push_back(pc2);

    //少し高い床
    pc3.AddPoint(4.4f , 1.5f);
    pc3.AddPoint(16, 1.5f);
    pc3.AddPoint(16, 0);
    pc3.AddPoint(4.4f , 0);
    colliders_.push_back(pc3);

    //壁(下)
    pc4.AddPoint(15.5f,4.8f);
    pc4.AddPoint(18.8f,4.8f);
    pc4.AddPoint(18.8f,0);
    pc4.AddPoint(15.5f,0);
    colliders_.push_back(pc4);

    //天井(地面)
    pc5.AddPoint(4.3f, 13.8f);
    pc5.AddPoint(12,13.8f);
    pc5.AddPoint(12,4.4f);
    pc5.AddPoint(4.3f, 4.4f);
    colliders_.push_back(pc5);

    //壁（上）
    pc6.AddPoint(15.5f, 15.7f);
    pc6.AddPoint(18.8f, 15.7f);
    pc6.AddPoint(18.8f, 8.3f);
    pc6.AddPoint(15.5f, 8.3f);
    colliders_.push_back(pc6);

    //空中飛び石1
    pc7.AddPoint(1.93f, 15.2f);
    pc7.AddPoint(2.38f, 15.2f);
    pc7.AddPoint(2.38f, 14.75f);
    pc7.AddPoint(1.93f, 14.75f);
    colliders_.push_back(pc7);

    //空中飛び石2
    pc8.AddPoint(0.3f,16.1f);
    pc8.AddPoint(0.74f, 16.1f);
    pc8.AddPoint(0.74f,15.65f);
    pc8.AddPoint(0.3f, 15.65f);
    colliders_.push_back(pc8);

    //凹凸1
    pc9.AddPoint(24.0f, 2.0f);
    pc9.AddPoint(27.45f, 2.0f);
    pc9.AddPoint(27.45f, -1.5f);
    pc9.AddPoint(24.0f, -1.5f);
    colliders_.push_back(pc9);

    //凹凸2
    pc10.AddPoint(30.0f, 3.0f);
    pc10.AddPoint(33.45f,3.0f);
    pc10.AddPoint(33.45f, -1.5f);
    pc10.AddPoint(30.0f, -1.5f);
    colliders_.push_back(pc10);

    //床2
    pc11.AddPoint(45.5f, 0);
    pc11.AddPoint(66.5f, 0);
    pc11.AddPoint(66.5f, -2);
    pc11.AddPoint(45.5f,  -2);
    colliders_.push_back(pc11);

    //浮き床1
    pc12.AddPoint(51.52f, 1.65f);
    pc12.AddPoint(54.22f, 1.65f);
    pc12.AddPoint(54.22f, 1.05f);
    pc12.AddPoint(51.52f, 1.05f);
    colliders_.push_back(pc12);

    //浮き床2
    pc13.AddPoint(56.3f, 3);
    pc13.AddPoint(59.23f, 3);
    pc13.AddPoint(59.23f, 2.4f);
    pc13.AddPoint(56.3f, 2.4f);
    colliders_.push_back(pc13);

    //浮き床3
    pc14.AddPoint(61.32f, 3.75f);
    pc14.AddPoint(63.96f, 3.75f);
    pc14.AddPoint(63.96f, 3.31f);
    pc14.AddPoint(61.32f, 3.31f);
    colliders_.push_back(pc14);
    
    //浮き床4
    pc15.AddPoint(65.41f, 4.61f);
    pc15.AddPoint(68.05f, 4.61f);
    pc15.AddPoint(68.05f, 4.18f);
    pc15.AddPoint(65.41f, 4.61f);
    colliders_.push_back(pc15);

    //浮き床5(長)
    pc16.AddPoint(70, 5.65f);
    pc16.AddPoint(84.58f, 5.65f);
    pc16.AddPoint(84.58f, 5.11f);
    pc16.AddPoint(70, 5.11f);
    colliders_.push_back(pc16);

    //浮き床6
    pc17.AddPoint(86.64f, 4.56f);
    pc17.AddPoint(89.34f, 4.56f);
    pc17.AddPoint(89.34f, 3.97f);
    pc17.AddPoint(86.64f, 3.97f);
    colliders_.push_back(pc17);

    //跳び床1
    pc18.AddPoint(68.13f,  0.29f);
    pc18.AddPoint(71.43f,  0.29f);
    pc18.AddPoint(71.43f, -1.96f);
    pc18.AddPoint(68.13f, -1.96f);
    colliders_.push_back(pc18);

    //跳び床2
    pc19.AddPoint(73.83f,  0.29f);
    pc19.AddPoint(77.13f,  0.29f);
    pc19.AddPoint(77.13f, -1.96f);
    pc19.AddPoint(73.83f, -1.96f);
    colliders_.push_back(pc19);

    //床3
    pc20.AddPoint(80.78f,  0.14f);
    pc20.AddPoint(91.88f,  0.14f);
    pc20.AddPoint(91.88f, -2.11f);
    pc20.AddPoint(80.78f, -2.11f);
    colliders_.push_back(pc20);



    //床4
    pc21.AddPoint(94.6f,    0.36f);
    pc21.AddPoint(109.46f,  0.36f);
    pc21.AddPoint(109.46f, -2.31f);
    pc21.AddPoint(94.6f,   -2.31f);
    colliders_.push_back(pc21);

    //登り床1
    pc22.AddPoint(103.35f,  4);
    pc22.AddPoint(106.34f,  4);
    pc22.AddPoint(106.34f, 3.5f);
    pc22.AddPoint(103.35f, 3.5f);
    colliders_.push_back(pc22);

    //登り床2
    pc23.AddPoint(105.55f, 3);
    pc23.AddPoint(107.96f, 3);
    pc23.AddPoint(107.96f, 2.42f);
    pc23.AddPoint(105.55f, 2.42f);
    colliders_.push_back(pc23);

    //登り床3
    pc24.AddPoint(103.46f, 6.09f);
    pc24.AddPoint(105.81f, 5.67f);
    pc24.AddPoint(105.7f,  5.07f);
    pc24.AddPoint(103.34f, 5.51f);
    colliders_.push_back(pc24);

    //登り床4
    pc25.AddPoint(105.78f, 10.39f);
    pc25.AddPoint(106.41f, 10.39f);
    pc25.AddPoint(106.42f, 8.f);
    pc25.AddPoint(105.78f, 8.f);
    colliders_.push_back(pc25);

    //壁1
    pc26.AddPoint(109.38f, 8.1f);
    pc26.AddPoint(111.48f, 8.1f);
    pc26.AddPoint(111.48f, -2.3f);
    pc26.AddPoint(109.38f, -2.3f);
    colliders_.push_back(pc26);

    //壁2
    pc27.AddPoint(115.48f, 7);
    pc27.AddPoint(119.23f, 7);
    pc27.AddPoint(119.23f, -2.33f);
    pc27.AddPoint(115.48f, -2.33f);
    colliders_.push_back(pc27);

    //壁内床
    pc28.AddPoint(111, -1.43f);
    pc28.AddPoint(116, -1.43f);
    pc28.AddPoint(116, -2.36f);
    pc28.AddPoint(111, -2.36f);
    colliders_.push_back(pc28);

    //床5
    pc29.AddPoint(119, 0.36f);
    pc29.AddPoint(133, 0.36f);
    pc29.AddPoint(133, -2.32f);
    pc29.AddPoint(119, -2.32f);
    colliders_.push_back(pc29);

    //ゴール壁
    pc30.AddPoint(132.25f, 17.5f);
    pc30.AddPoint(135.8f, 17.5f);
    pc30.AddPoint(135.8f, -2.32f);
    pc30.AddPoint(132.25f, -2.32f);
    colliders_.push_back(pc30);


    //スタートとゴールの設定
    gl.SetCameraStartX(startX);
    gl.SetCameraStartY(startY);
    gl.SetCameraGoalX(goalX);
    gl.SetCameraGoalY(goalY);
}

//Stage3の設定
void Stage::Stage3()
{
    float startX = 2;
    float startY = 0;
    float goalX = 3;
    float goalY = 0.f;

    StageModel_ = Model::Load("SuccessModel/stage3.fbx");
    assert(StageModel_ >= 0);

    //最初の左の壁
    pc1.AddPoint(-9,22);
    pc1.AddPoint(-4,22);
    pc1.AddPoint(-4, 0);
    pc1.AddPoint(-9, 0);
    colliders_.push_back(pc1);

    //最初の地面
    pc2.AddPoint(-9,  0);
    pc2.AddPoint(20,  0);
    pc2.AddPoint(20, -7);
    pc2.AddPoint(-9, -7);
    colliders_.push_back(pc2);

    //登り壁(左)
    pc3.AddPoint(17,19);
    pc3.AddPoint(19,19);
    pc3.AddPoint(19, 4);
    pc3.AddPoint(17, 4);
    colliders_.push_back(pc3);

    //登り壁(右)
    pc4.AddPoint(23, 19);
    pc4.AddPoint(25, 19);
    pc4.AddPoint(25,  5);
    pc4.AddPoint(23,  5);
    colliders_.push_back(pc4);
 
    pc5.AddPoint(25,19);
    pc5.AddPoint(28,19);
    pc5.AddPoint(28,15);
    pc5.AddPoint(25,15);
    colliders_.push_back(pc5);
    
    pc6.AddPoint(28,19);
    pc6.AddPoint(30,19);
    pc6.AddPoint(30,15);
    pc6.AddPoint(28,15);
    pc6.AddRepel(6);
    colliders_.push_back(pc6);
    /*
    pc7.AddPoint(, );
    pc7.AddPoint(, );
    pc7.AddPoint(, );
    pc7.AddPoint(, );
    colliders_.push_back(pc7);

    pc8.AddPoint(, );
    pc8.AddPoint(, );
    pc8.AddPoint(, );
    pc8.AddPoint(, );
    colliders_.push_back(pc8);

    pc9.AddPoint(, );
    pc9.AddPoint(, );
    pc9.AddPoint(, );
    pc9.AddPoint(, );
    colliders_.push_back(pc9);

    pc10.AddPoint(, );
    pc10.AddPoint(, );
    pc10.AddPoint(, );
    pc10.AddPoint(, );
    colliders_.push_back(pc10);

    pc11.AddPoint(, );
    pc11.AddPoint(, );
    pc11.AddPoint(, );
    pc11.AddPoint(, );
    colliders_.push_back(pc11);

    pc12.AddPoint(, );
    pc12.AddPoint(, );
    pc12.AddPoint(, );
    pc12.AddPoint(, );
    colliders_.push_back(pc12);

    pc13.AddPoint(, );
    pc13.AddPoint(, );
    pc13.AddPoint(, );
    pc13.AddPoint(, );
    colliders_.push_back(pc13);

    pc14.AddPoint(, );
    pc14.AddPoint(, );
    pc14.AddPoint(, );
    pc14.AddPoint(, );
    colliders_.push_back(pc14);

    pc15.AddPoint(, );
    pc15.AddPoint(, );
    pc15.AddPoint(, );
    pc15.AddPoint(, );
    colliders_.push_back(pc15);

    pc16.AddPoint(, );
    pc16.AddPoint(, );
    pc16.AddPoint(, );
    pc16.AddPoint(, );
    colliders_.push_back(pc16);

    pc17.AddPoint(, );
    pc17.AddPoint(, );
    pc17.AddPoint(, );
    pc17.AddPoint(, );
    colliders_.push_back(pc17);

    pc18.AddPoint(, );
    pc18.AddPoint(, );
    pc18.AddPoint(, );
    pc18.AddPoint(, );
    colliders_.push_back(pc18);

    pc19.AddPoint(, );
    pc19.AddPoint(, );
    pc19.AddPoint(, );
    pc19.AddPoint(, );
    colliders_.push_back(pc19);

    pc20.AddPoint(, );
    pc20.AddPoint(, );
    pc20.AddPoint(, );
    pc20.AddPoint(, );
    colliders_.push_back(pc20);

    pc.AddPoint(, );
    pc.AddPoint(, );
    pc.AddPoint(, );
    pc.AddPoint(, );
    colliders_.push_back(pc);
*/







    //スタートとゴールの設定
    gl.SetCameraStartX(startX);
    gl.SetCameraStartY(startY);
    gl.SetCameraGoalX(goalX);
    gl.SetCameraGoalY(goalY);
}


//はじく
XMFLOAT3 Stage::Repel()
{
    XMFLOAT3 repel = { 0.1f,0.3f,0 };

    return repel;
}

//はじく床をチェック
void Stage::RepelCheck(int i)
{
    PolygonCollider pc;
    pc.SetRepel(i);

    if (i == pc.GetRepel())
    {
        //はじくフラグtrue
        Global::RepelFlg = true;
        Global::IsJump = false;
        Global::HP -= 2;

    }
    else
    {
        Global::RepelFlg = false;
        Global::IsJump = true;
    }
}

//沈む
XMFLOAT3 Stage::Sink()
{
    XMFLOAT3 Sink = { 0,-0.01f,0 };
    return Sink;
}

//沈む床をチェック
void Stage::SinkCheck(int i)
{
    PolygonCollider pc;
    pc.SetSink(i);

    if (i == pc.GetSink())
    {
        //沈むフラグtrue
        Global::SinkFlg = true;
        Global::JumpStart = 0;
        Global::JumpEnd = 0;
        Global::HP++;
    }
    else
    {
        Global::SinkFlg = false;
    }
}


