#include "BoxCollider.h"
#include "SphereCollider.h"
#include "Model.h"


//コンストラクタ（当たり判定の作成）
//引数：basePos	当たり判定の中心位置（ゲームオブジェクトの原点から見た位置）
//引数：size	当たり判定のサイズ
BoxCollider::BoxCollider(XMFLOAT3 basePos, XMFLOAT3 size)
{
	center_ = basePos;
	size_ = size;
	type_ = COLLIDER_BOX;

	//リリース時は判定枠は表示しない
#ifdef _DEBUG
	//テスト表示用判定枠
	hDebugModel_ = Model::Load("DebugCollision/boxCollider.fbx");
#endif
}

//点との当たり判定
bool BoxCollider::IsHitBoxVsPoint(XMFLOAT3 position)
{
	if (position.x >= center_.x - size_.x / 2 &&
		position.x <= center_.x + size_.x / 2 &&
		position.y >= center_.y - size_.y / 2 &&
		position.y <= center_.y + size_.y / 2 &&
		position.z >= center_.x - size_.z / 2 &&
		position.z <= center_.x + size_.z / 2)
	{
		return true;
	}
	return false;
}

//接触判定
//引数：target	相手の当たり判定
//戻値：接触してればtrue
bool BoxCollider::IsHit(Collider* target)
{
	if (target->type_ == COLLIDER_BOX)
		return IsHitBoxVsBox((BoxCollider*)target, this);
	else
		return IsHitBoxVsCircle(this, (SphereCollider*)target);
}