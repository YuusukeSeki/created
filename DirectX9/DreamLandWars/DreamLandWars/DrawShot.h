//*****************************************************************************
//	
//		�h���[�V���b�g
//													Autohr : Yusuke Seki
//*****************************************************************************
#ifndef _DRAWSHOT_H_
#define _DRAWSHOT_H_

#include "main.h"
#include "Bullet3D.h"
#include "collision.h"

class Player;
class DrawLine;
class Camera;
class CollisionCharacter;


class DrawShot : public Bullet3D
{
public:
	//----- �R���X�g���N�^ / �f�X�g���N�^ -----
	DrawShot() {}
	DrawShot(Object::TYPE type);
	virtual ~DrawShot();

	//----- ��{�I�Ȋ֐� -----
	static DrawShot* Create(D3DXVECTOR3& position, D3DXVECTOR3& size);
	void Init(D3DXVECTOR3& position, D3DXVECTOR3& size);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// DS�̓��I��������
	// pStartPoint�F�J�n�_�̃|�C���^
	static void SetDrawShot(DrawLine* pStartPoint);

	//----- �f�[�^��Ԃ����� -----


private:
	// DS�̐ݒ�
	// pStartPoint�F�J�n�_�̃|�C���^
	void SetDrawShot_private(DrawLine* pStartPoint);

	// �G���m�Ƃ̓����蔻��
	void CollisionSoldier();

	// ���Ƃ̓����蔻��
	// �Ԃ�l�F	true  ��������
	//			false �������ĂȂ�
	bool Collision_Tower();

	// �������������������
	void ClearCollisionID();


	//----- �f�[�^ -----
	DrawLine*   m_pMoveWay;			// �ړ��o�H
	D3DXVECTOR3 m_vecPrevToNext;	// �o�H���̒P�ʃx�N�g��
	Camera*     m_pCamera;			// �J����
	Player*     m_pPlayer;			// �e�v���C���[

	//CollisionCharacter *m_pCollisionCharacter;	// ���������L�����N�^�̃|�C���^

	static const int NUM_COLLISION_ID_SOLDIER = 64;			// �ő�̕��m�����蔻�萔
	static const int CLEAR_ID = -1;							// CLEAR�l
	int m_CollisionID_Soldier[NUM_COLLISION_ID_SOLDIER];	// �����������m�̃o�b�t�@
	int m_cntCollisionSoldier;								// �����������m��

};


#endif

