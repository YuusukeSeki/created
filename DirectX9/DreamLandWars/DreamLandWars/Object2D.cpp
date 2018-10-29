//*****************************************************************************
//
//		2D�|���S���i���X�g�\���j
//												Autohr : Yusuke Seki
//*****************************************************************************
#include "Object2D.h"
#include "renderer.h"
#include "texture.h"


//-----------------------------------------------------------------------------
// �R���X�g���N�^
//-----------------------------------------------------------------------------
Object2D::Object2D() :Object(Object::TYPE::TYPE_2D)
{
	// �����o�ϐ�������
	m_halfSize = D3DXVECTOR3(0, 0, 0);
	m_color.color = 0xffffffff;
	m_UV_StartPoint = D3DXVECTOR2(0, 0);
	m_UV_Size = D3DXVECTOR2(0, 0);
	m_radius = 0;
	m_angle = 0;
	m_rotate = 0;
	m_pVtxBuff = nullptr;
	m_pTexture = nullptr;
	m_bUpdateVertexBuf = false;
	m_bDraw = true;
}


//-----------------------------------------------------------------------------
// �R���X�g���N�^
//-----------------------------------------------------------------------------
Object2D::Object2D(Object::TYPE type) :Object(type)
{
	// �����o�ϐ�������
	m_halfSize         = D3DXVECTOR3(0, 0, 0);
	m_color.color      = 0xffffffff;
	m_UV_StartPoint    = D3DXVECTOR2(0, 0);
	m_UV_Size          = D3DXVECTOR2(0, 0);
	m_radius           = 0;
	m_angle            = 0;
	m_rotate           = 0;
	m_pVtxBuff         = nullptr;
	m_pTexture         = nullptr;
	m_bUpdateVertexBuf = false;
	m_bDraw            = true;
}


//-----------------------------------------------------------------------------
// �f�X�g���N�^
//-----------------------------------------------------------------------------
Object2D::~Object2D()
{
	// �I������
	Uninit();

}


//-----------------------------------------------------------------------------
// ���̂̐���
//-----------------------------------------------------------------------------
Object2D* Object2D::Create(D3DXVECTOR3& pos, D3DXVECTOR3& size)
{
	// ����
	Object2D* pObject2D = new Object2D(Object::TYPE::TYPE_2D);

	// ������
	pObject2D->Init(pos, size);

	return pObject2D;
}


//-----------------------------------------------------------------------------
// ����������
//-----------------------------------------------------------------------------
void Object2D::Init(D3DXVECTOR3& position, D3DXVECTOR3& size)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();

	// �f�[�^��ݒ�
	Object::SetPosition(position);															// ���W
	m_halfSize         = size * 0.5f;														// �����̑傫��
	m_radius           = sqrtf(m_halfSize.x * m_halfSize.x + m_halfSize.y * m_halfSize.y);	// ���a
	m_angle            = atan2f(size.y, size.x);											// atan
	m_rotate           = 0;																	// ��]��
	m_color.color      = 0xffffffff;														// �F
	m_UV_StartPoint    = D3DXVECTOR2(0, 0);													// UV�J�n�_
	m_UV_Size          = D3DXVECTOR2(1, 1);													// UV�傫��
	m_bUpdateVertexBuf = false;																// true �Œ��_�o�b�t�@�̍X�V����������
	m_bDraw            = true;																// true �ŕ`�揈�����s��

	// ���_�o�b�t�@�̐���
	this->MakeVertexBuf();

}


