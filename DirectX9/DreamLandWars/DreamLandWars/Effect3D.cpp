//*****************************************************************************
//
//		�G�t�F�N�g�i3D�j
//												Autohr : Yusuke Seki
//*****************************************************************************
#include "Effect3D.h"
#include "renderer.h"
#include "texture.h"
#include "MainGame.h"


//-----------------------------------------------------------------------------
// �R���X�g���N�^
//-----------------------------------------------------------------------------
Effect3D::Effect3D(EffectManager::TYPE type) :EffectManager(type)
{
	// �����o�ϐ�������
	m_halfSize           = D3DXVECTOR3(0, 0, 0);
	m_rotate             = D3DXVECTOR3(0, 0, 0);
	m_scale              = D3DXVECTOR3(0, 0, 0);
	m_radius             = 0;
	m_accelerate         = D3DXVECTOR3(0, 0, 0);
	m_normal[0]          = D3DXVECTOR3(0, 0, 0);
	m_normal[1]          = D3DXVECTOR3(0, 0, 0);
	m_normal[2]          = D3DXVECTOR3(0, 0, 0);
	m_normal[3]          = D3DXVECTOR3(0, 0, 0);
	m_color_R            = 0.f;
	m_color_G            = 0.f;
	m_color_B            = 0.f;
	m_color_A            = 0.f;
	m_UV_StartPoint      = D3DXVECTOR2(0, 0);
	m_UV_Size            = D3DXVECTOR2(0, 0);
	m_pVtxBuff           = nullptr;
	m_pTexture           = nullptr;
	m_bUpdateVertexBuf   = false;
	m_bUpdateWorldMatrix = false;
	m_bInstance          = true;

	m_ChangeRotateByFrame       = D3DXVECTOR3(0, 0, 0);
	m_ChangeScaleByFrame        = D3DXVECTOR3(0, 0, 0);
	m_ChangeAccelerateByFrame   = D3DXVECTOR3(0, 0, 0);
	m_ChangeRedByFrame          = 0.f;
	m_ChangeGreenByFrame        = 0.f;
	m_ChangeBlueByFrame         = 0.f;
	m_ChangeAlphaByFrame        = 0.f;
	m_ChangeUVStartPointByFrame = D3DXVECTOR2(0, 0);
	m_ChangeUVSizeByFrame       = D3DXVECTOR2(0, 0);
	m_ChangeRedByFrame          = 0;
	m_ChangeGreenByFrame        = 0;
	m_ChangeBlueByFrame         = 0;
	m_ChangeAlphaByFrame        = 0;
	m_life                      = 0;

}


//-----------------------------------------------------------------------------
// �f�X�g���N�^
//-----------------------------------------------------------------------------
Effect3D::~Effect3D()
{
	// �I������
	Uninit();

}


//-----------------------------------------------------------------------------
// ���̂̐���
//-----------------------------------------------------------------------------
Effect3D* Effect3D::Create(D3DXVECTOR3& pos, D3DXVECTOR3& size)
{
	// ����
	Effect3D* pEffect3D = new Effect3D(EffectManager::TYPE::TYPE_3D);

	// ������
	pEffect3D->Init(pos, size);

	return pEffect3D;
}


