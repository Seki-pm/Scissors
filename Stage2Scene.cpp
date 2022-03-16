#include "Stage2Scene.h"

//�R���X�g���N�^
Stage2Scene::Stage2Scene(GameObject* parent)
	: GameObject(parent, "Stage2Scene")
{
}

//������
void Stage2Scene::Initialize()
{
    Global::MAXHP = 500;
    Global::HP = Global::MAXHP;
    Global::GameOver = false;

    //�X�e�[�W
    Instantiate<Stage>(this);

    //�n�T�~�{��
    Instantiate<Scissors>(this);

    //�n�T�~��HP
    Instantiate<HP>(this);

    //�A�C�e���̕\��
    Instantiate<ItemModel>(this);

    //�R�C���̃Q�b�g����
    Instantiate<ItemImage>(this);
}

//�X�V
void Stage2Scene::Update()
{
    Global gl;

    X = gl.GetTransPos_X();
    Y = gl.GetTransPos_Y();
    Z = gl.GetTransPos_Z();

    CameraMove(gl.GetCameraStart(), gl.GetCameraGoal());

    //�Q�[���I�[�o�[
    if (Global::GameOver) {
        Instantiate<GameOver>(this);
    }

}

//�`��
void Stage2Scene::Draw()
{
}

//�J��
void Stage2Scene::Release()
{
}

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
        Camera::SetPosition(XMFLOAT3(56, Y, -10));
        Camera::SetTarget(XMFLOAT3(56, Y, Z));
        Global::Unlock3 = true;
        if (Input::IsKeyDown(DIK_LSHIFT))
        {
            SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
            pSceneManager->ChangeScene(SCENE_ID_SELECT);
        }
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

