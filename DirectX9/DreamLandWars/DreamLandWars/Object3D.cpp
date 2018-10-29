//*****************************************************************************
//
//		3D�|���S���i���X�g�\���j
//												Autohr : Yusuke Seki
//*****************************************************************************
#include "Object3D.h"
#include "renderer.h"
#include "collision.h"


//-----------------------------------------------------------------------------
// �R���X�g���N�^
//-----------------------------------------------------------------------------
Object3D::Object3D() :Object(Object::TYPE::TYPE_3D)
{
	// �����o�ϐ�������
	m_halfSize           = D3DXVECTOR3(0, 0, 0);
	m_rotate             = D3DXVECTOR3(0, 0, 0);
	m_scale              = D3DXVECTOR3(0, 0, 0);
	m_radius             = 0;
	m_normal[0]          = D3DXVECTOR3(0, 0, 0);
	m_normal[1]          = D3DXVECTOR3(0, 0, 0);
	m_normal[2]          = D3DXVECTOR3(0, 0, 0);
	m_normal[3]          = D3DXVECTOR3(0, 0, 0);
	m_color.color        = 0xffffffff;
	m_UV_StartPoint      = D3DXVECTOR2(0, 0);
	m_UV_Size            = D3DXVECTOR2(0, 0);
	m_pVtxBuff           = nullptr;
	m_pTexture           = nullptr;
	m_bUpdateVertexBuf   = false;
	m_bUpdateWorldMatrix = false;
	m_bDraw              = true;
}


//-----------------------------------------------------------------------------
// �R���X�g���N�^
//-----------------------------------------------------------------------------
Object3D::Object3D(Object::TYPE type) :Object(type)
{
	// �����o�ϐ�������
	m_halfSize           = D3DXVECTOR3(0, 0, 0);
	m_rotate             = D3DXVECTOR3(0, 0, 0);
	m_scale              = D3DXVECTOR3(0, 0, 0);
	m_radius             = 0;
	m_normal[0]          = D3DXVECTOR3(0, 0, 0);
	m_normal[1]          = D3DXVECTOR3(0, 0, 0);
	m_normal[2]          = D3DXVECTOR3(0, 0, 0);
	m_normal[3]          = D3DXVECTOR3(0, 0, 0);
	m_color.color        = 0xffffffff;
	m_UV_StartPoint      = D3DXVECTOR2(0, 0);
	m_UV_Size            = D3DXVECTOR2(0, 0);
	m_pVtxBuff           = nullptr;
	m_pTexture           = nullptr;
	m_bUpdateVertexBuf   = false;
	m_bUpdateWorldMatrix = false;
	m_bDraw              = true;
}


//-----------------------------------------------------------------------------
// �f�X�g���N�^
//-----------------------------------------------------------------------------
Object3D::~Object3D()
{
	// �I������
	Uninit();

}


//-----------------------------------------------------------------------------
// ���̂̐���
//-----------------------------------------------------------------------------
Object3D* Object3D::Create(D3DXVECTOR3& pos, D3DXVECTOR3& size)
{
	// ����
	Object3D* pObject3D = new Object3D(Object::TYPE::TYPE_3D);

	// ������
	pObject3D->Init(pos, size);

	return pObject3D;
}