//-----------------------------------------------------------------------------
// ����������
//-----------------------------------------------------------------------------
void Effect3D::Init(D3DXVECTOR3& position, D3DXVECTOR3& size)
{
	//----- �f�[�^�̐ݒ� -----
	EffectManager::SetPosition(position);														// ���W
	m_halfSize           = size * 0.5f;															// �����̑傫��
	m_rotate             = D3DXVECTOR3(0, 0, 0);												// ��]��
	m_scale              = D3DXVECTOR3(1, 1, 1);												// �g�k��
	m_radius             = sqrtf(m_halfSize.x * m_halfSize.x + m_halfSize.y * m_halfSize.y);	// ���a
	m_accelerate         = D3DXVECTOR3(0, 0, 0);												// �����x
	m_normal[0]          = D3DXVECTOR3(0, 0, 1);												// �@��
	m_normal[1]          = D3DXVECTOR3(0, 0, 1);												// �@��
	m_normal[2]          = D3DXVECTOR3(0, 0, 1);												// �@��
	m_normal[3]          = D3DXVECTOR3(0, 0, 1);												// �@��
	m_color_R            = 0.f;																	// ���_�F - ��
	m_color_G            = 0.f;																	// ���_�F - ��
	m_color_B            = 0.f;																	// ���_�F - ��
	m_color_A            = 0.f;																	// ���_�F - ����
	m_UV_StartPoint      = D3DXVECTOR2(0, 0);													// UV�J�n�_
	m_UV_Size            = D3DXVECTOR2(1, 1);													// UV�傫��
	m_bUpdateVertexBuf   = false;																// true �Œ��_�o�b�t�@�̍X�V����
	m_bUpdateWorldMatrix = false;																// true �Ń��[���h�}�g���N�X�̍X�V����
	m_bInstance          = true;																// true �Ŏg�p��

	m_ChangeRotateByFrame       = D3DXVECTOR3(0, 0, 0);	// �t���[���Ԃ̉�]���ω���
	m_ChangeScaleByFrame        = D3DXVECTOR3(0, 0, 0);	// �t���[���Ԃ̊g�k���ω���
	m_ChangeAccelerateByFrame   = D3DXVECTOR3(0, 0, 0);	// �t���[���Ԃ̉����x�ω���
	m_ChangeRedByFrame          = 0;					// �t���[���Ԃ̒��_�F�E�ԁA�ω���
	m_ChangeGreenByFrame        = 0;					// �t���[���Ԃ̒��_�F�E�΁A�ω���
	m_ChangeBlueByFrame         = 0;					// �t���[���Ԃ̒��_�F�E�A�ω���
	m_ChangeAlphaByFrame        = 0;					// �t���[���Ԃ̒��_�F�E���ߒl�A�ω���
	m_ChangeUVStartPointByFrame = D3DXVECTOR2(0, 0);	// �t���[���Ԃ�UV�J�n�_�ω���
	m_ChangeUVSizeByFrame       = D3DXVECTOR2(0, 0);	// �t���[���Ԃ�UV�T�C�Y�ω���
	m_life                      = 0;					// ����

	// ���_�o�b�t�@�̐���
	Effect3D::MakeVertexBuf();

	// �s����Z�o
	this->UpdateWorldMatrix();

}


