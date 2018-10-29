//*****************************************************************************
//
//		�v���C���[
//												Autohr : Yusuke Seki
//*****************************************************************************
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"
#include "ObjectModel.h"
#include "MainGame.h"

class DrawLine;
class Camera;
class Tower;
class Castle;
class Part;

class Player : public ObjectModel
{
public:
	//----- �񋓌^�̒�` -----
	enum CHARACTER {	// �L�����N�^�[
		CHARACTER_KIBITSU,
	};

	enum POSTURE {	// �̐��i���[�V�����ƕ��p�j
		POSTURE_NONE,		// ����
		POSTURE_RUN,		// ����
		POSTURE_AVOID,		// ������
		POSTURE_EMAVOID,	// �ً}���
		POSTURE_BACKWORD,	// �̂�����
		POSTURE_TUMBLE,		// �|���
		POSTURE_DEATH,		// ����
		POSTURE_REVIVE,		// �����Ԃ�
		POSTURE_STREADY,	// �X�g���[�g����
		POSTURE_DRREADY,	// �h���[����
		POSTURE_STSHOT,		// �X�g���[�g�U��
		POSTURE_DRSHOT,		// �h���[�U��
		POSTURE_BREAK,		// ���_������
	};


public:
	Player() {}
	Player(Object::TYPE type, Player::CHARACTER character);
	virtual ~Player();

	static Player* Create(D3DXVECTOR3& position, Camera* pCamera, const char* modelPass, Player::CHARACTER character);
	void Init(D3DXVECTOR3& position, Camera* pCamera, const char* modelPass);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// ���W�̈ړ�
	void MovePosition(D3DXVECTOR3& movePosition);

	// �̗͂̑���
	void MoveLife(int move);

	// ���m���j�����Z
	void PlusScore_CrushSoldier() { _score_crushSoldier++; }

	// �̐��̐ݒ�
	void SetPosture(Player::POSTURE posture);

	// �̗͂̐ݒ�
	void SetLife(float life);

	Player::CHARACTER GetCharacter() { return m_character; }
	Player::POSTURE GetPosture() { return m_posture; }
	float GetLife() { return m_life; }
	float GetAvDist() { return m_avDist; }
	float GetStraightShotDamage() { return m_straightShotDamage; }
	float GetStraightShotSpeed() { return m_straightShotSpeed; }
	float GetStraightShotRange() { return m_straightShotRange; }
	float GetDrawShotDamage() { return m_drawShotDamage; }
	float GetDrawShotSpeed() { return m_drawShotSpeed; }
	float GetDrawShotRange() { return m_drawShotRange; }
	Camera* GetCamera() { return m_pCamera; }


	void Run(float moveX, float moveZ);		// ����
	void Avoid(float moveX, float moveZ);	// ������
	void EmAvoid(float moveX, float moveZ);	// �ً}���
	void STReady();							// SS����
	void STShot();							// SS�U��
	void DRReady(bool bTrigger);			// DS����
	void DRShot(bool bRelease);				// DS�U��
	void BreakBasePoint();					// ���_������

	int GetScore_CrushSoldier() { return _score_crushSoldier; }	// ���m���j��


	//----- ���̑����X�g�ǂݍ��ݎ��݂̂̐ݒ菈�� -----
	void SetInirtialVelocity(float inirtialVelocity)   { m_InitialVelosity    = inirtialVelocity; }	// �����̐ݒ�
	void SetAcceleration(float acceleration)           { m_Acceleration       = acceleration; }		// �����x�̐ݒ�
	void SetAvoidDiatance(float avoidDistance)         { m_avDist             = avoidDistance; }	// ��������̐ݒ�

	void SetStraightShotDamage(float straightShotDamage) { m_straightShotDamage = straightShotDamage; }	// SS�З͂̐ݒ�
	void SetStraightShotSpeed(float straightShotSpeed) { m_straightShotSpeed  = straightShotSpeed; }	// SS���x�̐ݒ�
	void SetStraightShotRange(float straightShotRange) { m_straightShotRange  = straightShotRange; }	// SS�˒������̐ݒ�

	void SetDrawShotDamage(float drawShotDamege)         { m_drawShotDamage     = drawShotDamege; }	// DS�З͂̐ݒ�
	void SetDrawShotSpeed(float drawShotSpeed)         { m_drawShotSpeed      = drawShotSpeed; }	// DS���x�̐ݒ�
	void SetDrawShotRange(float drawShotRange)         { m_drawShotRange      = drawShotRange; }	// DS�˒������̐ݒ�
	void SetDrawShotLength(float drawShotLength)       { m_drawShotLength     = drawShotLength; }	// DS�`����̍ő�̒����̐ݒ�

	void SetBreakPower(float breakPower)				   { m_breakPower         = breakPower; }		// ���_�����鋭���̐ݒ�

	void SetCooldown_Avoid(int cooldown_Avoid)         { m_cooldown_Avoid     = cooldown_Avoid; }	// �y�d�����Ԃ̐ݒ�z���̐�
	void SetCooldown_EmAvoid(int cooldown_EmAvoid)     { m_cooldown_EmAvoid   = cooldown_EmAvoid; }	// �y�d�����Ԃ̐ݒ�z�ً}���̐�
	void SetCooldown_StShot(int cooldown_StShot)       { m_cooldown_StShot    = cooldown_StShot; }	// �y�d�����Ԃ̐ݒ�zSS�̐�
	void SetCooldown_DrShot(int cooldown_DrShot)       { m_cooldown_DrShot    = cooldown_DrShot; }	// �y�d�����Ԃ̐ݒ�zDS�̐�

	void SetMaxLife(float maxLife)                       { m_maxLife            = maxLife; }			// �y�ő�l�z�̗͂̐ݒ�
	void SetMaxMoveSpeed(float maxMoveSpeed)           { m_maxMoveSpeed       = maxMoveSpeed; }		// �y�ő�l�z�ړ����x�̐ݒ�


private:
	//----- ���\�b�h -----
	void CollisionTower();
	void CollisionCastle();
	void CollisionWall();
	void UpdateInverseMatrix();
	bool CollisionCursor_Player(D3DXVECTOR3* pOut);
	Tower* CollisionCursor_BasePoint();


	//----- �萔 ----
	       const float INIRTIA      = 0.70f;	// ����
	static const int   NUM_DSBUF    = 0xf;		// DS�z��
	static const int   NUM_DRAWLINE = 1;		// �`����z��
	static const int   NON_DRAW     = 10;		// �`����Ƃ��ăJ�E���g���Ȃ�����

	//----- �f�[�^ -----
	Player::CHARACTER m_character;	// ���
	Player::POSTURE m_posture;		// �̐�

	float       m_life;					// ���݂̗̑�
	D3DXVECTOR3 m_movePosition;			// �ړ��ʃo�b�t�@
	float       m_InitialVelosity;		// ����
	float       m_Acceleration;			// �����x
	float       m_avDist;				// �������

	float       m_straightShotDamage;	// SS�̈З�
	float       m_straightShotSpeed;	// SS�̑��x
	float       m_straightShotRange;	// SS�̎˒�

	float       m_drawShotDamage;		// DS�̈З�
	float       m_drawShotSpeed;		// DS�̑��x
	float       m_drawShotRange;		// DS�̎˒�
	float       m_drawShotLength;		// DS�̕`���钷��

	float       m_breakPower;			// ���_�����鋭��

	int         m_cntCooldownFrame;		// �d�����Ԍv���p�J�E���^�[
	int         m_cooldown_Avoid;		// �y�d�����ԁz������
	int         m_cooldown_EmAvoid;		// �y�d�����ԁz�ً}���
	int         m_cooldown_StShot;		// �y�d�����ԁzSS�U��
	int         m_cooldown_DrShot;		// �y�d�����ԁzDS�U��
	float       m_maxLife;				// �y�ő�l�z�̗�
	float       m_maxMoveSpeed;			// �y�ő�l�z���x
	
	DrawLine*   m_pDL_StartPos;	// �`����̎n�_�̃o�b�t�@
	float       m_DL_Length;	// �`����̒����̃o�b�t�@
	D3DXVECTOR3 m_DL_PrePos;	// �`����̑O���W�̃o�b�t�@
	float       m_DL_PreLength;	// �`����̍X�V�O�̒����̃o�b�t�@

	D3DXVECTOR3 m_prePosion;	// �O�t���[���̍��W

	float currentFront, targetFront;	// ���݂̌���, �ڕW�̌���

	// ���z�x�N�g���̐ݒ�p
	Camera* m_pCamera;	// �J����
	D3DXMATRIX m_InverseMatrix;
	
	// score
	int _score_crushSoldier;	// ���m���j��
	
	Part *m_Part[10];

public:
	struct KEY {
		D3DXVECTOR3 Position;
		D3DXVECTOR3 Rotation;
	};

	struct KEY_FRAME {
		int Frame;
		KEY Key[10];
	};

private:
	KEY_FRAME *m_KeyFrame;
	int m_Key;
	int m_Frame;

	void TempInput();

};


#endif