//-----------------------------------------------------------------------------
// ����������
//-----------------------------------------------------------------------------
void Object3D::Init(D3DXVECTOR3& position, D3DXVECTOR3& size)
{
	//----- �f�[�^�̐ݒ� -----
	Object::SetPosition(position);																// ���W
	m_halfSize           = size * 0.5f;															// �����̑傫��
	m_rotate             = D3DXVECTOR3(0, 0, 0);												// ��]��
	m_scale              = D3DXVECTOR3(1, 1, 1);												// �g�k��
	m_radius             = sqrtf(m_halfSize.x * m_halfSize.x + m_halfSize.y * m_halfSize.y);	// ���a
	m_normal[0]          = D3DXVECTOR3(0, 0, -1);												// �@��
	m_normal[1]          = D3DXVECTOR3(0, 0, -1);												// �@��
	m_normal[2]          = D3DXVECTOR3(0, 0, -1);												// �@��
	m_normal[3]          = D3DXVECTOR3(0, 0, -1);												// �@��
	m_color.color        = 0xffffffff;															// �F
	m_UV_StartPoint      = D3DXVECTOR2(0, 0);													// UV�J�n�_
	m_UV_Size            = D3DXVECTOR2(1, 1);													// UV�傫��
	m_bUpdateVertexBuf   = false;																// true �Œ��_�o�b�t�@�̍X�V����
	m_bUpdateWorldMatrix = false;																// true �Ń��[���h�}�g���N�X�̍X�V����
	m_bDraw              = true;																// true �ŕ`�揈�����s��

	// ���_�o�b�t�@�̐���
	this->MakeVertexBuf();

	// �s����Z�o
	this->UpdateWorldMatrix();

}


