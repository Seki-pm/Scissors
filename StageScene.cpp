#include "StageScene.h"

//�R���X�g���N�^
StageScene::StageScene(GameObject* parent)
	: GameObject(parent, "StageScene"),pStage_(nullptr),
    Pos_X(0),Pos_Y(0),Pos_Z(0)
{
}

//������
void StageScene::Initialize()
{
    Global::HP = Global::MAXHP;
    Global::ItemImagePos = Global::ItemImagePos_Stage;
    Global::ItemImageSca = Global::ItemImageSca_Stage;
    Global::GameOver = false;
    Global::IsGameOver = false;
    Global::GetCoin = false;

    //�X�e�[�W
    pStage_ = Instantiate<Stage>(this); 
    pStage_->Load(Global::Select);

    //�n�T�~�{��
    Instantiate<Scissors>(this);

    //�n�T�~��HP
    Instantiate<HP>(this);

    //�S�[�����o
    Instantiate<GoalStaging>(this);

    //�A�C�e���̕\��
    Instantiate<ItemModel>(this);

    //�R�C���̃Q�b�g����
    Instantiate<ItemImage>(this);
}

//�X�V
void StageScene::Update()
{
    //true�̎��A�����b�N�����A�X�e�[�W�I���֑J��
    if (Global::Timer)
    {
        //Global::Unlock3 = true;
        Global::Timer = false;
        SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
        pSceneManager->ChangeScene(SCENE_ID_SELECT);
    }

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

}

//�`��
void StageScene::Draw()
{
    Image::Draw(BackImage_);
}

//�J��
void StageScene::Release()
{
    BackImage_ = -1;
    SelectSound_ = -1;
    DeterSound_ = -1;
    Global::Repel_.clear();
    Global::Sink_.clear();
}

void StageScene::GameOverSEL()
{
    GameOver* pGameOver = (GameOver*)FindObject("GameOver");

    if (Global::IsGameOver)
    {
        //GameOver�\��
        Instantiate<GameOver>(this);
        Global::IsGameOver = false;
    }

    //GameOver�ɂȂ�����
    if (Global::GameOver)
    {
        //�{�^����I��
        //�I��
        if (Input::IsKeyDown(DIK_LEFT))
        {
            Gselect_--;
            Audio::Play(SelectSound_);

            if (Gselect_ < 0)
            {
                Gselect_ = 0;
            }

            //GameOver�N���X�ɓn��
            pGameOver->SetSelect(Gselect_);
        }
        if (Input::IsKeyDown(DIK_RIGHT))
        {
            Gselect_++;
            Audio::Play(SelectSound_);

            if (Gselect_ > 1)
            {
                Gselect_ = 1;
            }

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
            Pselect_--;
            Audio::Play(SelectSound_);

            if (Pselect_ < 0)
            {
                Pselect_ = 0;
            }

            //Pause�N���X�ɓn��
            pPause->SetSelect(Pselect_);
        }
        if (Input::IsKeyDown(DIK_RIGHT))
        {
            Pselect_++;
            Audio::Play(SelectSound_);

            if (Pselect_ > 1)
            {
                Pselect_ = 1;
            }

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
        Camera::SetPosition(XMFLOAT3(global.GetCameraGoalX()-2, Pos_Y, -10));
        Camera::SetTarget(XMFLOAT3(global.GetCameraGoalX()-2, Pos_Y, Pos_Z));
    }
    //�����łȂ��ꍇPlayer�ɒǏ]����
    else
    {
        Camera::SetPosition(XMFLOAT3(Pos_X, Pos_Y, -10));
        Camera::SetTarget(XMFLOAT3(Pos_X, Pos_Y, Pos_Z));
    }


    //transform.y ��0��菬�����ꍇ�J�������~�߂�
    if (Pos_Y < -5)
    {
        Camera::SetPosition(XMFLOAT3(Pos_X, 3, -10));
        Camera::SetTarget(XMFLOAT3(Pos_X, 3, Pos_Z));
    }
}
