//*****************************************************************************
//
//		�w����
//													Author : Yusuke Seki
//*****************************************************************************
#ifndef _COMMANDER_H_
#define _COMMANDER_H_

#include "main.h"
#include "Object.h"

class Soldier;
class ObjectModel;


class Commander : public Object
{
public:
	Commander();
	~Commander();
	
	static Commander* CreateBuffer();
	void Init();
	void Uninit();
	void Update();
	void Draw() {}


	// �w�����̓��I��������
	// positon �F�����ʒu
	// �Ԃ�l  �F�������ꂽ�w�����̃|�C���^
	static Commander* SetCommander(D3DXVECTOR3& position, D3DXVECTOR3& front, Object::GROUP group);
	//static Commander* SetCommander(D3DXVECTOR3& position, D3DXVECTOR3& front, Object::GROUP group, D3DXVECTOR3 targetPosition);

	// �Ԃ�l�F	true  �g�p��
	//			false ���g�p
	bool GetInstance() { return m_bInstance; }

	// �w�����̕��m����G�����񍐂��󂯎��
	void ReceiveReport_SearchEnemy() { m_bSearchEnemy = true; }

	// �w�����̕��m���玀�S�񍐂��󂯎��
	// pSoldier�F���񂾕��m
	void ReceiveReport_Death(Soldier* pSoldier);

	// �����������Ă������Ԃ�
	// �Ԃ�l�F����
	D3DXVECTOR3& GetFront() { return m_front; }

	// ���񂵂Ă��邩�ǂ�����Ԃ�
	// �Ԃ�l�F	true  ���񂵂Ă���
	//			false ���񂵂Ă��Ȃ�
	bool GetFormLine() { return m_bFormLine; }

	// �w�����̕��m���狒�_�����񍐂��󂯎��
	// pTarget�F���������_
	void ReceiveReport_SearchBasePoint(ObjectModel* pTarget) { m_pSearchBasePoint = pTarget; }

	// �w�����̕��m���狒�_�j��񍐂��󂯎��
	void ReceiveReport_BreakBasePoint();

private:
	// �w�����̐ݒ菈��
	void SetCommander_private(D3DXVECTOR3& position, D3DXVECTOR3& front, Object::GROUP group);
	//void SetCommander_private(D3DXVECTOR3& position, D3DXVECTOR3& front, Object::GROUP group, D3DXVECTOR3 targetPosition);

	// �w�����̕��m�𐶐�
	void SpawnSoldier();

	// �w�����̕��m�𐮗񂳂���
	void FormLine();

	// �w�����̕��m�ɒe����������
	void ShotBullet();

	// �w�����̕��m��i�܂���
	void SoldierMove();

	// �w�����̕��m�����_�ɓˌ�������
	void AssaultBasePoint();

	// �w�����̕��m�̖ڕW���W��ݒ肷��
	void SetTargetPosition();

	// �w�����̕��m�����񂵂Ă��邩�ǂ�������������
	// �Ԃ�l�F	true  ���񂵂Ă���
	//			false ���񂵂Ă��Ȃ�
	bool CheckFormLine_Mine();

	// �O���̕��m�񂪐��񂵂Ă��邩�ǂ�������������
	// �Ԃ�l�F	true  ���񂵂Ă���
	//			false ���񂵂Ă��Ȃ��A���݂��Ȃ�
	bool CheckFormLine_Others();



	Soldier* m_pSoldier;				// �w�����̕��m�̐擪�A�h���X
	D3DXVECTOR3 m_front;				// �O����
	bool m_bSearchEnemy;				// �G�����t���O
	int  m_restTime;					// ���̎ˌ��܂ł̋x�e����
	bool m_bInstance;					// �g�p���t���O
	float m_radius_ViewAngle;			// ����p�̔��a
	bool  m_bFormLine;					// true �Ő��񂵂Ă���
	float m_velocity;					// �ړ����x
	ObjectModel*  m_pSearchBasePoint;	// ���_�̔����t���O	



};


#endif