//-----------------------------------------------------------------------------
// �I������
//-----------------------------------------------------------------------------
void Object3D::Uninit(void)
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
void Object3D::Draw(void)
{
	// false �ŕ`�揈�����s��Ȃ�
	if (!m_bDraw) return;

	// true �Œ��_�o�b�t�@�̍X�V����������
	if (m_bUpdateVertexBuf) this->UpdateVertexBuf();

	// true �Ń��[���h�}�g���N�X�̍X�V����������
	if (m_bUpdateWorldMatrix) this->UpdateWorldMatrix();

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();

	// �f�o�C�X�Ƀ��[���h�ϊ��s���ݒ�
	pDevice->SetTransform( D3DTS_WORLD , &m_WorldMatrix );

	// �X�g���[���̐ݒ�
	pDevice->SetStreamSource( 0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF( FVF_VERTEX_3D );

	// �e�N�X�`���\��t��
	pDevice->SetTexture(0, m_pTexture);

	// �`��
	pDevice->DrawPrimitive(	D3DPT_TRIANGLESTRIP, 0, 2);

}



//=============================================================================
//	��������
// ���W�̈ړ�
void Object3D::MovePosition(D3DXVECTOR3& movePosition)
{
	// ���W�̈ړ�
	Object::MovePosition(movePosition);

	// ���[���h�}�g���N�X�̍X�V�t���OON
	m_bUpdateWorldMatrix = true;
}

// �傫���̑���
void Object3D::MoveSize(D3DXVECTOR3& moveSize)
{
	// �傫���̑���
	m_halfSize += moveSize * 0.5f;
	m_radius    = sqrtf(m_halfSize.x * m_halfSize.x + m_halfSize.y * m_halfSize.y);	// ���a
	
	// ���_�o�b�t�@�̍X�V�t���OON
	m_bUpdateVertexBuf = true;

}

// ��]���̑���
void Object3D::MoveRotate(D3DXVECTOR3& moveRotate)
{
	// ��]���̑���
	m_rotate += moveRotate;
	
	// ���[���h�}�g���N�X�̍X�V�t���OON
	m_bUpdateWorldMatrix = true;
}

// �g�k���̑���
void Object3D::MoveScale(D3DXVECTOR3& moveScale)
{
	// �g�k���̑���
	m_scale.x = m_scale.x + moveScale.x < 0 ? 0 : m_scale.x + moveScale.x;
	m_scale.y = m_scale.y + moveScale.y < 0 ? 0 : m_scale.y + moveScale.y;
	m_scale.z = m_scale.z + moveScale.z < 0 ? 0 : m_scale.z + moveScale.z;

	// ���[���h�}�g���N�X�̍X�V�t���OON
	m_bUpdateWorldMatrix = true;
}

// �@���̑���
void Object3D::MoveNormal(D3DXVECTOR3& moveNormal0, D3DXVECTOR3& moveNormal1, D3DXVECTOR3& moveNormal2, D3DXVECTOR3& moveNormal3)
{
	// �@���̑���
	m_normal[0] += moveNormal0;
	m_normal[1] += moveNormal1;
	m_normal[2] += moveNormal2;
	m_normal[3] += moveNormal3;
	
	// ���_�o�b�t�@�̍X�V�t���OON
	m_bUpdateVertexBuf = true;
}

// �F�̑���
void Object3D::MoveColor(int r, int g, int b, int a)
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
void Object3D::MoveUV_StartPoint(D3DXVECTOR2& moveUV_StartPoint)
{
	// UV�J�n�_�̑���
	m_UV_StartPoint += moveUV_StartPoint;

	// ���_�o�b�t�@�̍X�V�t���OON
	m_bUpdateVertexBuf = true;

}

// UV�傫���̑���
void Object3D::MoveUV_Size(D3DXVECTOR2& moveUV_Size)
{
	// UV�J�n�_�̑���
	m_UV_Size += moveUV_Size;

	// ���_�o�b�t�@�̍X�V�t���OON
	m_bUpdateVertexBuf = true;

}



//=============================================================================
// �ݒ菈��
// ���W�̐ݒ�
void Object3D::SetPosition(D3DXVECTOR3& position)
{
	// ���W�̈ړ�
	Object::SetPosition(position);

	// ���[���h�}�g���N�X�̍X�V�t���OON
	m_bUpdateWorldMatrix = true;
}

// �傫���̐ݒ�
void Object3D::SetSize(D3DXVECTOR3& size)
{
	// �傫���̐ݒ�
	m_halfSize = size * 0.5f;
	m_radius   = sqrtf(m_halfSize.x * m_halfSize.x + m_halfSize.y * m_halfSize.y);	// ���a

	// ���_�o�b�t�@�̍X�V�t���OON
	m_bUpdateVertexBuf = true;

}

// ��]���̐ݒ�
void Object3D::SetRotate(D3DXVECTOR3& rotate)
{
	// ��]���̐ݒ�
	m_rotate = rotate;

	// ���[���h�}�g���N�X�̍X�V�t���OON
	m_bUpdateWorldMatrix = true;
}

// �g�k���̐ݒ�
void Object3D::SetScale(D3DXVECTOR3& scale)
{
	// �g�k���̐ݒ�
	m_scale.x = scale.x < 0 ? 0 : scale.x;
	m_scale.y = scale.y < 0 ? 0 : scale.y;
	m_scale.z = scale.z < 0 ? 0 : scale.z;


	// ���[���h�}�g���N�X�̍X�V�t���OON
	m_bUpdateWorldMatrix = true;
}

// �@���̐ݒ�
void Object3D::SetNormal(D3DXVECTOR3& moveNormal0, D3DXVECTOR3& moveNormal1, D3DXVECTOR3& moveNormal2, D3DXVECTOR3& moveNormal3)
{
	// �@���̑���
	m_normal[0] = moveNormal0;
	m_normal[1] = moveNormal1;
	m_normal[2] = moveNormal2;
	m_normal[3] = moveNormal3;

	// ���_�o�b�t�@�̍X�V�t���OON
	m_bUpdateVertexBuf = true;
}

// �F�̐ݒ�
void Object3D::SetColor(unsigned int rgba)
{
	// �F�ݒ�
	m_color.color = rgba;

	// ���_�o�b�t�@�̍X�V�t���OON
	m_bUpdateVertexBuf = true;

}

// UV�J�n�_�̐ݒ�
void Object3D::SetUV_StartPoint(D3DXVECTOR2& UV_StartPoint)
{
	// UV�J�n�_�̐ݒ�
	m_UV_StartPoint = UV_StartPoint;

	// ���_�o�b�t�@�̍X�V�t���OON
	m_bUpdateVertexBuf = true;

}

// UV�̑傫���̐ݒ�
void Object3D::SetUV_Size(D3DXVECTOR2& UV_Size)
{
	// UV�̑傫���̐ݒ�
	m_UV_StartPoint = UV_Size;

	// ���_�o�b�t�@�̍X�V�t���OON
	m_bUpdateVertexBuf = true;

}


//=============================================================================
//	private�֐�
// ���_�o�b�t�@�̐���
void Object3D::MakeVertexBuf()
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();

	// ���_�o�b�t�@�𐶐�
	if( m_pVtxBuff == nullptr ){
		// ���_�����Ɏ��s�����H
		if( FAILED( pDevice->CreateVertexBuffer( sizeof( VERTEX_3D ) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &m_pVtxBuff, nullptr ) )){
			// �G���[���b�Z�[�W�̕\��
			_MSGERROR("Failed Create Vertex Buffer!!", "void Object3D::MakeVertexBuf()");

			// ���̃I�u�W�F�N�g��j������
			this->Release();

			return;
		}
	}

	// VRAM�̉��z�A�h���X�擾
	VERTEX_3D* pVtx;
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-m_halfSize.x,  m_halfSize.y,  m_halfSize.z);	// ����
	pVtx[1].pos = D3DXVECTOR3( m_halfSize.x,  m_halfSize.y,  m_halfSize.z);	// �E��
	pVtx[2].pos = D3DXVECTOR3(-m_halfSize.x, -m_halfSize.y, -m_halfSize.z);	// ����
	pVtx[3].pos = D3DXVECTOR3( m_halfSize.x, -m_halfSize.y, -m_halfSize.z);	// �E��

	// �@���̐ݒ�
	pVtx[0].normal = m_normal[0];
	pVtx[1].normal = m_normal[1];
	pVtx[2].normal = m_normal[2];
	pVtx[3].normal = m_normal[3];

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

	// �ʖ@�����擾
	CreatePolygonNormal(&m_normal_Surface, pVtx[0].pos, pVtx[1].pos, pVtx[2].pos);

}

