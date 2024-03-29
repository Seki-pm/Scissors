#include "Sign.h"

//コンストラクタ
Sign::Sign(GameObject* parent)
    :GameObject(parent, "Sign"),
    Tutorial_(INITIAL_ERROR_VALUE), 
    Tutorial2_(INITIAL_ERROR_VALUE)
{
    for (int i = 1; i < Tips_MAX; i++)
    {
        TipsModel_[i] = INITIAL_ERROR_VALUE;
    }
}

//デストラクタ
Sign::~Sign()
{
}

//初期化
void Sign::Initialize()
{
    //------------------ 看板モデルのロード ---------------------
    {
        //方向を決める...ジャンプ...
        TipsModel_[Tips_1] = Model::Load("Model/InGameObject/Sign1.fbx");
        assert(TipsModel_[Tips_1] >= 0);
        SignTrans.position_ = SIGN1_POS;
        SignTrans.scale_ = SIGN_SIZE;
        Model::SetTransform(TipsModel_[Tips_1], SignTrans);

        //刃が地面に刺さってる時は,,,
        TipsModel_[Tips_2] = Model::Load("Model/InGameObject/Sign2.fbx");
        assert(TipsModel_[Tips_2] >= 0);
        SignTrans2.position_ = SIGN2_POS;
        SignTrans2.scale_ = SIGN_SIZE;
        Model::SetTransform(TipsModel_[Tips_2], SignTrans2);

        //刃が地面に着くたびに...
        TipsModel_[Tips_3] = Model::Load("Model/InGameObject/Sign3.fbx");
        assert(TipsModel_[Tips_3] >= 0);
        auto SignTrans3 = Transform();
        SignTrans3.position_ = SIGN3_POS;
        SignTrans3.scale_ = SIGN_SIZE;
        Model::SetTransform(TipsModel_[Tips_3], SignTrans3);

        //[Esc]を押すと...
        TipsModel_[Tips_4] = Model::Load("Model/InGameObject/Sign4.fbx");
        assert(TipsModel_[Tips_4] >= 0);
        auto SignTrans4 = Transform();
        SignTrans4.position_ = SIGN4_POS;
        SignTrans4.scale_ = SIGN_SIZE;
        Model::SetTransform(TipsModel_[Tips_4], SignTrans4);


        //壁に刃を向けてジャンプすると...
        TipsModel_[Tips_5] = Model::Load("Model/InGameObject/Sign5.fbx");
        assert(TipsModel_[Tips_5] >= 0);
        SignTrans5.position_ = SIGN5_POS;
        SignTrans5.scale_ = SIGN_SIZE;
        Model::SetTransform(TipsModel_[Tips_5], SignTrans5);


        //壁でも地面と同じ様に...
        TipsModel_[Tips_6] = Model::Load("Model/InGameObject/Sign6.fbx");
        assert(TipsModel_[Tips_6] >= 0);
        auto SignTrans6 = Transform();
        SignTrans6.position_ = SIGN6_POS;
        SignTrans6.scale_ = SIGN_SIZE;
        Model::SetTransform(TipsModel_[Tips_6], SignTrans6);
    }
    //-----------------------------------------------------------

    //-----------------  チュートリアル画像  --------------------
    {
        //チュートリアル1
        Tutorial_ = Image::Load("Image/StageScene/Tutorial.png");
        assert(Tutorial_ >= 0);
        auto TutorialTrans = Transform();
        TutorialTrans.position_ = TUTORIAL_POS;
        TutorialTrans.scale_ = TUTORIAL_SCA;
        Image::SetTransform(Tutorial_, TutorialTrans);

        //チュートリアル2
        Tutorial2_ = Image::Load("Image/StageScene/Tutorial2.png");
        assert(Tutorial2_ >= 0);
        Image::SetTransform(Tutorial2_, TutorialTrans);
    }
    //-----------------------------------------------------------

}

//更新
void Sign::Update()
{
}

//描画
void Sign::Draw()
{
    //看板の描画
    for (int i = 1; i < Tips_MAX; i++)
    {
        Model::Draw(TipsModel_[i]);
    }
    

    //条件付きでチュートリアルの描画
    if (game.GetTransPos().x >= SignTrans.position_.x &&
        game.GetTransPos().x <= SignTrans2.position_.x)
    {
        Image::Draw(Tutorial_);
    }

    if (game.GetTransPos().x >= SignTrans5.position_.x &&
        game.GetTransPos().x <= 42 &&
        game.GetTransPos().y <= 4.5f)
    {
        Image::Draw(Tutorial2_);
    }
}

//開放
void Sign::Release()
{
    for (int i = 1; i < Tips_MAX; i++)
    {
        TipsModel_[i] = INITIAL_ERROR_VALUE;
    }
    Tutorial_ = INITIAL_ERROR_VALUE;
    Tutorial2_ = INITIAL_ERROR_VALUE;
}