#include "Stage.h"
#include "Scissors.h"

//コンストラクタ
Stage::Stage(GameObject* parent)
    :GameObject(parent, "Stage"),
    StageModel_(-1), BackImage_(-1), NumberImage_(-1), DengerImage_(-1),Sound_(-1),
    startX(0),startY(0),goalX(0),goalY(0),StGo(XMFLOAT4(0,0,0,0)),
    RepelFlg(false), SinkFlg(false), pScissors_(nullptr), pNumber_(nullptr)
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
    switch (Global::SelectStage)
    {
    case STAGE_NUMBER_1: Stage1(); break;
    case STAGE_NUMBER_2: Stage2(); break;
    case STAGE_NUMBER_3: Stage3(); break;
    }

}

//更新
void Stage::Update()
{
}

//読み込み
void Stage::Load(const int stage)
{
    //引数で読み込むStageを変える
    switch (stage)
    {
    case STAGE_NUMBER_1: Stage1Load(); break;
    case STAGE_NUMBER_2: Stage2Load(); break;
    case STAGE_NUMBER_3: Stage3Load(); break;
    }

}

//描画
void Stage::Draw()
{
    pScissors_ = (Scissors*)FindObject("Scissors");

    Image::Draw(BackImage_);
    Model::SetTransform(StageModel_, transform_);
    Model::Draw(StageModel_);

    if (SinkFlg)
    {
        auto DengerTrans = Transform();
        DengerTrans.position_ = DENGER_IMAGE_POS;
        Image::SetTransform(DengerImage_, DengerTrans);
        Image::Draw(DengerImage_);

        pNumber_->Draw(pScissors_->GetCountDown(), NUMBER_POS.x, NUMBER_POS.y, NumberImage_);
    }
}