// ���_�o�b�t�@�̍X�V
void Object3D::UpdateVertexBuf()
{
	// VRAM�̉��z�A�h���X�擾
	VERTEX_3D* pVtx;
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-m_halfSize.x,  m_halfSize.y,  m_halfSize.z);	// ����
	pVtx[1].pos = D3DXVECTOR3( m_halfSize.x,  m_halfSize.y,  m_halfSize.z);	// �E��
	pVtx[2].pos = D3DXVECTOR3(-m_halfSize.x, -m_halfSize.y, -m_halfSize.z);	// ����
	pVtx[3].pos = D3DXVECTOR3( m_halfSize.x, -m_halfSize.y, -m_halfSize.z);	// �E��

	// �@���̐ݒ�
	pVtx[0].normal = m_normal[0];
	pVtx[1].normal = m_normal[1];
	pVtx[2].normal = m_normal[2];
	pVtx[3].normal = m_normal[3];

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

	// �ʖ@�����擾
	CreatePolygonNormal(&m_normal_Surface, pVtx[0].pos, pVtx[1].pos, pVtx[2].pos);

}

// ���[���h�}�g���N�X�̍X�V
void Object3D::UpdateWorldMatrix()
{
	// �ړ��A��]�A�g�k�s��̌v�Z
	D3DXMATRIX mtxTranslate, mtxRotate, mtxScale;
	D3DXVECTOR3 position = Object::GetPosition();
	D3DXMatrixTranslation(&mtxTranslate, position.x, position.y, position.z);
	D3DXMatrixRotationYawPitchRoll(&mtxRotate, m_rotate.y, m_rotate.x, m_rotate.z);
	D3DXMatrixScaling(&mtxScale, m_scale.x, m_scale.y, m_scale.z);

	// �R�s��̍���
	D3DXMatrixIdentity(&m_WorldMatrix);
	D3DXMatrixMultiply(&m_WorldMatrix, &m_WorldMatrix, &mtxScale);
	D3DXMatrixMultiply(&m_WorldMatrix, &m_WorldMatrix, &mtxRotate);
	D3DXMatrixMultiply(&m_WorldMatrix, &m_WorldMatrix, &mtxTranslate);

	// ���[���h�}�g���N�X�̍X�V�t���OOFF
	m_bUpdateWorldMatrix = false;

}
