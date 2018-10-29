//*****************************************************************************
//
//		�`���
//												Autohr	:	Yusuke Seki
//*****************************************************************************
#include "DrawLine.h"
#include "renderer.h"
#include "player.h"
#include "DrawShot.h"


//----- �ÓI�ȃf�[�^�̏����� -----
const float DrawLine::DRAWLINE_HEIGHT = 50.f;	// �`����|���S���̍���


//-----------------------------------------------------------------------------
//	�R���X�g���N�^
//-----------------------------------------------------------------------------
DrawLine::DrawLine(Object::TYPE type) :Object3D(type)
{
	// �f�[�^�̃N���A
	m_type      = DrawLine::TYPE::TYPE_START;	// ���
	m_pNext     = nullptr;						// ���̓_
	m_pTail     = nullptr;						// �����̓_
	m_pPlayer   = nullptr;						// �e�v���C���[
	m_bInstance = false;						// �g�p���t���O

}


//-----------------------------------------------------------------------------
//	�f�X�g���N�^
//-----------------------------------------------------------------------------
DrawLine::~DrawLine()
{
	Uninit();
}


//-----------------------------------------------------------------------------
//	����
//-----------------------------------------------------------------------------
DrawLine* DrawLine::Create(D3DXVECTOR3& position)
{
	DrawLine* pDrawLine = new DrawLine(Object::TYPE::TYPE_3D_DRAWLINE);
	pDrawLine->Init(position);

	return pDrawLine;
}


//-----------------------------------------------------------------------------
//	������
//-----------------------------------------------------------------------------
void DrawLine::Init(D3DXVECTOR3& position)
{
	// �p���f�[�^�̏�����
	Object3D::Init(position, D3DXVECTOR3(5, 0, 5));
	
	// �f�[�^�̏�����
	m_type      = DrawLine::TYPE::TYPE_START;	// ���
	m_pNext     = nullptr;						// ���̓_
	m_pTail     = nullptr;						// �����̓_
	m_pPlayer   = nullptr;						// �e�v���C���[
	m_bInstance = false;						// �g�p���t���O

}


//-----------------------------------------------------------------------------
//	�I��
//-----------------------------------------------------------------------------
void DrawLine::Uninit(void)
{
	// �p���f�[�^�̏I������
	Object3D::Uninit();

}


//-----------------------------------------------------------------------------
//	�X�V
//-----------------------------------------------------------------------------
void DrawLine::Update(void)
{
	// ���g�p�ŏ�������
	if (!m_bInstance) return;

	// ���X�ɓ����ɂȂ�
	//SetColor((255 / ELASE_FRAME) * m_life);
	//m_life = m_life - 1 < 0 ? 0 : m_life - 1;

}


//-----------------------------------------------------------------------------
//	�`��
//-----------------------------------------------------------------------------
void DrawLine::Draw(void)
{
	// ���g�p�ŏ�������
	if (!m_bInstance) return;

	// �`�揈��
	Object3D::Draw();
	
}

//=============================================================================
// �ݒ�
// �n�_�̐ݒ�
DrawLine* DrawLine::SetStartLine(D3DXVECTOR3& position, Player& player)
{
	// ���̎�����T��
	DrawLine* pDrawLine = (DrawLine*)Object::GetLDATA_HEAD(Object::TYPE::TYPE_3D_DRAWLINE);

	// �P������Ă��Ȃ������琶������
	if (pDrawLine == nullptr) {
		// ��������
		pDrawLine = DrawLine::Create(D3DXVECTOR3(0, 0, 0));

		// �ݒ菈��
		pDrawLine->SetStartLine_private(position, player);

		return pDrawLine;
	}

	// ����Ă����疢�g�p�̈��T��
	DrawLine* pCurrent = (DrawLine*)pDrawLine;
	DrawLine* pNext    = (DrawLine*)pDrawLine->GetNextPointer();
	for (;;) {
		// ���g�p�Ȃ�ݒ肵�ďI��
		if (!pCurrent->GetInstance()) {
			pCurrent->SetStartLine_private(position, player);
			return pCurrent;
		}

		// ���g�p�̈悪������Ȃ���΁A�V������������
		if (pNext == nullptr) {
			// ��������
			pNext = DrawLine::Create(D3DXVECTOR3(0, 0, 0));

			// �ݒ菈��
			pNext->SetStartLine_private(position, player);

			return pNext;
		}

		// �|�C���^�����炷
		pCurrent = pNext;
		pNext = (DrawLine*)pCurrent->GetNextPointer();

	}

}

