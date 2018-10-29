//*****************************************************************************
//
//		�����蔻��
//												Autohr : Yusuke Seki
//*****************************************************************************
#include "collision.h"
#include "renderer.h"
#include "scene.h"


#define IKD_EPSIRON 0.00001f // �덷



///////////////////////////////////////////////////
// �X�N���[�����W�����[���h���W�֕ϊ�
// out    : ���[���h���W�i�o�́j
// pDev   : �`��f�o�C�X
// sx, xy : �X�N���[�����W
// z      : �X�N���[�����W�̉��z�I��Z�����i0.0�`1.0�j
// view   : �r���[�s��
// proj   : �ˉe�ϊ��s��
// �߂�l : ���[���h���W�i�o�́j
D3DXVECTOR3* transScreenToWorld(D3DXVECTOR3* out, IDirect3DDevice9* pDev, int sx, int sy, float z, D3DXMATRIX* view, D3DXMATRIX* proj)
{
	// �r���[�|�[�g�s����쐬
	D3DXMATRIX vpMat;
	D3DXMatrixIdentity(&vpMat);

	D3DVIEWPORT9 vp;
	pDev->GetViewport(&vp);

	vpMat._11 = (float)vp.Width / 2;
	vpMat._22 = -1.0f * (float)(vp.Height / 2);
	vpMat._33 = (float)vp.MaxZ - vp.MinZ;
	vpMat._41 = (float)(vp.X + vp.Width / 2);
	vpMat._42 = (float)(vp.Y + vp.Height / 2);
	vpMat._43 = vp.MinZ;

	// �X�N���[���ʒu�����[���h��
	out->x = (float)sx;
	out->y = (float)sy;
	out->z = z;

	D3DXMATRIX invMat, inv_proj, inv_view;
	D3DXMatrixInverse(&invMat, 0, &vpMat);
	D3DXMatrixInverse(&inv_proj, 0, proj);
	D3DXMatrixInverse(&inv_view, 0, view);

	invMat *= inv_proj * inv_view;

	return D3DXVec3TransformCoord(out, out, &invMat);

}


///////////////////////////////////////////////////
// ���Ɩ������C�̏Փ˔���
// r          : ���̔��a
// center     : ���̒��S�_
// s          : ���C�̊J�n�_
// v          : ���C�̕����x�N�g��
// pOut_colli : �Փˈʒu
// pOut_t     : �Փˎ����i�o�́j
// �߂�l     : �Փ�(true), ��Փ�(false)
bool CalcSphereRayCollision(float r, D3DXVECTOR3* center, D3DXVECTOR3* s, D3DXVECTOR3* v, D3DXVECTOR3* pOut_colli, float* pOut_t)
{
	D3DXVECTOR3 u = *s - *center;

	float a = D3DXVec3Dot(v, v);
	float b = D3DXVec3Dot(v, &u);
	float c = D3DXVec3Dot(&u, &u) - r * r;

	if (a - IKD_EPSIRON <= 0.0f) {
		// �덷
		return false;
	}

	float isColli = b * b - a * c;
	if (isColli < 0.0f) {
		// �Փ˂��Ȃ�
		return false;
	}

	float t = (-b - sqrtf(b * b - a * c)) / a;

	if (pOut_t) {
		*pOut_t = t;
	}

	if (pOut_colli) {
		*pOut_colli = *s + *v * t;
	}

	// �Փ˂��Ă���I
	return true;
}