//-----------------------------------------------------------------------------
// �I������
//-----------------------------------------------------------------------------
void Effect3D::Uninit(void)
{
	// ���_�o�b�t�@�̔j��
	if (m_pVtxBuff != nullptr) {
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

}


//-----------------------------------------------------------------------------
// �X�V����
//-----------------------------------------------------------------------------
void Effect3D::Update(void)
{
	// ���g�p�ŏ�������
	if (!m_bInstance) return;

	// �������s������A�g�p�t���OOFF
	if (m_life <= 0) {
		m_bInstance = false;
		return;
	}

	// �����̌���
	m_life--;

	// �ʒu�̍X�V
	Effect3D::MovePosition(m_accelerate);

	// ��]���̍X�V
	Effect3D::MoveRotate(m_ChangeRotateByFrame);

	// �g�k���̍X�V
	Effect3D::MoveScale(m_ChangeScaleByFrame);

	// �����x�̍X�V
	Effect3D::MoveAccelerate(m_ChangeAccelerateByFrame);

	// ���_�F�̍X�V
	Effect3D::MoveColor(m_ChangeRedByFrame, m_ChangeGreenByFrame, m_ChangeBlueByFrame, m_ChangeAlphaByFrame);
	
	// UV�J�n�_�̍X�V
	Effect3D::MoveUV_StartPoint(m_ChangeUVStartPointByFrame);

	// UV�T�C�Y�̍X�V
	Effect3D::MoveUV_Size(m_ChangeUVSizeByFrame);

}


//-----------------------------------------------------------------------------
// �`�揈��
//-----------------------------------------------------------------------------
void Effect3D::Draw(void)
{
	// ���g�p�Ȃ�`�揈�����s��Ȃ�
	if (!m_bInstance) return;

	// true �Œ��_�o�b�t�@�̍X�V����������
	if (m_bUpdateVertexBuf) Effect3D::UpdateVertexBuf();

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
void Effect3D::MovePosition(D3DXVECTOR3& movePosition)
{
	// ���W�̈ړ�
	EffectManager::MovePosition(movePosition);

	// ���[���h�}�g���N�X�̍X�V�t���OON
	m_bUpdateWorldMatrix = true;
}

// �傫���̑���
void Effect3D::MoveSize(D3DXVECTOR3& moveSize)
{
	// �傫���̑���
	m_halfSize += moveSize * 0.5f;
	m_radius    = sqrtf(m_halfSize.x * m_halfSize.x + m_halfSize.y * m_halfSize.y);	// ���a
	
	// ���_�o�b�t�@�̍X�V�t���OON
	m_bUpdateVertexBuf = true;

}

// ��]���̑���
void Effect3D::MoveRotate(D3DXVECTOR3& moveRotate)
{
	// ��]���̑���
	m_rotate += moveRotate;
	
	// ���[���h�}�g���N�X�̍X�V�t���OON
	m_bUpdateWorldMatrix = true;
}

// �g�k���̑���
void Effect3D::MoveScale(D3DXVECTOR3& moveScale)
{
	// �g�k���̑���
	m_scale.x = m_scale.x + moveScale.x < 0 ? 0 : m_scale.x + moveScale.x;
	m_scale.y = m_scale.y + moveScale.y < 0 ? 0 : m_scale.y + moveScale.y;
	m_scale.z = m_scale.z + moveScale.z < 0 ? 0 : m_scale.z + moveScale.z;

	// ���[���h�}�g���N�X�̍X�V�t���OON
	m_bUpdateWorldMatrix = true;
}

// �@���̑���
void Effect3D::MoveNormal(D3DXVECTOR3& moveNormal0, D3DXVECTOR3& moveNormal1, D3DXVECTOR3& moveNormal2, D3DXVECTOR3& moveNormal3)
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
void Effect3D::MoveColor(float r, float g, float b, float a)
{
	// �F�̑���
	m_color_R = m_color_R + r >= 255 ? 255 : m_color_R + r;
	m_color_G = m_color_G + g >= 255 ? 255 : m_color_G + g;
	m_color_B = m_color_B + b >= 255 ? 255 : m_color_B + b;
	m_color_A = m_color_A + a >= 255 ? 255 : m_color_A + a;
	m_color_R = m_color_R + r <=   0 ?   0 : m_color_R + r;
	m_color_G = m_color_G + g <=   0 ?   0 : m_color_G + g;
	m_color_B = m_color_B + b <=   0 ?   0 : m_color_B + b;
	m_color_A = m_color_A + a <=   0 ?   0 : m_color_A + a;

	// ���_�o�b�t�@�̍X�V�t���OON
	m_bUpdateVertexBuf = true;

}

// UV�J�n�_�̑���
void Effect3D::MoveUV_StartPoint(D3DXVECTOR2& moveUV_StartPoint)
{
	// UV�J�n�_�̑���
	m_UV_StartPoint += moveUV_StartPoint;

	// ���_�o�b�t�@�̍X�V�t���OON
	m_bUpdateVertexBuf = true;

}

// UV�傫���̑���
void Effect3D::MoveUV_Size(D3DXVECTOR2& moveUV_Size)
{
	// UV�J�n�_�̑���
	m_UV_Size += moveUV_Size;

	// ���_�o�b�t�@�̍X�V�t���OON
	m_bUpdateVertexBuf = true;

}



//=============================================================================
// �ݒ菈��
// �G�t�F�N�g�̔���
void Effect3D::SetEffect(D3DXVECTOR3& position, D3DXVECTOR3& vecZ, Effect3D::TYPE effectType)
{
	// ���̎�����T��
	Effect3D* pEffect3D = (Effect3D*)EffectManager::GetLDATA_HEAD(EffectManager::TYPE::TYPE_3D);

	// �P������Ă��Ȃ������琶������
	if (pEffect3D == nullptr) {
		// ��������
		pEffect3D = Effect3D::Create(D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0));

		// �ݒ菈��
		pEffect3D->SetEffect_Protected(position, vecZ, effectType);

		return;
	}

	// ����Ă����疢�g�p�̃G�t�F�N�g��T��
	Effect3D* pCurrent = (Effect3D*)pEffect3D;
	Effect3D* pNext    = (Effect3D*)pEffect3D->GetNextPointer();
	for (;;) {
		// ���g�p�Ȃ�ݒ肵�ďI��
		if (!pCurrent->m_bInstance) {
			pCurrent->SetEffect_Protected(position, vecZ, effectType);
			break;
		}

		// ���g�p�G�t�F�N�g��������Ȃ���΁A�V������������
		if (pNext == nullptr) {
			// ��������
			pNext = Effect3D::Create(D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0));

			// �ݒ菈��
			pNext->SetEffect_Protected(position, vecZ, effectType);

			break;
		}

		// �|�C���^�����炷
		pCurrent = pNext;
		pNext    = (Effect3D*)pCurrent->GetNextPointer();

	}
}

// ���W�̐ݒ�
void Effect3D::SetPosition(D3DXVECTOR3& position)
{
	// ���W�̈ړ�
	EffectManager::SetPosition(position);

	// ���[���h�}�g���N�X�̍X�V�t���OON
	m_bUpdateWorldMatrix = true;
}

