#include "StageScene.h"


//�R���X�g���N�^
StageScene::StageScene(GameObject* parent)
	: GameObject(parent, "StageScene"),
      Gselect_(0), Pselect_(0)
{
}

//������
void StageScene::Initialize()
{                      
    Global::ItemImagePos = ITEMIMAGE_POSITION_STAGE;      //�R�C���̈ʒu���X�e�[�W�p�ɐݒ�
    Global::ItemImageSca = ITEMIMAGE_SCALE_STAGE;         //�R�C���̑傫�����X�e�[�W�p�ɐݒ�
    Global::GameOver = false;                             //GameOver�ł͂Ȃ�
    Global::IsGameOver = false;                           //GameOver�ł͂Ȃ�
    GetCoinJudge();                                       //�R�C�����蔻��

    //�X�e�[�W
    Stage* pStage_ = Instantiate<Stage>(this);
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
    //�X�e�[�W�̃X�^�[�g&�S�[���ʒu������
    CameraMove(gl.GetCameraStart().x, gl.GetCameraGoal().x);

    //�Q�[���I�[�o�[
    GameOverSEL();

    //�ꎞ��~
    PauseSEL();

    //�S�[�����o�p
    Timer();

    //�擾���Ă��烊�X�^�[�g�̏ꍇ�R�C�����ĕ\������
    //�擾���Ă�����͎̂擾���ĂȂ��l�ɂ���
    if (Global::GetCoin && Global::ItemReDraw)
    {
        Instantiate<ItemModel>(this);
        Global::ItemReDraw = false;
        GetCoinJudge(); //�R�C�����蔻��
    }


}

//�`��
void StageScene::Draw()
{
}

//�J��
void StageScene::Release()
{
}

//�Q�[���I�[�o�[
void StageScene::GameOverSEL()
{
    GameOver* pGameOver_ = (GameOver*)FindObject("GameOver");

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
        {
            if (Input::IsKeyDown(DIK_LEFT))
            {
                Gselect_ = 0;
                //GameOver�N���X�ɓn��
                pGameOver_->SetSelect(Gselect_);
            }
            if (Input::IsKeyDown(DIK_RIGHT))
            {
                Gselect_ = 1;
                //GameOver�N���X�ɓn��
                pGameOver_->SetSelect(Gselect_);
            }
        }

        //SPACE���������Ƃ�
        if (Input::IsKeyDown(DIK_SPACE))
        {
            if (Gselect_ == 0)
            {
                pGameOver_->KillMe();     //GameOver������
                pGameOver_->pScissors_->Restart(); //�X�^�[�g�ɖ߂�
            }
            else if (Gselect_ == 1)
            {
                //�X�e�[�W�I���V�[���Ɉړ�
                SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
                pSceneManager->ChangeScene(SCENE_ID_SELECT);
            }
        }
    }
}

//�|�[�Y
void StageScene::PauseSEL()
{
    Pause* pPause_ = (Pause*)FindObject("Pause");

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
        {
            if (Input::IsKeyDown(DIK_LEFT))
            {
                Pselect_ = 0;
                //Pause�N���X�ɓn��
                pPause_->SetSelect(Pselect_);
            }
            if (Input::IsKeyDown(DIK_RIGHT))
            {
                Pselect_ = 1;
                //Pause�N���X�ɓn��
                pPause_->SetSelect(Pselect_);
            }
        }

        //SPACE���������Ƃ�
        if (Input::IsKeyDown(DIK_SPACE))
        {
            Global::Pause = false;

            if (Pselect_ == 0)
            {
                pPause_->KillMe(); //Pause������
            }
            else if (Pselect_ == 1)
            {
                
                GetCoinJudge(); //�R�C�����蔻��

                //�X�e�[�W�I���V�[���Ɉړ�
                SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
                pSceneManager->ChangeScene(SCENE_ID_SELECT);
            }
        }
    }
}