//-----------------------------------------------------------------------------
// �I������
//-----------------------------------------------------------------------------
void Object2D::Uninit(void)
{
	// ���_�o�b�t�@�̔j��
	if (m_pVtxBuff != nullptr) {
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

}


//-----------------------------------------------------------------------------
// �`�揈��
//-----------------------------------------------------------------------------
void Object2D::Draw(void)
{
	// false �ŕ`�揈�����s��Ȃ�
	if (!m_bDraw) return;

	// true �Œ��_�o�b�t�@�̍X�V�������s��
	if (m_bUpdateVertexBuf) this->UpdateVertexBuf();

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}



//=============================================================================
//	��������
// ���W�̈ړ�
void Object2D::MovePosition(D3DXVECTOR3& movePosition)
{
	// ���W�̈ړ�
	Object::MovePosition(movePosition);

	// ���_�o�b�t�@�̍X�V�t���OON
	m_bUpdateVertexBuf = true;

}

// �傫���̑���
void Object2D::MoveSize(D3DXVECTOR3& moveSize)
{
	// �傫���̑���
	m_halfSize += moveSize * 0.5f;
	m_radius    = sqrtf(m_halfSize.x * m_halfSize.x + m_halfSize.y * m_halfSize.y);	// ���a
	m_angle     = atan2f(m_halfSize.y, m_halfSize.x);								// atan
	
	// ���_�o�b�t�@�̍X�V�t���OON
	m_bUpdateVertexBuf = true;

}

// ��]���̑���
void Object2D::MoveRotate(float moveRotate)
{
	// ��]���̑���
	m_rotate += moveRotate;
	
	// ���_�o�b�t�@�̍X�V�t���OON
	m_bUpdateVertexBuf = true;

}

// �F�̑���
void Object2D::MoveColor(int r, int g, int b, int a)
{
	// �F�̑���
	m_color.rgba[3] = m_color.rgba[3] + r >= 255 ? 255 : m_color.rgba[3] + r;
	m_color.rgba[2] = m_color.rgba[2] + g >= 255 ? 255 : m_color.rgba[2] + g;
	m_color.rgba[1] = m_color.rgba[1] + b >= 255 ? 255 : m_color.rgba[1] + b;
	m_color.rgba[0] = m_color.rgba[0] + a >= 255 ? 255 : m_color.rgba[0] + a;
	m_color.rgba[3] = m_color.rgba[3] + r <=   0 ?   0 : m_color.rgba[3] + r;
	m_color.rgba[2] = m_color.rgba[2] + g <=   0 ?   0 : m_color.rgba[2] + g;
	m_color.rgba[1] = m_color.rgba[1] + b <=   0 ?   0 : m_color.rgba[1] + b;
	m_color.rgba[0] = m_color.rgba[0] + a <=   0 ?   0 : m_color.rgba[0] + a;

	// ���_�o�b�t�@�̍X�V�t���OON
	m_bUpdateVertexBuf = true;

}

// UV�J�n�_�̑���
void Object2D::MoveUV_StartPoint(D3DXVECTOR2& moveUV_StartPoint)
{
	// UV�J�n�_�̑���
	m_UV_StartPoint += moveUV_StartPoint;

	// ���_�o�b�t�@�̍X�V�t���OON
	m_bUpdateVertexBuf = true;

}

// UV�傫���̑���
void Object2D::MoveUV_Size(D3DXVECTOR2& moveUV_Size)
{
	// UV�J�n�_�̑���
	m_UV_Size += moveUV_Size;

	// ���_�o�b�t�@�̍X�V�t���OON
	m_bUpdateVertexBuf = true;

}



//=============================================================================
// �ݒ菈��
// ���W�̐ݒ�
void Object2D::SetPosition(D3DXVECTOR3& position)
{
	// ���W�̈ړ�
	Object::SetPosition(position);

	// ���_�o�b�t�@�̍X�V�t���OON
	m_bUpdateVertexBuf = true;

}

// �傫���̐ݒ�
void Object2D::SetSize(D3DXVECTOR3& size)
{
	// �傫���̐ݒ�
	m_halfSize = size * 0.5f;
	m_radius   = sqrtf(m_halfSize.x * m_halfSize.x + m_halfSize.y * m_halfSize.y);	// ���a
	m_angle    = atan2f(m_halfSize.y, m_halfSize.x);								// atan

	// ���_�o�b�t�@�̍X�V�t���OON
	m_bUpdateVertexBuf = true;

}

// ��]���̐ݒ�
void Object2D::SetRotate(float rotate)
{
	// ��]���̑���
	m_rotate = rotate;

	// ���_�o�b�t�@�̍X�V�t���OON
	m_bUpdateVertexBuf = true;

}

// �F�̐ݒ�
void Object2D::SetColor(unsigned int rgba)
{
	// �F�ݒ�
	m_color.color = rgba;

	// ���_�o�b�t�@�̍X�V�t���OON
	m_bUpdateVertexBuf = true;

}

// UV�J�n�_�̐ݒ�
void Object2D::SetUV_StartPoint(D3DXVECTOR2& UV_StartPoint)
{
	// UV�J�n�_�̐ݒ�
	m_UV_StartPoint = UV_StartPoint;

	// ���_�o�b�t�@�̍X�V�t���OON
	m_bUpdateVertexBuf = true;

}

// UV�̑傫���̐ݒ�
void Object2D::SetUV_Size(D3DXVECTOR2& UV_Size)
{
	// UV�̑傫���̐ݒ�
	m_UV_Size = UV_Size;

	// ���_�o�b�t�@�̍X�V�t���OON
	m_bUpdateVertexBuf = true;

}


//=============================================================================
//	private�֐�
// ���_�o�b�t�@�̐���
void Object2D::MakeVertexBuf()
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();

	// ���_�o�b�t�@�𐶐�
	if (m_pVtxBuff == nullptr) {
		// ���_�����Ɏ��s�����H
		if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL))) {
			// �G���[���b�Z�[�W�̕\��
			_MSGERROR("Failed Create Vertex Buffer!!", "void Object2D::MakeVertexBuf()");

			// ���̃I�u�W�F�N�g��j������
			this->Release();

			return;
		}
	}

	// VRAM�̉��z�A�h���X�擾
	VERTEX_2D* pVtx;
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	D3DXVECTOR3 position = Object::GetPosition();
	pVtx[0].pos = D3DXVECTOR3(position.x - m_halfSize.x, position.y - m_halfSize.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(position.x + m_halfSize.x, position.y - m_halfSize.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(position.x - m_halfSize.x, position.y + m_halfSize.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(position.x + m_halfSize.x, position.y + m_halfSize.y, 0.0f);

	// 
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// ���_�F�̐ݒ�
	pVtx[0].color = D3DCOLOR_RGBA(m_color.rgba[3], m_color.rgba[2], m_color.rgba[1], m_color.rgba[0]);
	pVtx[1].color = D3DCOLOR_RGBA(m_color.rgba[3], m_color.rgba[2], m_color.rgba[1], m_color.rgba[0]);
	pVtx[2].color = D3DCOLOR_RGBA(m_color.rgba[3], m_color.rgba[2], m_color.rgba[1], m_color.rgba[0]);
	pVtx[3].color = D3DCOLOR_RGBA(m_color.rgba[3], m_color.rgba[2], m_color.rgba[1], m_color.rgba[0]);

	// �e�N�X�`��UV�l�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(m_UV_StartPoint.x              , m_UV_StartPoint.y              );
	pVtx[1].tex = D3DXVECTOR2(m_UV_StartPoint.x + m_UV_Size.x, m_UV_StartPoint.y              );
	pVtx[2].tex = D3DXVECTOR2(m_UV_StartPoint.x              , m_UV_StartPoint.y + m_UV_Size.y);
	pVtx[3].tex = D3DXVECTOR2(m_UV_StartPoint.x + m_UV_Size.x, m_UV_StartPoint.y + m_UV_Size.y);

	// VRAM�̉��z�A�h���X���
	m_pVtxBuff->Unlock();
}

// ���_�o�b�t�@�̍X�V
void Object2D::UpdateVertexBuf()
{
	// �ϐ��̒�`
	D3DXVECTOR3 position = Object::GetPosition();
	VERTEX_2D* pVtx;

	// VRAM�̉��z�A�h���X�擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3( position.x + cosf(m_rotate + m_angle + D3DX_PI) * m_radius
							 , position.y + sinf(m_rotate + m_angle + D3DX_PI) * m_radius, 0.0f);
	pVtx[1].pos = D3DXVECTOR3( position.x + cosf(m_rotate - m_angle          ) * m_radius
							 , position.y + sinf(m_rotate - m_angle          ) * m_radius, 0.0f);
	pVtx[2].pos = D3DXVECTOR3( position.x + cosf(m_rotate - m_angle + D3DX_PI) * m_radius
							 , position.y + sinf(m_rotate - m_angle + D3DX_PI) * m_radius, 0.0f);
	pVtx[3].pos = D3DXVECTOR3( position.x + cosf(m_rotate + m_angle          ) * m_radius
							 , position.y + sinf(m_rotate + m_angle          ) * m_radius, 0.0f);

	// ���_�F�̐ݒ�
	pVtx[0].color = D3DCOLOR_RGBA(m_color.rgba[3], m_color.rgba[2], m_color.rgba[1], m_color.rgba[0]);
	pVtx[1].color = D3DCOLOR_RGBA(m_color.rgba[3], m_color.rgba[2], m_color.rgba[1], m_color.rgba[0]);
	pVtx[2].color = D3DCOLOR_RGBA(m_color.rgba[3], m_color.rgba[2], m_color.rgba[1], m_color.rgba[0]);
	pVtx[3].color = D3DCOLOR_RGBA(m_color.rgba[3], m_color.rgba[2], m_color.rgba[1], m_color.rgba[0]);

	// �e�N�X�`��UV�l�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(m_UV_StartPoint.x              , m_UV_StartPoint.y              );
	pVtx[1].tex = D3DXVECTOR2(m_UV_StartPoint.x + m_UV_Size.x, m_UV_StartPoint.y              );
	pVtx[2].tex = D3DXVECTOR2(m_UV_StartPoint.x              , m_UV_StartPoint.y + m_UV_Size.y);
	pVtx[3].tex = D3DXVECTOR2(m_UV_StartPoint.x + m_UV_Size.x, m_UV_StartPoint.y + m_UV_Size.y);

	// VRAM�̉��z�A�h���X���
	m_pVtxBuff->Unlock();


	// ���_�o�b�t�@�̍X�V�t���OOFF
	m_bUpdateVertexBuf = false;

}

