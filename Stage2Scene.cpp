#include "Stage2Scene.h"

//�R���X�g���N�^
Stage2Scene::Stage2Scene(GameObject* parent)
	: GameObject(parent, "Stage2Scene"), select_(0), BackImage_(-1)
{
}

//������
void Stage2Scene::Initialize()
{
    Global::HP = Global::MAXHP;
    Global::GameOver = false;
    Global::IsGameOver = false;

    //�X�e�[�W
    Instantiate<Stage>(this);

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

    BackImage_ = Image::Load("Image/Stage2_Back.png");
    assert(BackImage_ >= 0);
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
            select_--;

            if (select_ < 0)
            {
                select_ = 0;
            }

            //GameOver�N���X�ɓn��
            pGameOver->SetSelect(select_);
        }
        if (Input::IsKeyDown(DIK_RIGHT))
        {
            select_++;

            if (select_ > 1)
            {
                select_ = 1;
            }

            //GameOver�N���X�ɓn��
            pGameOver->SetSelect(select_);
        }

        if (Input::IsKeyDown(DIK_SPACE) && select_ == 1)
        {
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

