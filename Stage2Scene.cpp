#include "Stage2Scene.h"

//�R���X�g���N�^
Stage2Scene::Stage2Scene(GameObject* parent)
	: GameObject(parent, "Stage2Scene"),
    BackImage_(-1), SelectSound_(-1), DeterSound_(-1),
    X(0),Y(0),Z(0), Gselect_(0), Pselect_(0)
{
}

//������
void Stage2Scene::Initialize()
{
    Global::HP = Global::MAXHP;
    Global::ItemImagePos = Global::ItemImagePos_Stage;
    Global::ItemImageSca = Global::ItemImageSca_Stage;
    Global::GameOver = false;
    Global::IsGameOver = false;
    Global::GetCoin = false;

    //�X�e�[�W
    Instantiate<Stage>(this);

    //�n�T�~�{��
    Instantiate<Scissors>(this);

    //�n�T�~��HP
    Instantiate<HP>(this);

    //�S�[�����o
    Instantiate<GoalStaging>(this);

    //�A�C�e���̕\��
    Global::ItemModelPos = XMFLOAT3(-1.5, 17, 0);
    Instantiate<ItemModel>(this);

    //�R�C���̃Q�b�g����
    Instantiate<ItemImage>(this);


    //------ �w�i ---------
    BackImage_ = Image::Load("Image/Stage2_Back.png");
    assert(BackImage_ >= 0);

    //------ Select --------------
    SelectSound_ = Audio::Load("Sound/Select.wav");
    assert(SelectSound_ >= 0);

    //------ Determination -------------
    DeterSound_ = Audio::Load("Sound/Determination.wav");
    assert(DeterSound_ >= 0);
}

//�X�V
void Stage2Scene::Update()
{
    //true�̎��A�����b�N�����A�X�e�[�W�I���֑J��
    if (Global::Timer)
    {
        Global::Unlock3 = true;
        Global::Timer = false;
        SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
        pSceneManager->ChangeScene(SCENE_ID_SELECT);
    }

    //�n�T�~�ʒu���擾
    Global gl;

    X = gl.GetTransPos_X();
    Y = gl.GetTransPos_Y();
    Z = gl.GetTransPos_Z();

    //�X�e�[�W�̃X�^�[�g&�S�[���ʒu������
    CameraMove(gl.GetCameraStartX(), gl.GetCameraGoalX());

    //�Q�[���I�[�o�[
    GameOverSEL();

    //�ꎞ��~
    PauseSEL();
}

//�`��
void Stage2Scene::Draw()
{
    Image::Draw(BackImage_);
}

//�J��
void Stage2Scene::Release()
{
    BackImage_ = -1;
    SelectSound_ = -1;
    DeterSound_ = -1;
}

//GameOver Select
void Stage2Scene::GameOverSEL()
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

//�ꎞ��~
void Stage2Scene::PauseSEL()
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
void Stage2Scene::CameraMove(float start, float goal)
{

    //transform.x �ɉ����ăJ�����ړ����~�߂�
    //�X�^�[�g�t��
    if (X < start)
    {
        Camera::SetPosition(XMFLOAT3(2, Y, -10));
        Camera::SetTarget(XMFLOAT3(2, Y, Z));
    }
    //�S�[���t��
    else if (X >= goal)
    {
        Camera::SetPosition(XMFLOAT3(125, Y, -10));
        Camera::SetTarget(XMFLOAT3(125, Y, Z));
    }
    //�����łȂ��ꍇPlayer�ɒǏ]����
    else
    {
        Camera::SetPosition(XMFLOAT3(X, Y, -10));
        Camera::SetTarget(XMFLOAT3(X, Y, Z));
    }


    //transform.y ��0��菬�����ꍇ�J�������~�߂�
    if (Y < -5)
    {
        Camera::SetPosition(XMFLOAT3(X, 3, -10));
        Camera::SetTarget(XMFLOAT3(X, 3, Z));
    }
}

