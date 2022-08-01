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
    Game::ItemImagePos = ITEMIMAGE_POSITION_STAGE;      //�R�C���̈ʒu���X�e�[�W�p�ɐݒ�
    Game::ItemImageSca = ITEMIMAGE_SCALE_STAGE;         //�R�C���̑傫�����X�e�[�W�p�ɐݒ�
    Game::GameOver = false;                             //GameOver�ł͂Ȃ�
    Game::IsGameOver = false;                           //GameOver�ł͂Ȃ�
    GetCoinJudge();                                       //�R�C�����蔻��

    //�X�e�[�W
    Stage* pStage_ = Instantiate<Stage>(this);
    pStage_->Load(Game::SelectStage);

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
    CameraMove(game.GetCameraStart().x, game.GetCameraGoal().x);

    //�Q�[���I�[�o�[
    GameOverSEL();

    //�ꎞ��~
    PauseSEL();

    //�S�[�����o�p
    Timer();

    //�擾���Ă��烊�X�^�[�g�̏ꍇ�R�C�����ĕ\������
    //�擾���Ă�����͎̂擾���ĂȂ��l�ɂ���
    if (Game::GetCoin && Game::ItemReDraw)
    {
        Instantiate<ItemModel>(this);
        Game::ItemReDraw = false;
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

    if (Game::IsGameOver)
    {
        //GameOver�\��
        Instantiate<GameOver>(this);
        Game::IsGameOver = false;

    }

    //GameOver�ɂȂ�����
    if (Game::GameOver)
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
    if (!Game::Pause) {
        if (Input::IsKeyDown(DIK_ESCAPE))
        {
            Instantiate<Pause>(this);			//�ꎞ��~
            Game::Pause = true;
        }
    }

    //�ꎞ��~���ꂽ�Ƃ�
    if (Game::Pause)
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
            Game::Pause = false;

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
    if (game.GetTransPos().x < start)
    {
        Camera::SetPosition(XMFLOAT3(game.GetCameraStart().x, game.GetTransPos().y, CAMERA_SET_POS));
        Camera::SetTarget(XMFLOAT3(game.GetCameraStart().x, game.GetTransPos().y, game.GetTransPos().z));
    }
    //�S�[���t��
    else if (game.GetTransPos().x >= goal)
    {
        Camera::SetPosition(XMFLOAT3(game.GetCameraGoal().x, game.GetTransPos().y, CAMERA_SET_POS));
        Camera::SetTarget(XMFLOAT3(game.GetCameraGoal().x, game.GetTransPos().y, game.GetTransPos().z));
    }
    //�����łȂ��ꍇPlayer�ɒǏ]����
    else
    {
        Camera::SetPosition(XMFLOAT3(game.GetTransPos().x, game.GetTransPos().y, CAMERA_SET_POS));
        Camera::SetTarget(XMFLOAT3(game.GetTransPos().x, game.GetTransPos().y, game.GetTransPos().z));
    }


    //transform.y ��0��菬�����i���������j�ꍇ�J�������~�߂�
    if (game.GetTransPos().y < FALL_MAX)
    {
        Camera::SetPosition(XMFLOAT3(game.GetTransPos().x, CAMERA_FALL_MAX, CAMERA_SET_POS));
        Camera::SetTarget(XMFLOAT3(game.GetTransPos().x, CAMERA_FALL_MAX, game.GetTransPos().z));
    }
}

//���̃X�e�[�W���A�����b�N
void StageScene::NextStageUnlock( int SelectStage )
{
    switch (SelectStage)
    {
    case STAGE_NUMBER_1: game.setState(Game::stage2.UnLock); break;
    case STAGE_NUMBER_2: game.setState(Game::stage3.UnLock); break;
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
        NextStageUnlock(Game::SelectStage);
        pGoalStaging_->timer_ = false;
        SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
        pSceneManager->ChangeScene(SCENE_ID_SELECT);
    }
}

//�e�X�e�[�W�̃R�C������肵�����ǂ����̔���
void StageScene::GetCoinJudge()
{
    Game::GetCoin = false;

    //���݂̃X�e�[�W�̃R�C�����擾���Ă��邩
    switch (Game::SelectStage)
    {
    case STAGE_NUMBER_1:
        //�N���A�t���O��true�Ȃ�
        if (game.getState(Game::stage1.Clear)) {
            Game::GetCoin = true;
            game.setState(Game::stage1.GetCoin);
        }
        else
        {
            Game::GetCoin = false;
            game.unsetState(Game::stage1.GetCoin);
        }
        break;
    case STAGE_NUMBER_2:
        if (game.getState(Game::stage2.Clear)) {
            Game::GetCoin = true;
            game.setState(Game::stage2.GetCoin);
        }
        else
        {
            Game::GetCoin = false;
            game.unsetState(Game::stage2.GetCoin);
        }
        break;
    case STAGE_NUMBER_3:
        if (game.getState(Game::stage3.Clear)) {
            Game::GetCoin = true;
            game.setState(Game::stage3.GetCoin);
        }
        else
        {
            Game::GetCoin = false;
            game.unsetState(Game::stage3.GetCoin);
        }
        break;
    }
}