///////////////////////////////////////////////////
// ���ʃp�[�e�B�N���Փ˔���E�����E�ʒu�Z�o�֐�
// r : �p�[�e�B�N���̔��a
// pPre_pos : �p�[�e�B�N���̑O�̈ʒu
// pPos : �p�[�e�B�N���̎��̓��B�ʒu
// pNormal : ���ʂ̖@��
// pPlane_pos : ���ʏ��1�_
// pOut_t : �Փˎ��Ԃ��i�[����FLOAT�^�ւ̃|�C���^
// pOut_colli : �p�[�e�B�N���̏Փˈʒu���i�[����D3DXVECTOR�^�ւ̃|�C���^
// �߂�l : �Փ�(true), ��Փ�(false)
bool CalcParticlePlaneCollision(FLOAT r, D3DXVECTOR3 *pPre_pos, D3DXVECTOR3 *pPos, D3DXVECTOR3 *pNormal, D3DXVECTOR3 *pPlane_pos, FLOAT *t, D3DXVECTOR3 *pOut_colli)
{
	D3DXVECTOR3 C0 = *pPre_pos - *pPlane_pos; // ���ʏ�̈�_���猻�݈ʒu�ւ̃x�N�g��
	D3DXVECTOR3 D = *pPos - *pPre_pos; // ���݈ʒu����\��ʒu�܂ł̃x�N�g��
	D3DXVECTOR3 N; // �@��
	D3DXVec3Normalize(&N, pNormal); // �@����W����

									// ���ʂƒ��S�_�̋������Z�o
	FLOAT Dot_C0 = D3DXVec3Dot(&C0, &N);
	FLOAT dist_plane_to_point = (float)fabs(Dot_C0);

	// �i�s�����Ɩ@���̊֌W���`�F�b�N
	FLOAT Dot = D3DXVec3Dot(&D, &N);

	// ���ʂƕ��s�Ɉړ����Ă߂荞��ł���X�y�V�����P�[�X
	if ((IKD_EPSIRON - fabs(Dot) > 0.0f) && (dist_plane_to_point < r)) {
		// �ꐶ�����o���Ȃ��̂ōő厞����Ԃ�
		*t = FLT_MAX;
		// �Փˈʒu�͎d���Ȃ��̂ō��̈ʒu���w��
		*pOut_colli = *pPre_pos;
		return true;
	}

	// �������Ԃ̎Z�o
	*t = (r - Dot_C0) / Dot;

	// �Փˈʒu�̎Z�o
	*pOut_colli = *pPre_pos + (*t) * D;

	// �߂荞��ł�����Փ˂Ƃ��ď����I��
	if (dist_plane_to_point < r)
		return true;

	// �ǂɑ΂��Ĉړ����t�����Ȃ�Փ˂��Ă��Ȃ�
	if (Dot >= 0)
		return false;

	// ���Ԃ�0�`1�̊Ԃɂ���ΏՓ�
	if ((0 <= *t) && (*t <= 1))
		return true;

	return false;
}

///////////////////////////////////////////
// �ǂ���x�N�g��
// out : ���K���ǂ���x�N�g���i�߂�l�j
// front : �i�s�x�N�g��
// normal: �Փ˓_�ł̖@���x�N�g��
D3DXVECTOR3* calcWallScratchVector(D3DXVECTOR3* out, const D3DXVECTOR3& front, const D3DXVECTOR3& normal)
{
	D3DXVECTOR3 normal_n;
	D3DXVec3Normalize(&normal_n, &normal);
	return D3DXVec3Normalize(out, &(front - D3DXVec3Dot(&front, &normal_n) * normal_n));
}

/////////////////////////////////////////
// ���˃x�N�g��
// out : ���K�����˃x�N�g���i�߂�l�j
// front : �i�s�x�N�g��
// normal: �Փ˓_�ł̖@���x�N�g��
D3DXVECTOR3* calcReflectVector(D3DXVECTOR3* out, const D3DXVECTOR3& front, const D3DXVECTOR3& normal)
{
	D3DXVECTOR3 normal_n;
	D3DXVec3Normalize(&normal_n, &normal);
	return D3DXVec3Normalize(out, &(front - 2.0f * D3DXVec3Dot(&front, &normal_n) * normal_n));
}

//���_ABC�ō��ꂽ�|���S������@�����v�Z����B
D3DXVECTOR3* CreatePolygonNormal(D3DXVECTOR3* out, D3DXVECTOR3& posA, D3DXVECTOR3& posB, D3DXVECTOR3& posC)
{
	D3DXVECTOR3 AB(posB - posA);
	D3DXVECTOR3 BC(posC - posB);

	D3DXVec3Cross(out, &AB, &BC);	//AB BC�̊O��
	D3DXVec3Normalize(out, out);	//�P�ʃx�N�g���ɂ���

	return out;
}


