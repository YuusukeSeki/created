//*****************************************************************************
//
//		�r���{�[�h
//												Autohr : Yusuke Seki
//*****************************************************************************
#include "billboard.h"
#include "renderer.h"
#include "camera.h"
#include "MainGame.h"


//-----------------------------------------------------------------------------
//	�R���X�g���N�^
//-----------------------------------------------------------------------------
Billboard::Billboard(int priority, TYPE type) :Scene(priority, type)
{
	// �����o�ϐ�������
	D3DXMatrixIdentity(&m_mtxWorld);
	m_rot = D3DXVECTOR3(0, 0, 0);
	m_scl = D3DXVECTOR3(0, 0, 0);
	m_size = D3DXVECTOR3(0, 0, 0);
	m_color.color = 0xffffffff;

	m_pVtxBuff = nullptr;
	m_pTexture = nullptr;

}


//-----------------------------------------------------------------------------
//	�f�X�g���N�^
//-----------------------------------------------------------------------------
Billboard::~Billboard()
{
	Uninit();

}


//-----------------------------------------------------------------------------
//	����
//-----------------------------------------------------------------------------
Billboard* Billboard::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXVECTOR3 scl)
{
	Billboard* pBillboard = new Billboard(1, TYPE_3D);
	pBillboard->Init(pos, size, rot, scl);

	return pBillboard;
}


//-----------------------------------------------------------------------------
//	������
//-----------------------------------------------------------------------------
HRESULT Billboard::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXVECTOR3 scl)
{
	D3DXMATRIX mtxTrans, mtxRot, mtxScall;
	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();
	VERTEX_3D* pVtx;
	D3DXVECTOR3 halfSize = size * 0.5f;


	// �����o�ϐ��ݒ�
	SetPos(pos);
	m_size = size;
	m_rot = rot;
	m_scl = scl;


	// ���_�o�b�t�@�̈�̐���
	if (m_pVtxBuff == nullptr) {
		if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D,
			D3DPOOL_MANAGED, &m_pVtxBuff, nullptr))) {
			MessageBox(nullptr, "���_�o�b�t�@�������s", "Billboard::Init", MB_OK);
		}
	}


	// VRAM�̉��z�A�h���X�擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-halfSize.x, halfSize.y, halfSize.z);	// ����
	pVtx[1].pos = D3DXVECTOR3(halfSize.x, halfSize.y, halfSize.z);	// �E��
	pVtx[2].pos = D3DXVECTOR3(-halfSize.x, -halfSize.y, -halfSize.z);	// ����
	pVtx[3].pos = D3DXVECTOR3(halfSize.x, -halfSize.y, -halfSize.z);	// �E��

	// �@���̐ݒ�
	pVtx[0].normal = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	pVtx[1].normal = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	pVtx[2].normal = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	pVtx[3].normal = D3DXVECTOR3(0.0f, 0.0f, 1.0f);

	// ���_�F�̐ݒ�
	pVtx[0].color = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].color = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].color = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].color = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`��UV�l�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// VRAM�̉��z�A�h���X���
	m_pVtxBuff->Unlock();


	// �e�s��v�Z
	D3DXMatrixScaling(&mtxScall, m_scl.x, m_scl.y, m_scl.z);
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);

	// �s��̍���
	D3DXMatrixIdentity(&m_mtxWorld);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxScall);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);


	return S_OK;
}


//-----------------------------------------------------------------------------
//	�I��
//-----------------------------------------------------------------------------
void Billboard::Uninit(void)
{
	// ���_�o�b�t�@�̔j��
	if (m_pVtxBuff != nullptr) {
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

}


//-----------------------------------------------------------------------------
//	�X�V
//-----------------------------------------------------------------------------
void Billboard::Update(void)
{
}


//-----------------------------------------------------------------------------
//	�`��
//-----------------------------------------------------------------------------
void Billboard::Draw(void)
{
	D3DXVECTOR3 pos = GetPos();
	D3DXMATRIX mtxTrans, mtxRot, mtxScall, mtxView, mtxViewInverse;
	Camera* pCamera = MainGame::GetCamera(0);
	mtxView = pCamera->GetMtxView();


	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();

	// ���[���h�s������߂�
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixScaling(&mtxScall, m_scl.x, m_scl.y, m_scl.z);
	D3DXMatrixTranspose(&mtxViewInverse, &mtxView);
	mtxViewInverse._14 = mtxViewInverse._24 = mtxViewInverse._34 = 0.0f;

	D3DXMatrixIdentity(&m_mtxWorld);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxViewInverse);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxScall);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// �f�o�C�X�Ƀ��[���h�ϊ��s���ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// �X�g���[���̐ݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �e�N�X�`���\��t��
	pDevice->SetTexture(0, m_pTexture->GetTexture());

	// ���e�X�g�̐ݒ�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);		// ���e�X�g�n�m
	pDevice->SetRenderState(D3DRS_ALPHAREF, 128);				// ����l
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);	// ���Z�q

	// ���C�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// �`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	// ���C�g��L���ɖ߂�
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	// ���e�X�g�I��
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);		// ���e�X�gOFF

}