// �傫���̐ݒ�
void Effect3D::SetSize(D3DXVECTOR3& size)
{
	// �傫���̐ݒ�
	m_halfSize = size * 0.5f;
	m_radius   = sqrtf(m_halfSize.x * m_halfSize.x + m_halfSize.y * m_halfSize.y);	// ���a

	// ���_�o�b�t�@�̍X�V�t���OON
	m_bUpdateVertexBuf = true;

}

// ��]���̐ݒ�
void Effect3D::SetRotate(D3DXVECTOR3& rotate)
{
	// ��]���̑���
	m_rotate = rotate;

	// ���[���h�}�g���N�X�̍X�V�t���OON
	m_bUpdateWorldMatrix = true;
}

// �g�k���̐ݒ�
void Effect3D::SetScale(D3DXVECTOR3& scale)
{
	// �g�k���̐ݒ�
	m_scale.x = scale.x < 0 ? 0 : scale.x;
	m_scale.y = scale.y < 0 ? 0 : scale.y;
	m_scale.z = scale.z < 0 ? 0 : scale.z;


	// ���[���h�}�g���N�X�̍X�V�t���OON
	m_bUpdateWorldMatrix = true;
}

// �@���̐ݒ�
void Effect3D::SetNormal(D3DXVECTOR3& moveNormal0, D3DXVECTOR3& moveNormal1, D3DXVECTOR3& moveNormal2, D3DXVECTOR3& moveNormal3)
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
void Effect3D::SetColor(int r, int g, int b, int a)
{
	// �F�ݒ�
	m_color_R = (float)r;
	m_color_G = (float)g;
	m_color_B = (float)b;
	m_color_A = (float)a;

	// ���_�o�b�t�@�̍X�V�t���OON
	m_bUpdateVertexBuf = true;

}

// UV�J�n�_�̐ݒ�
void Effect3D::SetUV_StartPoint(D3DXVECTOR2& UV_StartPoint)
{
	// UV�J�n�_�̐ݒ�
	m_UV_StartPoint = UV_StartPoint;

	// ���_�o�b�t�@�̍X�V�t���OON
	m_bUpdateVertexBuf = true;

}

// UV�̑傫���̐ݒ�
void Effect3D::SetUV_Size(D3DXVECTOR2& UV_Size)
{
	// UV�̑傫���̐ݒ�
	m_UV_Size = UV_Size;

	// ���_�o�b�t�@�̍X�V�t���OON
	m_bUpdateVertexBuf = true;

}


