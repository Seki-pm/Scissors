#include "Stage1Scene.h"
#include "Engine/Camera.h"
#include "Engine/Input.h"
#include "Stage.h"
#include "Sign.h"
#include "HP.h"
#include "GameOver.h"



//�R���X�g���N�^
Stage1Scene::Stage1Scene(GameObject* parent)
    : GameObject(parent, "Stage1Scene")
{
}

//������
void Stage1Scene::Initialize()
{
    Global::MAXHP = 300;
    Global::GameOver = false;

    //�X�e�[�W
    Instantiate<Stage>(this);

    //�Ŕ�
    Instantiate<Sign>(this);

    //�n�T�~�{��
    Instantiate<Scissors>(this);

    //�n�T�~��HP
    Instantiate<HP>(this);

}

//�X�V
void Stage1Scene::Update()
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
void Stage1Scene::Draw()
{
}

//�J��
void Stage1Scene::Release()
{
}

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
        XMFLOAT3 CamPos = XMFLOAT3(56, Y, -10);


        Camera::SetPosition(XMFLOAT3(56, Y, -10));
        Camera::SetTarget(XMFLOAT3(56, Y, Z));
        Global::Unlock2 = true;
        if (Input::IsKeyDown(DIK_LSHIFT))
        {
            SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
            pSceneManager->ChangeScene(SCENE_ID_SELECT);
        }
    }
    //�����łȂ��ꍇPlayer�ɒǏ]����
    else
    {
        Camera::SetPosition(XMFLOAT3(X, 3 ,-10));
        Camera::SetTarget(XMFLOAT3(X, 3, Z));
    }


    //transform.y ��0��菬�����ꍇ�J�������~�߂�
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