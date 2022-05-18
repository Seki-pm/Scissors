#pragma once
#include <vector>
#include <DirectXMath.h>
#include "Global.h"

using namespace DirectX;
using namespace std;

//多角形の当たり判定
class PolygonCollider
{
	//多角形の各頂点を入れる配列
	//何角形でもいいが、凸多角形じゃないとダメ
	vector<XMVECTOR> points_;

	int RepelNumber = -1;
	int SinkNumber = -1;

public:

	//多角形の頂点の位置を追加
	//※凸多角形じゃないとダメ
	//※時計回りに設定していくこと
	//引数：x,y	追加したい位置
	void AddPoint(float x, float z);


	//多角形と点の当たり判定
	//引数：point　点の位置
	//戻値：ぶつかってたらtrue
	bool Hit(XMFLOAT3 point, XMMATRIX worldMatrix = XMMatrixIdentity());


	//線分と多角形の「交点」と、当たってる面の「法線」を求める
	//（「ハサミの中心から刃先までの線分」と地面との交点、及びその地面の法線を求めるのに使用）
	//引数：線分の端の位置（ハサミの中心）
	//引数：線分のもう一端の位置（ハサミの先端）
	//引数：法線を入れる変数のアドレス
	//引数：交点を入れる変数のアドレス
	//戻値：そもそも交差してるかどうか
	bool GetNormal(XMFLOAT3 p1, XMFLOAT3 p2, XMFLOAT3* normal, XMFLOAT3* hitPoint);

	//ステージと刃先との当たり判定
	//引数：target  当たっている面の三角形
	//戻値：ぶつかっていたらtrue
	bool Hit(PolygonCollider* target, XMMATRIX worldMatrix);

	//ギミック床を配列に入れる
	//引数：地面番号を入れる
	void AddRepel(int num);
	void AddSink(int num);

	//はじく床との判定＆送る
	void SetRepel(int search);
	int GetRepel();

	//沈む床との判定＆送る
	void SetSink(int search);
	int GetSink();
};