//=============================================================================
//	private�֐�
// ���_�o�b�t�@�̐���
void Effect3D::MakeVertexBuf()
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();

	// ���_�o�b�t�@�𐶐�
	if( m_pVtxBuff == nullptr ){
		// ���_�����Ɏ��s�����H
		if( FAILED( pDevice->CreateVertexBuffer( sizeof( VERTEX_3D ) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &m_pVtxBuff, nullptr ) )){
			// �G���[���b�Z�[�W�̕\��
			_MSGERROR("Failed Create Vertex Buffer!!", "void Effect3D::MakeVertexBuf()");

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
	pVtx[0].color = D3DCOLOR_RGBA((int)m_color_R, (int)m_color_G, (int)m_color_B, (int)m_color_A);
	pVtx[1].color = D3DCOLOR_RGBA((int)m_color_R, (int)m_color_G, (int)m_color_B, (int)m_color_A);
	pVtx[2].color = D3DCOLOR_RGBA((int)m_color_R, (int)m_color_G, (int)m_color_B, (int)m_color_A);
	pVtx[3].color = D3DCOLOR_RGBA((int)m_color_R, (int)m_color_G, (int)m_color_B, (int)m_color_A);

	// �e�N�X�`��UV�l�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(m_UV_StartPoint.x              , m_UV_StartPoint.y              );
	pVtx[1].tex = D3DXVECTOR2(m_UV_StartPoint.x + m_UV_Size.x, m_UV_StartPoint.y              );
	pVtx[2].tex = D3DXVECTOR2(m_UV_StartPoint.x              , m_UV_StartPoint.y + m_UV_Size.y);
	pVtx[3].tex = D3DXVECTOR2(m_UV_StartPoint.x + m_UV_Size.x, m_UV_StartPoint.y + m_UV_Size.y);

	// VRAM�̉��z�A�h���X���
	m_pVtxBuff->Unlock();
}

// ���_�o�b�t�@�̍X�V
void Effect3D::UpdateVertexBuf()
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
	pVtx[0].color = D3DCOLOR_RGBA((int)m_color_R, (int)m_color_G, (int)m_color_B, (int)m_color_A);
	pVtx[1].color = D3DCOLOR_RGBA((int)m_color_R, (int)m_color_G, (int)m_color_B, (int)m_color_A);
	pVtx[2].color = D3DCOLOR_RGBA((int)m_color_R, (int)m_color_G, (int)m_color_B, (int)m_color_A);
	pVtx[3].color = D3DCOLOR_RGBA((int)m_color_R, (int)m_color_G, (int)m_color_B, (int)m_color_A);

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

// ���[���h�}�g���N�X�̍X�V
void Effect3D::UpdateWorldMatrix()
{
	// �ړ��A��]�A�g�k�s��̌v�Z
	D3DXMATRIX mtxTranslate, mtxRotate, mtxScale;
	D3DXVECTOR3* pPosition = EffectManager::GetPosition();
	D3DXMatrixTranslation(&mtxTranslate, pPosition->x, pPosition->y, pPosition->z);
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

// �G�t�F�N�g�̐ݒ�
void Effect3D::SetEffect_Protected(D3DXVECTOR3& position, D3DXVECTOR3& vecZ, Effect3D::TYPE effectType)
{
	// �����N�_�擾
	D3DXVECTOR3 pos = position;

	// �G�t�F�N�g�̎�ނŏ��������e��ύX
	switch (effectType)
	{
	// ��
	case Effect3D::TYPE::TYPE_FIRE:
		// �����̐ݒ�
		m_life = 60;
		//m_life = 240;

		// �o���ʒu�𒲐�
		pos.x += rand() % 10 - 5;
		pos.y += rand() % 10 - 2;
		EffectManager::SetPosition(pos);

		// �����̑傫���̐ݒ�
		m_halfSize = D3DXVECTOR3(10, 10, 0);

		// ��]���̐ݒ�
		m_rotate = D3DXVECTOR3(0, 0, 0);

		// �g�k���̐ݒ�
		m_scale = D3DXVECTOR3(1, 1, 1);

		// �����x�̐ݒ�
		vecZ *= -1;
		m_accelerate = D3DXVECTOR3(vecZ.x * 3, (float)(rand() % 10001 / 2000), vecZ.z * 3);

		// ���_�F�̐ݒ�
		m_color_R = 255;	// ��
		m_color_G = 128;	// ��
		m_color_B =  64;	// ��
		m_color_A = 255;	// ����

		// UV�J�n�_�̐ݒ�
		m_UV_StartPoint = D3DXVECTOR2(0, 0);

		// UV�T�C�Y�̐ݒ�
		m_UV_Size = D3DXVECTOR2(1, 1);


		// ��]���ω��ʂ̐ݒ�
		m_ChangeRotateByFrame = D3DXVECTOR3(0, 0, 0.1f);

		// �g�k���ω��ʂ̐ݒ�
		m_ChangeScaleByFrame = D3DXVECTOR3(-1.f / m_life, -1.f / m_life, -1.f / m_life);

		// �����x�ω��ʂ̐ݒ�
		m_ChangeAccelerateByFrame = D3DXVECTOR3(0, 0, 0);

		// ���_�F�ω��ʂ̐ݒ�
		m_ChangeRedByFrame   = -m_color_R / m_life;
		m_ChangeGreenByFrame = -m_color_G / m_life;
		m_ChangeBlueByFrame  = -m_color_B / m_life;
		m_ChangeAlphaByFrame = 0;
		//m_ChangeAlphaByFrame = -m_color_A / m_life;

		// UV�J�n�_�ω��ʂ̐ݒ�
		m_ChangeUVStartPointByFrame = D3DXVECTOR2(0, 0);

		// UV�T�C�Y�ω��ʂ̐ݒ�
		m_ChangeUVSizeByFrame = D3DXVECTOR2(0, 0);


		// ���_�o�b�t�@�̍X�V�t���OON
		m_bUpdateVertexBuf = true;

		// ���[���h�}�g���N�X�̍X�V�t���OON
		m_bUpdateWorldMatrix = true;

		// �g�p���t���OON
		m_bInstance = true;

		// �e�N�X�`���̐ݒ�
		SetTexture(MainGame::GetTexture(List_LoadTexture_MainGame::TEXTURE_NAME::EFFECT_TEXNAME)->GetTexture());

		break;


	// ��O
	default:
		// �G���[���b�Z�[�W�̕\��
		_MSGERROR("Cannot Create This Effect Type!!", "void ObjectEffect::SetEffect_Private(D3DXVECTOR3& position, ObjectEffect::TYPE effectType)");
		break;

	}
}

