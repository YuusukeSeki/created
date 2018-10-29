//*****************************************************************************
//
//		���m
//												Autohr : Yusuke Seki
//*****************************************************************************
#ifndef _SOLDIER_H_
#define _SOLDIER_H_

#include "main.h"
#include "ObjectModel.h"

class Commander;
class Tower;
class Castle;
class Player;


class Soldier : public ObjectModel
{
public:	//----- �񋓌^�̒�` -----
	enum POSTURE {	// �̐�
		POSTURE_BONE,		// ���܂�Ă����i���G�j
		POSTURE_STAND,		// �����~�܂�
		POSTURE_RUN,		// ����
		POSTURE_BACKWORD,	// �̂�����
		POSTURE_TUMBLE,		// �|���
		POSTURE_RISE,		// �N���オ��
		POSTURE_DEATH,		// ����
		POSTURE_BULLETSHOT,	// �ˌ��U��
		POSTURE_ASSAULT,	// �ˌ��i���A��ցj
	};

public:	// ���������E���m��ݒ�A�擾����
	// ���m�̓��I��������
	static Soldier* SetSoldier(D3DXVECTOR3& position, D3DXVECTOR3& front, const char* modelPass, Object::GROUP group, Commander* pCommnader);

	// ���̕��m��ݒ肷��
	void SetNextSoldier(Soldier* pSoldier) { m_pNextSoldier = pSoldier; }

	// �O�̕��m��ݒ肷��
	void SetPrevSoldier(Soldier* pSoldier) { m_pPrevSoldier = pSoldier; }

	// ���̕��m���擾����
	Soldier* GetNextSoldier() { return m_pNextSoldier; }

	// �O�̕��m���擾����
	Soldier* GetPrevSoldier() { return m_pPrevSoldier; }


public:
	Soldier();
	~Soldier();
	static Soldier* Create(D3DXVECTOR3& position, const char* modelPass);
	void Init(D3DXVECTOR3& position, const char* modelPass);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// ����
	// vecZ�F�i�ޕ���
	void Run(D3DXVECTOR3& vecZ, float velocity);

	// �g�p���t���O��Ԃ�
	// �Ԃ�l�F true  - �g�p��
	//			false - ���g�p
	bool GetInstance() { return m_bInstance; }

	// �U�������
	void Attack(float damage, D3DXVECTOR3& vector, float accelerate, Player* pPlayer);

	// �_���[�W���󂯂�
	// damage�F�^����_���[�W��
	// �Ԃ�l�F true  ���񂾂�
	//			false �����Ă��
	bool Damage(float damage);

	// �񕜂���
	// heal�F�^����񕜐�
	void Heal(float heal) { m_life = m_life + heal > m_maxLife ? m_maxLife : m_life + heal; }

	// �ڕW���_��ݒ肷��
	void SetTargetBasePoint(ObjectModel* pTarget);

	// �G�ɍU��������
	void ShotBullet();

	// ���̕��m���E��
	void KillMe();

	// ID���擾
	// �Ԃ�l�F���m�ŗL��ID
	int GetID() { return m_ID; }


private:
	// ���m�̐ݒ菈��
	void SetSoldier_private(D3DXVECTOR3& position, D3DXVECTOR3& front, Object::GROUP group, Commander* pCommnader);

	// ���G�i���j
	// �Ԃ�l�F Tower�̃|�C���^  ����
	//			nullptr          ���Ȃ���
	Tower* SearchTower();

	// ���G�i��j
	// �Ԃ�l�F Castle�̃|�C���^  ����
	//			nullptr          ���Ȃ���
	Castle* SearchCastle();

	// ���G�i���j�b�g�j
	// �Ԃ�l�F true  ����
	//			false ���Ȃ���
	bool SearchEnemy();

	// ���G�i���m�j
	// �Ԃ�l�F true  ����
	//			false ���Ȃ���
	bool SearchEnemy_Soldier();

	// ���G�i�L���X�g�j
	// �Ԃ�l�F true  ����
	//			false ���Ȃ���
	bool SearchEnemy_Cast();

	// ��ԋ߂��G��T��
	// �Ԃ�l�F	��ԋ߂��G�̃|�C���^
	ObjectModel* SearchNearEnemy();

	// ���_�Ƃ̓����蔻��
	bool CollisionBasePoint();

	// ���_������
	void BreakBasePoint();


	//----- �f�[�^ -----
	Commander* m_pParent;	// �����̎w����

	Soldier* m_pNextSoldier;	// ���̕��m
	Soldier* m_pPrevSoldier;	// �O�̕��m

	bool m_bInstance;	// �g�p���t���O

	float m_searchRange;	// ���G�͈�

	float m_maxLife;	// �̗͂̍ő�l
	float m_life;		// ���݂̗̑�

	float m_breakPower;					// ���_�j���
	ObjectModel* m_pAssaultBasePoint;	// �����������_

	static int m_cntID;	// ��ӂ�ID����U��
	int m_ID;			// ��ӂ�ID����U��

	

};


#endif
