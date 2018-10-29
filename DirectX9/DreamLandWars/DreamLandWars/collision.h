//*****************************************************************************
//
//		�����蔻��
//													Autohr : Yusuke Seki
//*****************************************************************************
#ifndef _COLLISION_H_
#define _COLLISION_H_

#include "main.h"


class Collision_History
{
public:
	Collision_History() { m_pNext = nullptr; }
	void SetNextPointer(void* pNext) { m_pNext = (Collision_History*)pNext; }
	void* GetNextPointer() { return m_pNext; }

private:
	Collision_History * m_pNext;

};



// �x�N�g���̒����̂Q����v�Z
float VectorLength(D3DXVECTOR3& vec);

// 2�_�Ԃ̋�����2����v�Z
float Distance3D(D3DXVECTOR3& p1, D3DXVECTOR3& p2);

 // �J�[�\�����W��3D���W�ɕϊ�
D3DXVECTOR3* transScreenToWorld(D3DXVECTOR3* out, IDirect3DDevice9* pDev, int sx, int sy, float z, D3DXMATRIX* view, D3DXMATRIX* proj);

// �y�����蔻��z���Ɩ������C
bool CalcSphereRayCollision(float r, D3DXVECTOR3* center, D3DXVECTOR3* s, D3DXVECTOR3* v, D3DXVECTOR3* pOut_colli, float* pOut_t);

// �y�����蔻��z�_�Ɛ���
bool Collision_PointToSegment(D3DXVECTOR3& pointPosition, D3DXVECTOR3& segmentPosition, D3DXVECTOR3& segmentVector);

// �y�����蔻��z�����Ɛ���
bool Collision_SegmentToSegment(D3DXVECTOR3& posA, float radiusA, D3DXVECTOR3& posB, float radiusB);

// �y�����蔻��z�����ƕ���
bool Collision_SegmentToPlane(D3DXVECTOR3& posA, float radiusA, D3DXVECTOR3& posB, float radiusB);

// �y�����蔻��z���Ƌ�
bool Collision_SphereToSphere(D3DXVECTOR3 posA, float radiusA, D3DXVECTOR3 posB, float radiusB);

// �y�����蔻��z���Ɠ�
bool Collision_CapsuleToCapsule(D3DXVECTOR3& posA, float radiusA, D3DXVECTOR3& posB, float radiusB);

// �y�����蔻��z�����Ɣ|���S��
bool Collision_SegmentToSquare(D3DXVECTOR3& startPos, D3DXVECTOR3& endPos, D3DXVECTOR3& cenPos, D3DXVECTOR3& halfSize);

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
bool CalcParticlePlaneCollision(FLOAT r, D3DXVECTOR3 *pPre_pos, D3DXVECTOR3 *pPos, D3DXVECTOR3 *pNormal, D3DXVECTOR3 *pPlane_pos, FLOAT *t, D3DXVECTOR3 *pOut_colli);

///////////////////////////////////////////
// �ǂ���x�N�g��
// out : ���K���ǂ���x�N�g���i�߂�l�j
// front : �i�s�x�N�g��
// normal: �Փ˓_�ł̖@���x�N�g��
D3DXVECTOR3* calcWallScratchVector(D3DXVECTOR3* out, const D3DXVECTOR3& front, const D3DXVECTOR3& normal);

/////////////////////////////////////////
// ���˃x�N�g��
// out : ���K�����˃x�N�g���i�߂�l�j
// front : �i�s�x�N�g��
// normal: �Փ˓_�ł̖@���x�N�g��
D3DXVECTOR3* calcReflectVector(D3DXVECTOR3* out, const D3DXVECTOR3& front, const D3DXVECTOR3& normal);

//���_ABC�ō��ꂽ�|���S������@�����v�Z����B
D3DXVECTOR3* CreatePolygonNormal(D3DXVECTOR3* out, D3DXVECTOR3& posA, D3DXVECTOR3& posB, D3DXVECTOR3& posC);

#endif