//-----------------------------------------------------------------------------
// �x�N�g���̒����̂Q����v�Z
//-----------------------------------------------------------------------------
float VectorLength(D3DXVECTOR3& vec)
{
	return vec.x * vec.x + vec.y * vec.y + vec.z * vec.z;
}

//-----------------------------------------------------------------------------
// 2�_�Ԃ̋����v�Z
//-----------------------------------------------------------------------------
float Distance3D(D3DXVECTOR3& p1, D3DXVECTOR3& p2)
{
	D3DXVECTOR3 sub = D3DXVECTOR3(p1.x - p2.x, p1.y - p2.y, p1.z - p2.z);

	return sub.x * sub.x + sub.y * sub.y + sub.z * sub.z;
}

//=============================================================================
//	�����蔻��
// �_�Ɛ���
bool Collision_PointToSegment(D3DXVECTOR3& pointPosition, D3DXVECTOR3& segmentPosition, D3DXVECTOR3& segmentVector)
{
	return false;
}

// �����Ɛ���
bool Collision_SegmentToSegment(D3DXVECTOR3& posA, float radiusA, D3DXVECTOR3& posB, float radiusB)
{
	return false;

}

// �����ƕ���
bool Collision_SegmentToPlane(D3DXVECTOR3& posA, float radiusA, D3DXVECTOR3& posB, float radiusB)
{
	return false;

}

// ���Ƌ�
bool Collision_SphereToSphere(D3DXVECTOR3 posA, float radiusA, D3DXVECTOR3 posB, float radiusB) {
	if ((posB.x - posA.x) * (posB.x - posA.x) + (posB.y - posA.y) * (posB.y - posA.y) + (posB.z - posA.z) * (posB.z - posA.z)
		<= (radiusA + radiusB) * (radiusA + radiusB)) {
		return true;
	}
	return false;
}

// ���Ɠ�
bool Collision_CapsuleToCapsule(D3DXVECTOR3& posA, float radiusA, D3DXVECTOR3& posB, float radiusB)
{
	return false;

}

// �����Ɣ|���S��
bool Collision_SegmentToSquare(D3DXVECTOR3& startPos, D3DXVECTOR3& endPos, D3DXVECTOR3& cenPos, D3DXVECTOR3& halfSize)
{
	D3DXVECTOR3 vec = endPos - startPos;
	D3DXVec3Normalize(&vec, &vec);

	float d1 = startPos.y - cenPos.y;
	float d2 = cenPos.y   - endPos.y;

	float a = d1 / (d1 + d2);

	D3DXVECTOR3 point = startPos + vec * a;

	D3DXVECTOR3 p0, p1, p2, p3;
	D3DXVECTOR3 v01, v12, v23, v30, v0p, v1p, v2p, v3p;
	D3DXVECTOR3 c0, c1, c2, c3;

	p0 = D3DXVECTOR3(cenPos.x - halfSize.x, cenPos.y + halfSize.y, cenPos.z + halfSize.z);
	p1 = D3DXVECTOR3(cenPos.x + halfSize.x, cenPos.y + halfSize.y, cenPos.z + halfSize.z);
	p2 = D3DXVECTOR3(cenPos.x - halfSize.x, cenPos.y - halfSize.y, cenPos.z - halfSize.z);
	p3 = D3DXVECTOR3(cenPos.x + halfSize.x, cenPos.y - halfSize.y, cenPos.z - halfSize.z);

	v01 = p1 - p0;
	v12 = p2 - p1;
	v23 = p3 - p2;
	v30 = p0 - p3;
	v0p = point - p0;
	v1p = point - p1;
	v2p = point - p2;
	v3p = point - p3;

	D3DXVec3Cross(&c0, &v01, &v0p);
	D3DXVec3Cross(&c1, &v12, &v1p);
	D3DXVec3Cross(&c2, &v23, &v2p);
	D3DXVec3Cross(&c3, &v30, &v3p);

	if (c0 <= 0 && c1 <= 0 && c2 <= 0 && c3 <= 0) return true;

	return false;

}


