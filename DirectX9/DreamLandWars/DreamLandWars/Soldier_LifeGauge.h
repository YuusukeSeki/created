//*****************************************************************************
//
//		Life Gauge of Soldier
//													Autohr : Yusuke Seki
//*****************************************************************************
#ifndef _SOLDIER_LIFEGAUGE_H_
#define _SOLDIER_LIFEGAUGE_H_

#include "main.h"
#include "ObjectModel.h"

class Hold;
class LifeGauge;
class Icon;


class Castle : public ObjectModel
{
public:
	//----- �R���X�g���N�^ / �f�X�g���N�^ -----
	Castle();
	Castle(Object::TYPE type);
	virtual ~Castle();

	//----- ��{�I�Ȋ֐� -----
	static Castle* Create(const char* FileName, Object::GROUP group);
	virtual void Init(const char* FileName, Object::GROUP group);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

	// �_���[�W��^����
	// breakPower : �^����_���[�W
	void BrowCastle(float breakPower);

	// �����͈͂Ƃ̓����蔻��
	// position : �ΏۃL���X�g�̈ʒu
	// �y�Ԃ�l�z	true  : �����
	//				false : ����Ȃ�
	bool CollisionBrowRange(D3DXVECTOR3& position);


private:
	float m_browRange;	// �����͈�
	Hold* m_pHold;	// �����͈͂�GUI

	int m_frameCounter;	// ���m�����p�t���[���J�E���^�[

	D3DXVECTOR3 vector_LEFT, vector_RIGHT;	// ���m�������̎w�����̏����O����

};

#endif

