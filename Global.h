#pragma once
#include "Engine/Direct3D.h"
#include <vector>
using namespace std;

//グローバル変数（シーンをまたいで有効）
class Global
{
private:
	//ハサミの位置を入れる変数
	static XMFLOAT3 Position_;

	//カメラのStart & Goal
	static XMFLOAT2 Camera_Start;
	static XMFLOAT2 Camera_Goal;

public:

	//StageSelectSceneの選択されている番号
	static int SelectStage;

	//コインの表示位置・大きさ
	static XMFLOAT3 ItemModelPos;  //モデル位置
	static XMFLOAT3 ItemImagePos;  //画像位置
	static XMFLOAT3 ItemImageSca;  //画像サイズ

	//StageUnlock変数
	static bool Unlock2;
	static bool Unlock3;

	//Playerの最大HP
	static int MAXHP;           //最大HP

	//Globalのフラグ
	static bool GetCoin;        //コインのGetしたか
	static bool GetCoin_1;      //Stage1のコインをGet
	static bool GetCoin_2;      //Stage2のコインをGet
	static bool GetCoin_3;      //Stage3のコインをGet
	static bool GameOver;       //GameOverの処理
	static bool IsGameOver;     //GameOverを一回だけ表示
	static bool Pause;          //Pause用
	static bool ItemReDraw;     //アイテムの再表示

	//地面ギミック用動的配列
	static vector<int> Repel_;
	static vector<int> Sink_;

	//ハサミの位置を設定&送る
	void SetTransPos(XMFLOAT3 position);
	XMFLOAT3 GetTransPos();

	//カメラのスタートとゴール位置を設定（ X , Y ）
	void SetCameraStart(float startX, float startY);
    void SetCameraGoal(float goalX, float goalY);

	//カメラのスタートとゴール位置を取得（ X , Y ）
	XMFLOAT2 GetCameraStart();
	XMFLOAT2 GetCameraGoal();
};
