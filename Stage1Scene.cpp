#include "Stage1Scene.h"


//�R���X�g���N�^
Stage1Scene::Stage1Scene(GameObject* parent)
    : GameObject(parent, "Stage1Scene"),
    X(0),Y(0),Z(0), BackImage_(-1),
    pNumber_(nullptr),Itemflg(false),
    cnt(0), Gselect_(0), Pselect_(0)
{
}

//������
void Stage1Scene::Initialize()
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

    //�Ŕ�
    Instantiate<Sign>(this);

    //�R�C���̃Q�b�g����
    Instantiate<ItemImage>(this);

    //�R�C���̕\���ʒu
    Global::ItemModelPos = XMFLOAT3(47, 9, 0);


    BackImage_ = Image::Load("Image/Stage1_Back.png");
    assert(BackImage_ >= 0);
}

//�X�V
void Stage1Scene::Update()
{
    //true�̎��A�����b�N�����A�X�e�[�W�I���֑J��
    if (Global::Timer)
    {
        Global::Unlock2 = true;
        Global::Timer = false;
        SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
        pSceneManager->ChangeScene(SCENE_ID_SELECT);
    }

    //�n�T�~�ʒu���擾
    X = gl.GetTransPos_X();
    Y = gl.GetTransPos_Y();
    Z = gl.GetTransPos_Z();

    //�X�e�[�W�̃X�^�[�g&�S�[���ʒu������
    CameraMove(gl.GetCameraStartX(), gl.GetCameraGoalX());

    //GameOverSelect
    GameOverSEL();

    //�ꎞ��~
    PauseSEL();

    //Coin��\��
    if (Itemflg  && cnt == 0)
    {
        Instantiate<ItemModel>(this);
        cnt++;
    }
}

//�`��
void Stage1Scene::Draw()
{
    Image::Draw(BackImage_);
}

//�J��
void Stage1Scene::Release()
{
    BackImage_ = -1;
}

//GameOver Select
void Stage1Scene::GameOverSEL()
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

            if (Gselect_ > 1)
            {
                Gselect_ = 1;
            }

            //GameOver�N���X�ɓn��
            pGameOver->SetSelect(Gselect_);
        }

        if (Input::IsKeyDown(DIK_SPACE) && Gselect_ == 1)
        {
            SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
            pSceneManager->ChangeScene(SCENE_ID_SELECT);
        }
    }
}

//�ꎞ��~
void Stage1Scene::PauseSEL()
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

            //���j���[�V�[���Ɉړ�
            SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
            pSceneManager->ChangeScene(SCENE_ID_SELECT);
        }
    }
}

//�J�����ړ�
void Stage1Scene::CameraMove(float start, float goal)
{

    //transform.x �ɉ����ăJ�����ړ����~�߂�
    //�X�^�[�g�t��
    if (X < start)
    {
        Camera::SetPosition(XMFLOAT3(2, 3, -10));
        Camera::SetTarget(XMFLOAT3(2, 3, Z));
    }
    //�S�[���t��
    else if (X >= goal)
    {
        Camera::SetPosition(XMFLOAT3(55, Y, -10));
        Camera::SetTarget(XMFLOAT3(55, Y, Z));
        Itemflg = true;
    }
    //�����łȂ��ꍇPlayer�ɒǏ]����
    else
    {
        Camera::SetPosition(XMFLOAT3(X, 3 ,-10));
        Camera::SetTarget(XMFLOAT3(X, 3, Z));
    }


    //transform.y ��0��菬�����i���ɗ������j�ꍇ�J�������~�߂�
    if (Y < -5)
    {
        Camera::SetPosition(XMFLOAT3(X, 3, -10));
        Camera::SetTarget(XMFLOAT3(X, 3, Z));
    }
    else if (Y > 5)
    {
        Camera::SetPosition(XMFLOAT3(X, 6, -10));
        Camera::SetTarget(XMFLOAT3(X, 6, Z));
    }
}