//開放
void Stage::Release()
{
    BackImage_ = -1;
    StageModel_ = -1;
    DengerImage_ = -1;
    NumberImage_ = -1;
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

//Stage1のコライダ設定
void Stage::Stage1()
{
    //スタートとゴールを設定
    StGo = ST1_START_GOAL_POS;
    startX = StGo.x;
    startY = StGo.y;
    goalX = StGo.z;
    goalY = StGo.w;
    
    //スタートから壁まで
    {
        //スタートの壁
        pc1.AddPoint(-5,     7);
        pc1.AddPoint(-3.5f,  7);
        pc1.AddPoint(-3.5f, -1);
        pc1.AddPoint(-5,    -1);
        colliders_.push_back(pc1);

        //初めの床
        pc2.AddPoint(-4,  0);
        pc2.AddPoint(15,  0);
        pc2.AddPoint(15, -1);
        pc2.AddPoint(-4, -1);
        colliders_.push_back(pc2);

        pc21.AddPoint(3.5f, 1);
        pc21.AddPoint(5.5f, 1);
        pc21.AddPoint(5.5f, 0);
        pc21.AddPoint(3.5f, 0);
        colliders_.push_back(pc21);

        //斜め床(右上がり)
        pc3.AddPoint(14.7f,       0);
        pc3.AddPoint(19.37f,  1.68f);
        pc3.AddPoint(19.71f,  0.74f);
        pc3.AddPoint(15.02f, -0.97f);
        colliders_.push_back(pc3);

        //斜め床(右下がり)
        pc4.AddPoint(19.37f,  1.68f);
        pc4.AddPoint(24.07f, -0.04f);
        pc4.AddPoint(23.73f, -0.98f);
        pc4.AddPoint(19.03f,  0.73f);
        colliders_.push_back(pc4);

        //壁までの床
        pc5.AddPoint(23.75f,  0);
        pc5.AddPoint(38,      0);
        pc5.AddPoint(38,     -1);
        pc5.AddPoint(23.75f, -1);
        colliders_.push_back(pc5);
    }

    //壁からゴール前まで
    {
        //右の壁
        pc6.AddPoint(38.5f,  7);
        pc6.AddPoint(42,     7);
        pc6.AddPoint(42,    -1);
        pc6.AddPoint(38.5f, -1);
        colliders_.push_back(pc6);

        //左の壁
        pc7.AddPoint(33,    12.5f);
        pc7.AddPoint(34.5f, 12.5f);
        pc7.AddPoint(34.5f,  4.5f);
        pc7.AddPoint(33,     4.5f);
        colliders_.push_back(pc7);

        //壁上がった後の床
        pc8.AddPoint(38.5f, 8);
        pc8.AddPoint(48,    8);
        pc8.AddPoint(48,    7);
        pc8.AddPoint(38.5f, 7);
        colliders_.push_back(pc8);

    }

    //ゴール
    {
        //ゴール床
        pc9.AddPoint(49.5f, 5.3f);
        pc9.AddPoint(60,    5.3f);
        pc9.AddPoint(60,    4);
        pc9.AddPoint(49.5f, 4);
        colliders_.push_back(pc9);

        //ゴール壁
        pc10.AddPoint(60.5f, 14);
        pc10.AddPoint(61,    14);
        pc10.AddPoint(61,     4);
        pc10.AddPoint(60.5f,  4);
        colliders_.push_back(pc10);
    }

    //スタートとゴールのカメラ位置の設定
    gl.SetCameraStart(startX , startY);
    gl.SetCameraGoal(goalX, goalY);
}

//Stage1の読み込み
void Stage::Stage1Load()
{
    //ステージモデルと背景を読み込み
    StageModel_ = Model::Load("Model/Stage/Stage1/stage1.fbx");
    assert(StageModel_ >= 0);

    BackImage_ = Image::Load("Image/StageScene/Stage1_Back.png");
    assert(BackImage_ >= 0);


    //サウンドを追加
    for (int i = 0; i < St1_Max; i++)
    {
        Sound_ = -1;

        switch (i)
        {
        case St1_Glass:
            Sound_ = Audio::Load("Sound/InStage/Stage1/FootStep_Glass.wav"); break;
        case St1_Wood:
            Sound_ = Audio::Load("Sound/InStage/Stage1/FootStep_Wood.wav"); break;
        }
        assert(Sound_ >= 0);
    }


    //コインの位置
    Global::ItemModelPos = ST1_ITEMMODEL_POS;
    //看板
    Instantiate<Sign>(this);
}

//Stage2のコライダ設定
void Stage::Stage2()
{
    StGo = ST2_START_GOAL_POS;
    startX = StGo.x;
    startY = StGo.y;
    goalX = StGo.z;
    goalY = StGo.w;

    //スタートから穴まで
    {
        //スタートのの壁
        pc1.AddPoint(-10, 28);
        pc1.AddPoint(-3.7f, 28);
        pc1.AddPoint(-3.7f, -2);
        pc1.AddPoint(-10, -2);
        colliders_.push_back(pc1);

        //最初の床
        pc2.AddPoint(-5, 0);
        pc2.AddPoint(42.5f, 0);
        pc2.AddPoint(42.5f, -2);
        pc2.AddPoint(-5, -2);
        colliders_.push_back(pc2);

        //少し高い床
        pc3.AddPoint(4.4f, 1.5f);
        pc3.AddPoint(16, 1.5f);
        pc3.AddPoint(16, 0);
        pc3.AddPoint(4.4f, 0);
        colliders_.push_back(pc3);

        //壁(下)
        pc4.AddPoint(15.5f, 4.8f);
        pc4.AddPoint(18.8f, 4.8f);
        pc4.AddPoint(18.8f, 0);
        pc4.AddPoint(15.5f, 0);
        colliders_.push_back(pc4);

        //天井(地面)
        pc5.AddPoint(4.3f, 13.8f);
        pc5.AddPoint(12, 13.8f);
        pc5.AddPoint(12, 4.4f);
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
        pc8.AddPoint(0.3f, 16.1f);
        pc8.AddPoint(0.74f, 16.1f);
        pc8.AddPoint(0.74f, 15.65f);
        pc8.AddPoint(0.3f, 15.65f);
        colliders_.push_back(pc8);

        //凹凸1
        pc9.AddPoint(24.0f,   2.0f);
        pc9.AddPoint(27.45f,  2.0f);
        pc9.AddPoint(27.45f, -1.5f);
        pc9.AddPoint(24.0f,  -1.5f);
        colliders_.push_back(pc9);

        //凹凸2
        pc10.AddPoint(30.0f,   3.0f);
        pc10.AddPoint(33.45f,  3.0f);
        pc10.AddPoint(33.45f, -1.5f);
        pc10.AddPoint(30.0f,  -1.5f);
        colliders_.push_back(pc10);
    }

    //～浮き床ギミックまで
    {
        //床2
        pc11.AddPoint(45.5f,  0);
        pc11.AddPoint(66.5f,  0);
        pc11.AddPoint(66.5f, -2);
        pc11.AddPoint(45.5f, -2);
        colliders_.push_back(pc11);

        //浮き床1
        pc12.AddPoint(51.52f, 1.65f);
        pc12.AddPoint(54.22f, 1.65f);
        pc12.AddPoint(54.22f, 1.05f);
        pc12.AddPoint(51.52f, 1.05f);
        colliders_.push_back(pc12);

        //浮き床2
        pc13.AddPoint(56.3f,  3);
        pc13.AddPoint(59.23f, 3);
        pc13.AddPoint(59.23f, 2.4f);
        pc13.AddPoint(56.3f,  2.4f);
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
        pc16.AddPoint(70,     5.65f);
        pc16.AddPoint(84.58f, 5.65f);
        pc16.AddPoint(84.58f, 5.11f);
        pc16.AddPoint(70,     5.11f);
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
    }

    //ゴール前まで
    {
        //床4
        pc21.AddPoint( 94.6f,   0.36f);
        pc21.AddPoint(109.46f,  0.36f);
        pc21.AddPoint(109.46f, -2.31f);
        pc21.AddPoint( 94.6f,  -2.31f);
        colliders_.push_back(pc21);

        //登り床1
        pc22.AddPoint(103, 3.5f);
        pc22.AddPoint(107, 3.5f);
        pc22.AddPoint(107, 3);
        pc22.AddPoint(103, 3);
        colliders_.push_back(pc22);

        //登り床2
        pc23.AddPoint(103, 6.5f);
        pc23.AddPoint(107, 6.5f);
        pc23.AddPoint(107, 6);
        pc23.AddPoint(103, 6);
        colliders_.push_back(pc23);

        //壁1
        pc24.AddPoint(109.38f,  8.1f);
        pc24.AddPoint(111.48f,  8.1f);
        pc24.AddPoint(111.48f, -2.3f);
        pc24.AddPoint(109.38f, -2.3f);
        colliders_.push_back(pc24);

        //壁2
        pc25.AddPoint(115.48f,  7);
        pc25.AddPoint(119.23f,  7);
        pc25.AddPoint(119.23f, -2.33f);
        pc25.AddPoint(115.48f, -2.33f);
        colliders_.push_back(pc25);

        //壁内床
        pc26.AddPoint(111, -1.43f);
        pc26.AddPoint(116, -1.43f);
        pc26.AddPoint(116, -2.36f);
        pc26.AddPoint(111, -2.36f);
        colliders_.push_back(pc26);
    }

    //ゴール
    {
        //床5
        pc27.AddPoint(119,  0.36f);
        pc27.AddPoint(133,  0.36f);
        pc27.AddPoint(133, -2.32f);
        pc27.AddPoint(119, -2.32f);
        colliders_.push_back(pc27);

        //ゴール壁
        pc28.AddPoint(132.25f, 17.5f);
        pc28.AddPoint(135.8f,  17.5f);
        pc28.AddPoint(135.8f,  -2.32f);
        pc28.AddPoint(132.25f, -2.32f);
        colliders_.push_back(pc28);
    }

    //スタートとゴールの設定
    gl.SetCameraStart(startX, startY);
    gl.SetCameraGoal(goalX, goalY);
}

//Stage2の読み込み
void Stage::Stage2Load()
{
    //ステージモデルと背景を読み込み
    StageModel_ = Model::Load("Model/Stage/Stage2/stage2.fbx");
    assert(StageModel_ >= 0);
    BackImage_ = Image::Load("Image/StageScene/Stage2_Back.png");
    assert(BackImage_ >= 0);

    //サウンドを追加
    for (int i = 0; i < St2_Max; i++)
    {
        Sound_ = -1;

        switch (i)
        {
        case St1_Glass:
            Sound_ = Audio::Load("Sound/InStage/Stage2/FootStep_Gravel.wav"); break;
        case St1_Wood:
            Sound_ = Audio::Load("Sound/InStage/Stage2/FootStep_Stone.wav"); break;
        }
        assert(Sound_ >= 0);
    }

    //コインの位置
    Global::ItemModelPos = ST2_ITEMMODEL_POS;
}

//Stage3のコライダ設定
void Stage::Stage3()
{
    StGo = ST3_START_GOAL_POS;
    startX = StGo.x;
    startY = StGo.y;
    goalX = StGo.z;
    goalY = StGo.w;

    //スタートから壁まで
    {
        //スタートの壁
        pc1.AddPoint(-9, 22);
        pc1.AddPoint(-4, 22);
        pc1.AddPoint(-4,  0);
        pc1.AddPoint(-9,  0);
        colliders_.push_back(pc1);

        //最初の地面
        pc2.AddPoint(-9,  0);
        pc2.AddPoint(20,  0);
        pc2.AddPoint(20, -7);
        pc2.AddPoint(-9, -7);
        colliders_.push_back(pc2);

        //登り壁(左)
        pc3.AddPoint(17, 19);
        pc3.AddPoint(19, 19);
        pc3.AddPoint(19,  3);
        pc3.AddPoint(17,  3);
        colliders_.push_back(pc3);

        //登り壁(右)
        pc4.AddPoint(24, 19);
        pc4.AddPoint(26, 19);
        pc4.AddPoint(26,  4);
        pc4.AddPoint(24,  4);
        colliders_.push_back(pc4);
    }

    //上コース
    {
        //上コース床
        pc5.AddPoint(26, 19);
        pc5.AddPoint(29, 19);
        pc5.AddPoint(29, 15);
        pc5.AddPoint(26, 15);
        colliders_.push_back(pc5);

        //初はじき床
        pc6.AddPoint(29, 19);
        pc6.AddPoint(31, 19);
        pc6.AddPoint(31, 15);
        pc6.AddPoint(29, 15);
        pc6.AddRepel(6);
        colliders_.push_back(pc6);

        //上床②
        pc7.AddPoint(31, 19);
        pc7.AddPoint(38, 19);
        pc7.AddPoint(38, 15);
        pc7.AddPoint(31, 15);
        colliders_.push_back(pc7);

        //交互①
        pc8.AddPoint(38, 19);
        pc8.AddPoint(40, 19);
        pc8.AddPoint(40, 15);
        pc8.AddPoint(38, 15);
        colliders_.push_back(pc8);

        //交互②(はじく)
        pc9.AddPoint(40, 19);
        pc9.AddPoint(41.5f, 19);
        pc9.AddPoint(41.5f, 15);
        pc9.AddPoint(40, 15);
        pc9.AddRepel(9);
        colliders_.push_back(pc9);

        //交互③
        pc10.AddPoint(41.5f, 19);
        pc10.AddPoint(43, 19);
        pc10.AddPoint(43, 15);
        pc10.AddPoint(41.5f, 15);
        colliders_.push_back(pc10);

        //交互④(はじく)
        pc11.AddPoint(43, 19);
        pc11.AddPoint(44.5f, 19);
        pc11.AddPoint(44.5f, 15);
        pc11.AddPoint(43, 15);
        pc11.AddRepel(11);
        colliders_.push_back(pc11);

        //交互⑤
        pc12.AddPoint(44.5f, 19);
        pc12.AddPoint(46, 19);
        pc12.AddPoint(46, 15);
        pc12.AddPoint(44.5f, 15);
        colliders_.push_back(pc12);

        //交互⑥(はじく)
        pc13.AddPoint(46, 19);
        pc13.AddPoint(47.5f, 19);
        pc13.AddPoint(47.5f, 15);
        pc13.AddPoint(46, 15);
        pc13.AddRepel(13);
        colliders_.push_back(pc13);

        //交互⑦
        pc14.AddPoint(47.5f, 19);
        pc14.AddPoint(49, 19);
        pc14.AddPoint(49, 15);
        pc14.AddPoint(47.5f, 15);
        colliders_.push_back(pc14);

        //飛び床
        pc15.AddPoint(52, 17);
        pc15.AddPoint(58, 17);
        pc15.AddPoint(58, 13);
        pc15.AddPoint(52, 13);
        colliders_.push_back(pc15);

        //飛び床②
        pc16.AddPoint(61, 15);
        pc16.AddPoint(64, 15);
        pc16.AddPoint(64, 11);
        pc16.AddPoint(61, 11);
        colliders_.push_back(pc16);

        //飛び床③
        pc17.AddPoint(67, 13);
        pc17.AddPoint(69, 13);
        pc17.AddPoint(69, 11);
        pc17.AddPoint(67, 11);
        colliders_.push_back(pc17);

        //飛び床④
        pc18.AddPoint(72, 11);
        pc18.AddPoint(73, 11);
        pc18.AddPoint(73, 10);
        pc18.AddPoint(72, 10);
        colliders_.push_back(pc18);
    }

    //下コース
    {
        //下コース床
        pc19.AddPoint(24, 0);
        pc19.AddPoint(39, 0);
        pc19.AddPoint(39, -7);
        pc19.AddPoint(24, -7);
        colliders_.push_back(pc19);

        //沈む①
        pc20.AddPoint(39, 0);
        pc20.AddPoint(43, 0);
        pc20.AddPoint(43, -7);
        pc20.AddPoint(39, -7);
        pc20.AddSink(20);
        colliders_.push_back(pc20);

        //床②
        pc21.AddPoint(43, 0);
        pc21.AddPoint(49, 0);
        pc21.AddPoint(49, -7);
        pc21.AddPoint(43, -7);
        colliders_.push_back(pc21);

        //沈む②
        pc22.AddPoint(49, -0.5f);
        pc22.AddPoint(52, -0.5f);
        pc22.AddPoint(52, -7);
        pc22.AddPoint(49, -7);
        pc22.AddSink(22);
        colliders_.push_back(pc22);

        //床③
        pc23.AddPoint(52, 0);
        pc23.AddPoint(56, 0);
        pc23.AddPoint(56, -7);
        pc23.AddPoint(52, -7);
        colliders_.push_back(pc23);

        //飛び床⑤
        pc24.AddPoint(58, 1);
        pc24.AddPoint(63, 1);
        pc24.AddPoint(63, -3);
        pc24.AddPoint(58, -3);
        colliders_.push_back(pc24);

        //飛び床⑥
        pc25.AddPoint(65, 3);
        pc25.AddPoint(69, 3);
        pc25.AddPoint(69, -1);
        pc25.AddPoint(65, -1);
        colliders_.push_back(pc25);

        //飛び床⑦
        pc26.AddPoint(71, 4);
        pc26.AddPoint(72, 4);
        pc26.AddPoint(72, 3);
        pc26.AddPoint(71, 3);
        colliders_.push_back(pc26);
    }

    //合流した所の床
    pc27.AddPoint(74, 6);
    pc27.AddPoint(84, 6);
    pc27.AddPoint(84, 3);
    pc27.AddPoint(74, 3);
    colliders_.push_back(pc27);

    //ギミック有りの壁
    {
        //壁下の沈む床
        pc28.AddPoint(84,  6);
        pc28.AddPoint(88,  6);
        pc28.AddPoint(88, -3);
        pc28.AddPoint(84, -3);
        pc28.AddSink(28);
        colliders_.push_back(pc28);

        //右の壁
        //普通
        pc29.AddPoint(88, 11);
        pc29.AddPoint(91, 11);
        pc29.AddPoint(91,  2);
        pc29.AddPoint(88,  2);
        colliders_.push_back(pc29);

        //はじく①
        pc30.AddPoint(88, 12);
        pc30.AddPoint(91, 12);
        pc30.AddPoint(91, 11);
        pc30.AddPoint(88, 11);
        pc30.AddRepel(30);
        colliders_.push_back(pc30);

        //普通
        pc31.AddPoint(88, 13.5f);
        pc31.AddPoint(91, 13.5f);
        pc31.AddPoint(91, 12);
        pc31.AddPoint(88, 12);
        colliders_.push_back(pc31);

        //はじく②
        pc32.AddPoint(88, 14.5f);
        pc32.AddPoint(91, 14.5f);
        pc32.AddPoint(91, 13.5f);
        pc32.AddPoint(88, 13.5f);
        pc32.AddRepel(32);
        colliders_.push_back(pc32);

        //普通
        pc33.AddPoint(88, 17);
        pc33.AddPoint(91, 17);
        pc33.AddPoint(91, 14.5f);
        pc33.AddPoint(88, 14.5f);
        colliders_.push_back(pc33);

        //左の壁
        //普通
        pc34.AddPoint(81,12);
        pc34.AddPoint(84,12);
        pc34.AddPoint(84, 9);
        pc34.AddPoint(81, 9);
        colliders_.push_back(pc34);

        //はじく③
        pc35.AddPoint(81,13);
        pc35.AddPoint(84,13);
        pc35.AddPoint(84,12);
        pc35.AddPoint(81,12);
        pc35.AddRepel(35);
        colliders_.push_back(pc35);

        //普通
        pc36.AddPoint(81,15);
        pc36.AddPoint(84,15);
        pc36.AddPoint(84,13);
        pc36.AddPoint(81,13);
        colliders_.push_back(pc36);

        //はじく④
        pc37.AddPoint(81,16);
        pc37.AddPoint(84,16);
        pc37.AddPoint(84,15);
        pc37.AddPoint(81,15);
        pc37.AddRepel(37);
        colliders_.push_back(pc37);


        //普通
        pc38.AddPoint(81,20);
        pc38.AddPoint(84,20);
        pc38.AddPoint(84,16);
        pc38.AddPoint(81,16);
        colliders_.push_back(pc38);

    }

    //飛び石ゾーン
    {
        //飛び石①
        pc39.AddPoint(92,17);
        pc39.AddPoint(95,17);
        pc39.AddPoint(95,15);
        pc39.AddPoint(92,15);
        colliders_.push_back(pc39);

        //飛び石②
        pc40.AddPoint(96,17);
        pc40.AddPoint(99,17);
        pc40.AddPoint(99,15);
        pc40.AddPoint(96,15);
        colliders_.push_back(pc40);

        //飛び石③
        pc41.AddPoint(100.5f,17);
        pc41.AddPoint(102.5f,17);
        pc41.AddPoint(102.5f,15);
        pc41.AddPoint(100.5f,15);
        colliders_.push_back(pc41);

        //飛び石④
        pc42.AddPoint(104,17);
        pc42.AddPoint(106,17);
        pc42.AddPoint(106,15);
        pc42.AddPoint(104,15);
        colliders_.push_back(pc42);

        //飛び石⑤
        pc43.AddPoint(108,17);
        pc43.AddPoint(109,17);
        pc43.AddPoint(109,15);
        pc43.AddPoint(108,15);
        colliders_.push_back(pc43);

        //飛び石⑥
        pc44.AddPoint(111,17);
        pc44.AddPoint(112,17);
        pc44.AddPoint(112,15);
        pc44.AddPoint(111,15);
        colliders_.push_back(pc44);

        //飛び石⑦
        pc45.AddPoint(114.25f,16.25f);
        pc45.AddPoint(114.75f,16.25f);
        pc45.AddPoint(114.75f,15.75f);
        pc45.AddPoint(114.25f,15.75f);
        colliders_.push_back(pc45);
        
        //飛び石⑧
        pc46.AddPoint(116.75f,16.25f);
        pc46.AddPoint(117.25f,16.25f);
        pc46.AddPoint(117.25f,15.75f);
        pc46.AddPoint(116.75f,15.75f);
        colliders_.push_back(pc46);

        //飛び石⑨
        pc47.AddPoint(119.75f,16.25f);
        pc47.AddPoint(120.25f,16.25f);
        pc47.AddPoint(120.25f,15.75f);
        pc47.AddPoint(119.75f,15.75f);
        colliders_.push_back(pc47);

        //飛び石⑩
        pc48.AddPoint(123.75f,16.25f);
        pc48.AddPoint(124.25f,16.25f);
        pc48.AddPoint(124.25f,15.75f);
        pc48.AddPoint(123.75f,15.75f);
        colliders_.push_back(pc48);
    }

    //ゴール
    {
        //ゴール床
        pc49.AddPoint(128, 16);
        pc49.AddPoint(144, 16);
        pc49.AddPoint(144,  0);
        pc49.AddPoint(128,  0);
        colliders_.push_back(pc49);

        //ゴール壁
        pc50.AddPoint(144, 32);
        pc50.AddPoint(157, 32);
        pc50.AddPoint(157,  0);
        pc50.AddPoint(144,  0);
        colliders_.push_back(pc50);
    }



    //スタートとゴールの設定
    gl.SetCameraStart(startX, startY);
    gl.SetCameraGoal(goalX, goalY);
}

//Stage3の読み込み
void Stage::Stage3Load()
{
    //ステージモデルと背景を読み込み
    StageModel_ = Model::Load("Model/Stage/Stage3/stage3.fbx");
    assert(StageModel_ >= 0);
    BackImage_ = Image::Load("Image/StageScene/Stage3_Back.png");
    assert(BackImage_ >= 0);

    //数字   
    NumberImage_ = Image::Load("Image/StageScene/Number.png");
    assert(NumberImage_ >= 0);

    //数字の背景
    DengerImage_ = Image::Load("Image/StageScene/Denger.png");
    assert(DengerImage_ >= 0);

    //サウンドを追加
    for (int i = 0; i < St3_Max; i++)
    {
        Sound_ = -1;

        switch (i)
        {
        case St3_Iron:
            Sound_ = Audio::Load("Sound/InStage/Stage3/FootStep_Iron.wav"); break;
        case St3_Sand:
            Sound_ = Audio::Load("Sound/InStage/Stage3/FootStep_Sand.wav"); break;
        case St3_Volcano_Sand:
            Sound_ = Audio::Load("Sound/InStage/Stage3/FootStep_Volcano_Sand.wav"); break;
        case St3_Volcano:
            Sound_ = Audio::Load("Sound/InStage/Stage3/FootStep_Volcano.wav"); break;
        }
        assert(Sound_ >= 0);
    }

    //コインの位置
    Global::ItemModelPos = ST3_ITEMMODEL_POS;
}


//はじく床をチェック
void Stage::RepelCheck(int i)
{
    pScissors_ = (Scissors*)FindObject("Scissors");

    PolygonCollider pc;
    pc.SetRepel(i);

    //引数と同じ値ならば
    if (i == pc.GetRepel())
    {
        //フラグをtrue
        RepelFlg = true;
        pScissors_->IsJump = false;
        pScissors_->CurrentHP -= REPEL_DAMAGE;

    }
    //そうでなければ戻す
    else
    {
        RepelFlg = false;
        pScissors_->IsJump = true;
    }
}

//沈む床をチェック
void Stage::SinkCheck(int i)
{
    PolygonCollider pc;
    pc.SetSink(i);

    //引数と同じ値ならば
    if (i == pc.GetSink())
    {
        //フラグをtrue
        SinkFlg = true;
        pScissors_->JumpStart = 0;
        pScissors_->JumpEnd = 0;
    }
    //そうでなければ戻す
    else
    {
        SinkFlg = false;
    }
}