//�J�����ړ�
void StageScene::CameraMove(float start, float goal)
{
    //transform.x �ɉ����ăJ�����ړ����~�߂�
    //�X�^�[�g�t��
    if (gl.GetTransPos().x < start)
    {
        Camera::SetPosition(XMFLOAT3(gl.GetCameraStart().x, gl.GetTransPos().y, CAMERA_SET_POS));
        Camera::SetTarget(XMFLOAT3(gl.GetCameraStart().x, gl.GetTransPos().y, gl.GetTransPos().z));
    }
    //�S�[���t��
    else if (gl.GetTransPos().x >= goal)
    {
        Camera::SetPosition(XMFLOAT3(gl.GetCameraGoal().x, gl.GetTransPos().y, CAMERA_SET_POS));
        Camera::SetTarget(XMFLOAT3(gl.GetCameraGoal().x, gl.GetTransPos().y, gl.GetTransPos().z));
    }
    //�����łȂ��ꍇPlayer�ɒǏ]����
    else
    {
        Camera::SetPosition(XMFLOAT3(gl.GetTransPos().x, gl.GetTransPos().y, CAMERA_SET_POS));
        Camera::SetTarget(XMFLOAT3(gl.GetTransPos().x, gl.GetTransPos().y, gl.GetTransPos().z));
    }


    //transform.y ��0��菬�����i���������j�ꍇ�J�������~�߂�
    if (gl.GetTransPos().y < FALL_MAX)
    {
        Camera::SetPosition(XMFLOAT3(gl.GetTransPos().x, CAMERA_FALL_MAX, CAMERA_SET_POS));
        Camera::SetTarget(XMFLOAT3(gl.GetTransPos().x, CAMERA_FALL_MAX, gl.GetTransPos().z));
    }
}

//���̃X�e�[�W���A�����b�N
void StageScene::NextStageUnlock( int SelectStage )
{
    switch (SelectStage)
    {
    case STAGE_NUMBER_1: gl.setState(Global::stage2.UnLock); break;
    case STAGE_NUMBER_2: gl.setState(Global::stage3.UnLock); break;
    case STAGE_NUMBER_3: break;
    }
}

//�S�[�����o�p
void StageScene::Timer()
{
    GoalStaging* pGoalStaging_ = (GoalStaging*)FindObject("GoalStaging");

    //true�̎�
    if (pGoalStaging_->timer_)
    {
        //���̃X�e�[�W���A�����b�N�����A�X�e�[�W�I���֑J��
        NextStageUnlock(Global::SelectStage);
        pGoalStaging_->timer_ = false;
        SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
        pSceneManager->ChangeScene(SCENE_ID_SELECT);
    }
}

//�e�X�e�[�W�̃R�C������肵�����ǂ����̔���
void StageScene::GetCoinJudge()
{
    Global::GetCoin = false;

    //���݂̃X�e�[�W�̃R�C�����擾���Ă��邩
    switch (Global::SelectStage)
    {
    case STAGE_NUMBER_1:
        //�N���A�t���O��true�Ȃ�
        if (gl.getState(Global::stage1.Clear)) {
            Global::GetCoin = true;
            gl.setState(Global::stage1.GetCoin);
        }
        else
        {
            Global::GetCoin = false;
            gl.unsetState(Global::stage1.GetCoin);
        }
        break;
    case STAGE_NUMBER_2:
        if (gl.getState(Global::stage2.Clear)) {
            Global::GetCoin = true;
            gl.setState(Global::stage2.GetCoin);
        }
        else
        {
            Global::GetCoin = false;
            gl.unsetState(Global::stage2.GetCoin);
        }
        break;
    case STAGE_NUMBER_3:
        if (gl.getState(Global::stage3.Clear)) {
            Global::GetCoin = true;
            gl.setState(Global::stage3.GetCoin);
        }
        else
        {
            Global::GetCoin = false;
            gl.unsetState(Global::stage3.GetCoin);
        }
        break;
    }
}
