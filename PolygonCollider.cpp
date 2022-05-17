#include "PolygonCollider.h"
#include "Global.h"


//多角形の頂点の位置を追加
// ○角形かが分かる ==　points_.size() 
void PolygonCollider::AddPoint(float x, float y)
{
	points_.push_back(XMVectorSet(x, y, 0, 0));
}


//多角形と点の当たり判定
//
//「四角形ABCD」と「点Ｐ」の当たり判定を考える
//（ABCDは時計回りに配置されているものとする）
//
//点が四角形内部にあるなら
//点Pは、線ABの右側にあり、線BCの右側にあり、線CDの右側にあり、線DAの右側にあるはず
// 
//右か左かは外積を求めればわかる
//PがABの右にあるかどうかはABとAPの外積を求めればいい（結果のZがマイナスだったら右にある）
bool PolygonCollider::Hit(XMFLOAT3 point, XMMATRIX worldMatrix)
{
	//ｚ方向は考えない
	point.z = 0;

	//点の数（＝辺の数）ループ
	for (int i = 0; i < points_.size(); i++)
	{
		// 2頂点(1辺)の位置を求める
		XMVECTOR v1 = points_[i];
		XMVECTOR v2 = points_[(i + 1) % points_.size()];

		// ワールド行列をかける
		v1 = XMVector3TransformCoord(v1, worldMatrix);
		v2 = XMVector3TransformCoord(v2, worldMatrix);

		// point = 点の位置
		XMVECTOR p = XMLoadFloat3(&point);

		// 二つのベクトルから外積を求める
		XMVECTOR edge1 = v2 - v1;        // 多角形の辺のベクトル(時計回り)
		XMVECTOR edge2 = p - v1;         // 当たった点までのベクトル
		XMVECTOR cross = XMVector3Cross(edge1, edge2);


		//点が辺の左にあるならぶつかってない
		// crossがマイナスならぶつかっている
		if (XMVectorGetZ(cross) > 0)
		{
			return false;
		}
	}

	//全ての辺の右側にあった＝ぶつかっている
	return true;
}

// 線分と地形の「交点」と地形からの「法線」を求める
bool PolygonCollider::GetNormal(XMFLOAT3 point1, XMFLOAT3 point2, XMFLOAT3* normal, XMFLOAT3* hitPoint)
{
	// z方向は考えない
	point1.z = 0;
	point2.z = 0;

	//点の数（＝辺の数）ループ
	for (int i = 0; i < points_.size(); i++)
	{
		// 地形側の頂点の位置
		XMVECTOR v1 = points_[i];
		XMVECTOR v2 = points_[(i + 1) % points_.size()];

		// ハサミ側の真ん中と刃先の位置
		XMVECTOR v3 = XMLoadFloat3(&point1);
		XMVECTOR v4 = XMLoadFloat3(&point2);



		//まず直線 v1-v2 に対して、点v3とv4が左右どっちにあるか
		XMVECTOR cross1 = XMVector3Cross(v2 - v1, v3 - v1);     
		XMVECTOR cross2 = XMVector3Cross(v2 - v1, v4 - v1);     

		// 交差の有無
		if ((XMVectorGetZ(cross1) > 0 && XMVectorGetZ(cross2) > 0)			//どっちも左 
			|| (XMVectorGetZ(cross1) < 0 && XMVectorGetZ(cross2) < 0))		//またはどっちも右
		{
			//交差してない
			continue;
		}


		//今度は直線 v3-v4 に対して、点v1とv2が左右どっちにあるか
		cross1 = XMVector3Cross(v4 - v3, v1 - v3);
		cross2 = XMVector3Cross(v4 - v3, v2 - v3);

		// 交差の有無
		if ((XMVectorGetZ(cross1) > 0 && XMVectorGetZ(cross2) > 0)			//どっちも左 
			|| (XMVectorGetZ(cross1) < 0 && XMVectorGetZ(cross2) < 0))		//またはどっちも右
		{
			//交差してない
			continue;
		}

		//---------------ここまで来たら交差している!!-------------------

		//交差してるのが分かったので、交点を求める
		//https://qiita.com/kaityo256/items/988bf94bf7b674b8bfdc
		float det = (XMVectorGetX(v1) - XMVectorGetX(v2)) * (XMVectorGetY(v4) - XMVectorGetY(v3)) - (XMVectorGetX(v4) - XMVectorGetX(v3)) * (XMVectorGetY(v1) - XMVectorGetY(v2));
		float t = ((XMVectorGetY(v4) - XMVectorGetY(v3)) * (XMVectorGetX(v4) - XMVectorGetX(v2)) + (XMVectorGetX(v3) - XMVectorGetX(v4)) * (XMVectorGetY(v4) - XMVectorGetY(v2))) / det;
		hitPoint->x = t * XMVectorGetX(v1) + (1.0 - t) * XMVectorGetX(v2);
		hitPoint->y = t * XMVectorGetY(v1) + (1.0 - t) * XMVectorGetY(v2);
		hitPoint->z = 0;

		//法線を求める
		//こっち向きのベクトルとの外積を求めれば法線になる
		XMVECTOR vecNormal = XMVector3Cross(v2 - v1, XMVectorSet(0, 0, -1, 0));
		vecNormal = XMVector3Normalize(vecNormal);
		XMStoreFloat3(normal, vecNormal);

		return true;
	}

	return false;
}

//ステージとの当たり判定
bool PolygonCollider::Hit(PolygonCollider* target, XMMATRIX worldMatrix)
{
	//targetの頂点の数（＝辺の数）ループ
	for (int i = 0; i < target->points_.size(); i++)
	{
		XMVECTOR vP = XMVector3TransformCoord(target->points_[i], worldMatrix);
		XMFLOAT3 fP;
		XMStoreFloat3(&fP, vP);
		if (Hit(fP))
		{
			return true;
		}
	}

	//頂点の数ループ
	for (int i = 0; i < points_.size(); i++)
	{
		XMFLOAT3 fP;
		XMStoreFloat3(&fP, points_[i]);

		if (target->Hit(fP, worldMatrix))
		{
			return true;
		}
	}

	return false;
}

//はじく床を追加
void PolygonCollider::AddRepel(int num)
{
	Global::Repel_.push_back(num - 1);
}

//はじく床との判定を行う
void PolygonCollider::SetRepelCheck(int search)
{
	for (int i = 0; i < Global::Repel_.size(); i++)
	{
		if (Global::Repel_[i] == search)
		{
			number = search;
		}	
	}
}

//はじく床の番号を送る
int PolygonCollider::GetRepelCheck()
{
	return number;
}