//-----------------------------------------------------------------------------
// �傫���̑���
//-----------------------------------------------------------------------------
void Billboard::MoveSize(D3DXVECTOR3 move)
{
	D3DXVECTOR3 halfSize;
	VERTEX_3D* pVtx;


	// �傫�����X�V
	m_size += move;
	halfSize = m_size * 0.5f;

	// VRAM�̉��z�A�h���X�擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-halfSize.x, halfSize.y, halfSize.z);	// ����
	pVtx[1].pos = D3DXVECTOR3(halfSize.x, halfSize.y, halfSize.z);	// �E��
	pVtx[2].pos = D3DXVECTOR3(-halfSize.x, -halfSize.y, -halfSize.z);	// ����
	pVtx[3].pos = D3DXVECTOR3(halfSize.x, -halfSize.y, -halfSize.z);	// �E��

																		// VRAM�̉��z�A�h���X���
	m_pVtxBuff->Unlock();
}


//-----------------------------------------------------------------------------
// �傫���̐ݒ�
//-----------------------------------------------------------------------------
void Billboard::SetSize(D3DXVECTOR3 size)
{
	D3DXVECTOR3 halfSize;
	VERTEX_3D* pVtx;


	// �傫�����X�V
	m_size = size;
	halfSize = m_size * 0.5f;

	// VRAM�̉��z�A�h���X�擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-halfSize.x, halfSize.y, halfSize.z);		// ����
	pVtx[1].pos = D3DXVECTOR3(halfSize.x, halfSize.y, halfSize.z);		// �E��
	pVtx[2].pos = D3DXVECTOR3(-halfSize.x, -halfSize.y, -halfSize.z);	// ����
	pVtx[3].pos = D3DXVECTOR3(halfSize.x, -halfSize.y, -halfSize.z);	// �E��

	// VRAM�̉��z�A�h���X���
	m_pVtxBuff->Unlock();

}


// �F
void Billboard::SetColor(unsigned int color)
{
	m_color.color = color;

	// ���_����ݒ�
	VERTEX_3D* pVtx;

	// VRAM�̉��z�A�h���X�擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_�F�̐ݒ�
	pVtx[0].color = D3DCOLOR_RGBA(m_color.rgba[3], m_color.rgba[2], m_color.rgba[1], m_color.rgba[0]);
	pVtx[1].color = D3DCOLOR_RGBA(m_color.rgba[3], m_color.rgba[2], m_color.rgba[1], m_color.rgba[0]);
	pVtx[2].color = D3DCOLOR_RGBA(m_color.rgba[3], m_color.rgba[2], m_color.rgba[1], m_color.rgba[0]);
	pVtx[3].color = D3DCOLOR_RGBA(m_color.rgba[3], m_color.rgba[2], m_color.rgba[1], m_color.rgba[0]);

	// VRAM�̉��z�A�h���X���
	m_pVtxBuff->Unlock();


}


