#include "StageScene.h"



//�R���X�g���N�^
StageScene::StageScene(GameObject* parent)
	: GameObject(parent, "StageScene"),pStage_(nullptr),
    Pos_X(0),Pos_Y(0),Pos_Z(0), Gselect_(-1), Pselect_(-1),
    SelectSound_(-1), DeterSound_(-1)
{
}

//������
void StageScene::Initialize()
{
    Global::HP = Global::MAXHP;                             //�ő�̗͂�ݒ�
    Global::ItemImagePos = Global::ItemImagePos_Stage;      //�R�C���̈ʒu���X�e�[�W�p�ɐݒ�
    Global::ItemImageSca = Global::ItemImageSca_Stage;      //�R�C���̑傫�����X�e�[�W�p�ɐݒ�
    Global::GameOver = false;                               //GameOver�ł͂Ȃ�
    Global::IsGameOver = false;                             //GameOver�ł͂Ȃ�
    Global::GetCoin = false;                                //�R�C�����擾���Ă��Ȃ�

    //�X�e�[�W
    pStage_ = Instantiate<Stage>(this);
    pStage_->Load(Global::SelectStage);


    //�n�T�~�{��
    Instantiate<Scissors>(this);

    //�n�T�~��HP
    Instantiate<HP>(this);

    //�A�C�e���̕\��
    Instantiate<ItemModel>(this);

    //�R�C���̃Q�b�g����
    Instantiate<ItemImage>(this);

    //�S�[�����o
    Instantiate<GoalStaging>(this);
}

//�X�V
void StageScene::Update()
{
    //�n�T�~�̈ʒu���擾
    Pos_X = global.GetTransPos_X();
    Pos_Y = global.GetTransPos_Y();
    Pos_Z = global.GetTransPos_Z();

    //�X�e�[�W�̃X�^�[�g&�S�[���ʒu������
    CameraMove(global.GetCameraStartX(), global.GetCameraGoalX());

    //�Q�[���I�[�o�[
    GameOverSEL();

    //�ꎞ��~
    PauseSEL();

    //�S�[�����o�p
    Timer();

    //�擾���Ă���GameOver�̏ꍇ�R�C�����ĕ\������
    //�擾���Ă�����͎̂擾���ĂȂ����ƂƂ���
    if (Global::GetCoin && Global::ItemReDraw)
    {
        Instantiate<ItemModel>(this);
        Global::ItemReDraw = false;
        Global::GetCoin = false;
        Global::GetCoin_1 = false;
        Global::GetCoin_2 = false;
        Global::GetCoin_3 = false;
    }
}

//�`��
void StageScene::Draw()
{
}

//�J��
void StageScene::Release()
{
    SelectSound_ = -1;
    DeterSound_ = -1;
    Global::Repel_.clear();
    Global::Sink_.clear();
}

//GameOver
void StageScene::GameOverSEL()
{
    GameOver* pGameOver = (GameOver*)FindObject("GameOver");

    if (Global::IsGameOver)
    {
        //GameOver�\��
        Instantiate<GameOver>(this);
        Global::IsGameOver = false;
        Global::ItemReDraw = true;
    }

    //GameOver�ɂȂ�����
    if (Global::GameOver)
    {
        //�{�^����I��
        //�I��
        if (Input::IsKeyDown(DIK_LEFT))
        {
            Gselect_ = 0;
            Audio::Play(SelectSound_);

            //GameOver�N���X�ɓn��
            pGameOver->SetSelect(Gselect_);
        }
        if (Input::IsKeyDown(DIK_RIGHT))
        {
            Gselect_ = 1;
            Audio::Play(SelectSound_);

            //GameOver�N���X�ɓn��
            pGameOver->SetSelect(Gselect_);
        }

        if (Input::IsKeyDown(DIK_SPACE) && Gselect_ == 1)
        {
            Audio::Play(DeterSound_);

            SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
            pSceneManager->ChangeScene(SCENE_ID_SELECT);
        }
    }
}

//Pause
void StageScene::PauseSEL()
{
    Pause* pPause = (Pause*)FindObject("Pause");

    //�ꎞ��~����(false�̎��̂�)
    if (!Global::Pause) {
        if (Input::IsKeyDown(DIK_ESCAPE))
        {
            Instantiate<Pause>(this);			//�ꎞ��~
            Global::Pause = true;
        }
    }
    //�ꎞ��~���ꂽ�Ƃ�
    if (Global::Pause)
    {
        //�{�^����I��
        if (Input::IsKeyDown(DIK_LEFT))
        {
            Pselect_ = 0;
            Audio::Play(SelectSound_);

            //Pause�N���X�ɓn��
            pPause->SetSelect(Pselect_);
        }
        if (Input::IsKeyDown(DIK_RIGHT))
        {
            Pselect_ = 1;
            Audio::Play(SelectSound_);

            //Pause�N���X�ɓn��
            pPause->SetSelect(Pselect_);
        }


        //���j���[�V�[���Ɉړ�����
        if (Input::IsKeyDown(DIK_SPACE) && Pselect_ == 1)
        {
            Global::GetCoin = false;
            Global::Pause = false;

            Audio::Play(DeterSound_);

            //���j���[�V�[���Ɉړ�
            SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
            pSceneManager->ChangeScene(SCENE_ID_SELECT);
        }
    }
}

//�J�����ړ�
void StageScene::CameraMove(float start, float goal)
{

    //transform.x �ɉ����ăJ�����ړ����~�߂�
    //�X�^�[�g�t��
    if (Pos_X < start)
    {
        Camera::SetPosition(XMFLOAT3(global.GetCameraStartX(), Pos_Y, -10));
        Camera::SetTarget(XMFLOAT3(global.GetCameraStartX(), Pos_Y, Pos_Z));
    }
    //�S�[���t��
    else if (Pos_X >= goal)
    {
        Camera::SetPosition(XMFLOAT3(global.GetCameraGoalX(), Pos_Y, -10));
        Camera::SetTarget(XMFLOAT3(global.GetCameraGoalX(), Pos_Y, Pos_Z));
    }
    //�����łȂ��ꍇPlayer�ɒǏ]����
    else
    {
        Camera::SetPosition(XMFLOAT3(Pos_X, Pos_Y, -10));
        Camera::SetTarget(XMFLOAT3(Pos_X, Pos_Y, Pos_Z));
    }


    //transform.y ��0��菬�����ꍇ�J�������~�߂�
    if (Pos_Y < -6)
    {
        Camera::SetPosition(XMFLOAT3(Pos_X, -3, -10));
        Camera::SetTarget(XMFLOAT3(Pos_X, -3, Pos_Z));
    }
}

//���̃X�e�[�W���A�����b�N
void StageScene::NextStageUnlock( int SelectStage )
{
    switch (SelectStage)
    {
    case STAGE_NUMBER_1:
        Global::Unlock2 = true;
        break;
    case STAGE_NUMBER_2:
        Global::Unlock3 = true;
        break;
    case STAGE_NUMBER_3:
        break;
    }
}

//�S�[�����o�p
void StageScene::Timer()
{
    //true�̎��A�����b�N�����A�X�e�[�W�I���֑J��
    if (Global::Timer)
    {
        NextStageUnlock(Global::SelectStage);
        Global::Timer = false;
        SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
        pSceneManager->ChangeScene(SCENE_ID_SELECT);
    }
}