// �o�R�_�̐ݒ�
void DrawLine::SetViaPoint(D3DXVECTOR3& position, DrawLine* pStartPoint)
{
	// �n�_��NULL�`�F�b�N
	if (pStartPoint == nullptr) {
		// �G���[���b�Z�[�W
		_MSGERROR("pStartPoint cannnot be nullptr!!", "void DrawLine::SetViaPoint(D3DXVECTOR3& position, DrawLine* pStartPoint)");

	}


	// ���̎�����T��
	DrawLine* pDrawLine = (DrawLine*)Object::GetLDATA_HEAD(Object::TYPE::TYPE_3D_DRAWLINE);

	// �P������Ă��Ȃ������琶������
	if (pDrawLine == nullptr) {
		// ��������
		pDrawLine = DrawLine::Create(D3DXVECTOR3(0, 0, 0));

		// �ݒ菈��
		pDrawLine->SetViaPoint_private(position, pStartPoint);

		return;
	}

	// ����Ă����疢�g�p�̈��T��
	DrawLine* pCurrent = (DrawLine*)pDrawLine;
	DrawLine* pNext    = (DrawLine*)pDrawLine->GetNextPointer();
	for (;;) {
		// ���g�p�Ȃ�ݒ肵�ďI��
		if (!pCurrent->GetInstance()) {
			pCurrent->SetViaPoint_private(position, pStartPoint);
			break;
		}

		// ���g�p�̈悪������Ȃ���΁A�V������������
		if (pNext == nullptr) {
			// ��������
			pNext = DrawLine::Create(D3DXVECTOR3(0, 0, 0));

			// �ݒ菈��
			pNext->SetViaPoint_private(position, pStartPoint);

			break;
		}

		// �|�C���^�����炷
		pCurrent = pNext;
		pNext = (DrawLine*)pCurrent->GetNextPointer();

	}

}

// DS�̔���
void DrawLine::SetDrawShot(DrawLine* pStartPoint)
{
	// �n�_��NULL�`�F�b�N
	if (pStartPoint == nullptr) {
		// �G���[���b�Z�[�W
		_MSGERROR("pStartPoint cannnot be nullptr!!", "void DrawLine::SetDrawShot(DrawLine* pStartPoint)");
	}

	// DS������
	DrawShot::SetDrawShot(pStartPoint);

}

// �p�����[�^�̃N���A
void DrawLine::ClearParameter()
{
	// �f�[�^�̃N���A
	m_type      = DrawLine::TYPE::TYPE_START;	// ���
	m_pNext     = nullptr;						// ���̓_
	m_pTail     = nullptr;						// �����̓_
	m_bInstance = false;						// �g�p���t���O
	m_pPlayer   = nullptr;						// �e�v���C���[

}

// �f�[�^�̃N���A�F�q�����Ă�̈�S��
void DrawLine::ClearParameter_List(DrawLine* pStartPoint)
{
	// �n�_��NULL�`�F�b�N
	if (pStartPoint == nullptr) {
		// �G���[���b�Z�[�W
		_MSGERROR("pStartPoint cannnot be nullptr!!", "void DrawLine::ClearParameter_List(DrawLine* pStartPoint)");
	}

	// �n�_�Ǝ��̓_�̎擾
	DrawLine* pCurrent = (DrawLine*)pStartPoint;
	DrawLine* pNext    = (DrawLine*)pStartPoint->m_pNext;

	for (;;) {
		// �f�[�^�̃N���A
		pCurrent->ClearParameter();

		// �I�_�Ȃ珈���I��
		if (pNext == nullptr) break;

		// ���̓_�ւ��炷
		pCurrent = pNext;
		pNext    = pCurrent->m_pNext;

	}
}



//=============================================================================
//	private�֐�
// �n�_�̐ݒ�
void DrawLine::SetStartLine_private(D3DXVECTOR3& position, Player& player)
{
	// ��ނ̐ݒ�
	m_type = DrawLine::TYPE::TYPE_START;

	// ���W�̐ݒ�
	SetPosition(position);

	// �����̃|�C���^�ݒ�
	m_pTail = this;

	// �e�v���C���[�̐ݒ�
	m_pPlayer = &player;

	// �g�p���t���OON
	m_bInstance = true;

}

// �o�R�_�̐ݒ�
void DrawLine::SetViaPoint_private(D3DXVECTOR3& position, DrawLine* pStartPoint)
{
	// ��ނ̐ݒ�
	m_type = DrawLine::TYPE::TYPE_VIA;

	// ���W�̐ݒ�
	SetPosition(position);

	// �O�̃|�C���^�Ǝ������q��
	pStartPoint->m_pTail->m_pNext = this;

	// �����̃|�C���^�������ɍX�V
	pStartPoint->m_pTail = this;

	// �e�v���C���[�̐ݒ�
	m_pPlayer = pStartPoint->m_pPlayer;

	// �g�p���t���OON
	m_bInstance = true;

}
