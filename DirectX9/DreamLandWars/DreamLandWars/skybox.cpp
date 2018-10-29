//*****************************************************************************
//
//		�X�J�C�{�b�N�X
//													Autohr : Yusuke Seki
//
//*****************************************************************************
#include "skybox.h"
#include "renderer.h"

// ���W�������Ă��c�[
//#define _USE_JPEG_



//-----------------------------------------------------------------------------
//	�R���X�g���N�^
//-----------------------------------------------------------------------------
SkyBox::SkyBox(Object::TYPE type) : Object(type)
{
	// �����o�ϐ�������
	D3DXMatrixIdentity(&m_mtxWorld); // �s���P�ʍs��ɂ���i�S�l���P�ɂ���j
	m_width = 0.f;                   // ��ӂ̒���
	m_pVtxBuff = nullptr;			 // ���_�o�b�t�@
	m_pTexture = nullptr;			 // �e�N�X�`��
}

//-----------------------------------------------------------------------------
//	�f�X�g���N�^
//-----------------------------------------------------------------------------
SkyBox::~SkyBox()
{
	Uninit();

}

//-----------------------------------------------------------------------------
//	����
//-----------------------------------------------------------------------------
SkyBox* SkyBox::Create(D3DXVECTOR3 pos, float width)
{
	SkyBox* pSkyBox = new SkyBox(Object::TYPE::TYPE_3D_SKYBOX);
	pSkyBox->Init(pos, width);

	return pSkyBox;
}

//-----------------------------------------------------------------------------
//	������
//-----------------------------------------------------------------------------
HRESULT SkyBox::Init(D3DXVECTOR3 pos, float width)
{
	// �ϐ��錾
	D3DXMATRIX mtxTrans;
	D3DXMATRIX mtxRot;
	D3DXMATRIX mtxScall;

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();

	// �����o�ϐ��ݒ�
	Object::SetPosition(pos);
	m_width = width;

	// �s��̐���
	D3DXMatrixIdentity(&m_mtxWorld);
	D3DXMatrixScaling(&mtxScall, 1.f, 1.f, 1.f);
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);
	D3DXMatrixRotationYawPitchRoll(&mtxRot, 0.f, 0.f, 0.f);

	// �s��̍���
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxScall);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ���_�o�b�t�@�̈�̐���
	MakeVertexBuf();

	// ����ɏ���������
	return S_OK;
}

//-----------------------------------------------------------------------------
//	�I��
//-----------------------------------------------------------------------------
void SkyBox::Uninit(void)
{
	// ���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL) {
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

}

//-----------------------------------------------------------------------------
//	�X�V
//-----------------------------------------------------------------------------
void SkyBox::Update(void)
{
}

//-----------------------------------------------------------------------------
//	�`��
//-----------------------------------------------------------------------------
void SkyBox::Draw(void)
{
	// �ϐ��錾
#ifdef _USE_JPEG_
	const int numPolygon = 2 * 5;
#else
	const int numPolygon = 2 * 6;
#endif

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();

	// �f�o�C�X�Ƀ��[���h�ϊ��s���ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// �X�g���[���̐ݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �e�N�X�`���\��t��
	pDevice->SetTexture(0, m_pTexture->GetTexture());

	// ���C�gOFF
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// �`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, numPolygon);

	// ���C�gON
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//-----------------------------------------------------------------------------
// ���W�̈ړ�
//-----------------------------------------------------------------------------
void SkyBox::MovePos(D3DXVECTOR3 move)
{
	// �ϐ��錾
	D3DXVECTOR3 pos;
	D3DXMATRIX mtxTrans;
	D3DXMATRIX mtxRot;
	D3DXMATRIX mtxScall;

	// ���W�̈ړ�
	Object::MovePosition(move);
	pos = Object::GetPosition();

	// �s��̐���
	D3DXMatrixIdentity(&m_mtxWorld);
	D3DXMatrixScaling(&mtxScall, 1.f, 1.f, 1.f);
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);
	D3DXMatrixRotationYawPitchRoll(&mtxRot, 0.f, 0.f, 0.f);

	// �s��̍���
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxScall);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);
}

//-----------------------------------------------------------------------------
// ���W�̐ݒ�
//-----------------------------------------------------------------------------
void SkyBox::SetPos(D3DXVECTOR3 pos)
{
	// �ϐ��錾
	D3DXMATRIX mtxTrans;
	D3DXMATRIX mtxRot;
	D3DXMATRIX mtxScall;

	// ���W�̐ݒ�
	Object::SetPosition(pos);

	// �s��̐���
	D3DXMatrixIdentity(&m_mtxWorld);
	D3DXMatrixScaling(&mtxScall, 1.f, 1.f, 1.f);
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);
	D3DXMatrixRotationYawPitchRoll(&mtxRot, 0.f, 0.f, 0.f);

	// �s��̍���
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxScall);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);
}


//-----------------------------------------------------------------------------
// ���_�o�b�t�@�̐���
//-----------------------------------------------------------------------------
void SkyBox::MakeVertexBuf()
{
	// �ϐ��錾
	D3DXVECTOR3 pos = GetPosition();
	float halfWidth = m_width * 0.5f;
#ifdef _USE_JPEG_
	const int numPolygon = 2 * 5;
	const int numVertex = 3 * 2 * 5;
	float texWidth = 1.0f / 4;
	float texHeight = 1.0f / 2;
#else
	const int numPolygon = 2 * 6;
	const int numVertex = 3 * 2 * 6;
	float texWidth = 1.0f / 4;
	float texHeight = 1.0f / 3;
#endif

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();

	// ���_�o�b�t�@�̈�̐���
	if (m_pVtxBuff == NULL) {
		if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * numVertex, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D,
			D3DPOOL_MANAGED, &m_pVtxBuff, NULL))) {
			MessageBox(NULL, "���_�o�b�t�@�������s", "SkyBox::Init", MB_OK);
		}
	}

	// ���_�o�b�t�@�̐ݒ�
	VERTEX_3D* pVtx;

	// VRAM�̉��z�A�h���X�擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

#ifdef _USE_JPEG_
	//----- ���_���W�̐ݒ� -----
	// ���
	pVtx[0].pos = D3DXVECTOR3(pos.x + halfWidth, pos.y + halfWidth, pos.z - halfWidth); // �E��
	pVtx[1].pos = D3DXVECTOR3(pos.x + halfWidth, pos.y + halfWidth, pos.z + halfWidth); // �E��
	pVtx[2].pos = D3DXVECTOR3(pos.x - halfWidth, pos.y + halfWidth, pos.z - halfWidth); // ����
	pVtx[3].pos = D3DXVECTOR3(pos.x - halfWidth, pos.y + halfWidth, pos.z - halfWidth); // ����
	pVtx[4].pos = D3DXVECTOR3(pos.x + halfWidth, pos.y + halfWidth, pos.z + halfWidth); // �E��
	pVtx[5].pos = D3DXVECTOR3(pos.x - halfWidth, pos.y + halfWidth, pos.z + halfWidth); // ����

	// �w��
	pVtx[6].pos = D3DXVECTOR3(pos.x + halfWidth, pos.y + halfWidth, pos.z + halfWidth); // �E��
	pVtx[7].pos = D3DXVECTOR3(pos.x + halfWidth, pos.y - halfWidth, pos.z + halfWidth); // �E��
	pVtx[8].pos = D3DXVECTOR3(pos.x - halfWidth, pos.y + halfWidth, pos.z + halfWidth); // ����
	pVtx[9].pos = D3DXVECTOR3(pos.x - halfWidth, pos.y + halfWidth, pos.z + halfWidth); // ����
	pVtx[10].pos = D3DXVECTOR3(pos.x + halfWidth, pos.y - halfWidth, pos.z + halfWidth); // �E��
	pVtx[11].pos = D3DXVECTOR3(pos.x - halfWidth, pos.y - halfWidth, pos.z + halfWidth); // ����

	// ����
	pVtx[12].pos = D3DXVECTOR3(pos.x - halfWidth, pos.y + halfWidth, pos.z + halfWidth); // �E��
	pVtx[13].pos = D3DXVECTOR3(pos.x - halfWidth, pos.y - halfWidth, pos.z + halfWidth); // �E��
	pVtx[14].pos = D3DXVECTOR3(pos.x - halfWidth, pos.y + halfWidth, pos.z - halfWidth); // ����
	pVtx[15].pos = D3DXVECTOR3(pos.x - halfWidth, pos.y + halfWidth, pos.z - halfWidth); // ����
	pVtx[16].pos = D3DXVECTOR3(pos.x - halfWidth, pos.y - halfWidth, pos.z + halfWidth); // �E��
	pVtx[17].pos = D3DXVECTOR3(pos.x - halfWidth, pos.y - halfWidth, pos.z - halfWidth); // ����

	// �E��
	pVtx[18].pos = D3DXVECTOR3(pos.x + halfWidth, pos.y + halfWidth, pos.z - halfWidth); // �E��
	pVtx[19].pos = D3DXVECTOR3(pos.x + halfWidth, pos.y - halfWidth, pos.z - halfWidth); // �E��
	pVtx[20].pos = D3DXVECTOR3(pos.x + halfWidth, pos.y + halfWidth, pos.z + halfWidth); // ����
	pVtx[21].pos = D3DXVECTOR3(pos.x + halfWidth, pos.y + halfWidth, pos.z + halfWidth); // ����
	pVtx[22].pos = D3DXVECTOR3(pos.x + halfWidth, pos.y - halfWidth, pos.z - halfWidth); // �E��
	pVtx[23].pos = D3DXVECTOR3(pos.x + halfWidth, pos.y - halfWidth, pos.z + halfWidth); // ����

	// ����
	pVtx[24].pos = D3DXVECTOR3(pos.x - halfWidth, pos.y + halfWidth, pos.z - halfWidth); // �E��
	pVtx[25].pos = D3DXVECTOR3(pos.x - halfWidth, pos.y - halfWidth, pos.z - halfWidth); // �E��
	pVtx[26].pos = D3DXVECTOR3(pos.x + halfWidth, pos.y + halfWidth, pos.z - halfWidth); // ����
	pVtx[27].pos = D3DXVECTOR3(pos.x + halfWidth, pos.y + halfWidth, pos.z - halfWidth); // ����
	pVtx[28].pos = D3DXVECTOR3(pos.x - halfWidth, pos.y - halfWidth, pos.z - halfWidth); // �E��
	pVtx[29].pos = D3DXVECTOR3(pos.x + halfWidth, pos.y - halfWidth, pos.z - halfWidth); // ����

	//----- �@���ƒ��_�F�̐ݒ� -----
	for (int i = 0; i < numVertex; i++) {
		pVtx[i].normal = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		pVtx[i].color = D3DCOLOR_RGBA(255, 255, 255, 255);
	}

	//----- �e�N�X�`��UV�l�̐ݒ� -----
	// ���
	pVtx[0].tex = D3DXVECTOR2(texWidth * 2, texHeight * 0); // �E��
	pVtx[1].tex = D3DXVECTOR2(texWidth * 2, texHeight * 1); // �E��
	pVtx[2].tex = D3DXVECTOR2(texWidth * 1, texHeight * 0); // ����
	pVtx[3].tex = D3DXVECTOR2(texWidth * 1, texHeight * 0); // ����
	pVtx[4].tex = D3DXVECTOR2(texWidth * 2, texHeight * 1); // �E��
	pVtx[5].tex = D3DXVECTOR2(texWidth * 1, texHeight * 1); // ����

	// �w��
	pVtx[6].tex  = D3DXVECTOR2(texWidth * 2, texHeight * 1); // �E��
	pVtx[7].tex  = D3DXVECTOR2(texWidth * 2, texHeight * 2); // �E��
	pVtx[8].tex  = D3DXVECTOR2(texWidth * 1, texHeight * 1); // ����
	pVtx[9].tex  = D3DXVECTOR2(texWidth * 1, texHeight * 1); // ����
	pVtx[10].tex = D3DXVECTOR2(texWidth * 2, texHeight * 2); // �E��
	pVtx[11].tex = D3DXVECTOR2(texWidth * 1, texHeight * 2); // ����

	// ����
	pVtx[12].tex = D3DXVECTOR2(texWidth * 1, texHeight * 1); // �E��
	pVtx[13].tex = D3DXVECTOR2(texWidth * 1, texHeight * 2); // �E��
	pVtx[14].tex = D3DXVECTOR2(texWidth * 0, texHeight * 1); // ����
	pVtx[15].tex = D3DXVECTOR2(texWidth * 0, texHeight * 1); // ����
	pVtx[16].tex = D3DXVECTOR2(texWidth * 1, texHeight * 2); // �E��
	pVtx[17].tex = D3DXVECTOR2(texWidth * 0, texHeight * 2); // ����

	// �E��
	pVtx[18].tex = D3DXVECTOR2(texWidth * 3, texHeight * 1); // �E��
	pVtx[19].tex = D3DXVECTOR2(texWidth * 3, texHeight * 2); // �E��
	pVtx[20].tex = D3DXVECTOR2(texWidth * 2, texHeight * 1); // ����
	pVtx[21].tex = D3DXVECTOR2(texWidth * 2, texHeight * 1); // ����
	pVtx[22].tex = D3DXVECTOR2(texWidth * 3, texHeight * 2); // �E��
	pVtx[23].tex = D3DXVECTOR2(texWidth * 2, texHeight * 2); // ����

	// ����
	pVtx[24].tex = D3DXVECTOR2(texWidth * 4, texHeight * 1); // �E��
	pVtx[25].tex = D3DXVECTOR2(texWidth * 4, texHeight * 2); // �E��
	pVtx[26].tex = D3DXVECTOR2(texWidth * 3, texHeight * 1); // ����
	pVtx[27].tex = D3DXVECTOR2(texWidth * 3, texHeight * 1); // ����
	pVtx[28].tex = D3DXVECTOR2(texWidth * 4, texHeight * 2); // �E��
	pVtx[29].tex = D3DXVECTOR2(texWidth * 3, texHeight * 2); // ����
#else
	//----- ���_���W�̐ݒ� -----
	// ���
	pVtx[0].pos = D3DXVECTOR3(pos.x + halfWidth, pos.y + halfWidth, pos.z - halfWidth); // �E��
	pVtx[1].pos = D3DXVECTOR3(pos.x + halfWidth, pos.y + halfWidth, pos.z + halfWidth); // �E��
	pVtx[2].pos = D3DXVECTOR3(pos.x - halfWidth, pos.y + halfWidth, pos.z - halfWidth); // ����
	pVtx[3].pos = D3DXVECTOR3(pos.x - halfWidth, pos.y + halfWidth, pos.z - halfWidth); // ����
	pVtx[4].pos = D3DXVECTOR3(pos.x + halfWidth, pos.y + halfWidth, pos.z + halfWidth); // �E��
	pVtx[5].pos = D3DXVECTOR3(pos.x - halfWidth, pos.y + halfWidth, pos.z + halfWidth); // ����

	// �w��
	pVtx[6].pos = D3DXVECTOR3(pos.x + halfWidth, pos.y + halfWidth, pos.z + halfWidth); // �E��
	pVtx[7].pos = D3DXVECTOR3(pos.x + halfWidth, pos.y - halfWidth, pos.z + halfWidth); // �E��
	pVtx[8].pos = D3DXVECTOR3(pos.x - halfWidth, pos.y + halfWidth, pos.z + halfWidth); // ����
	pVtx[9].pos = D3DXVECTOR3(pos.x - halfWidth, pos.y + halfWidth, pos.z + halfWidth); // ����
	pVtx[10].pos = D3DXVECTOR3(pos.x + halfWidth, pos.y - halfWidth, pos.z + halfWidth); // �E��
	pVtx[11].pos = D3DXVECTOR3(pos.x - halfWidth, pos.y - halfWidth, pos.z + halfWidth); // ����

	// ����
	pVtx[12].pos = D3DXVECTOR3(pos.x - halfWidth, pos.y + halfWidth, pos.z + halfWidth); // �E��
	pVtx[13].pos = D3DXVECTOR3(pos.x - halfWidth, pos.y - halfWidth, pos.z + halfWidth); // �E��
	pVtx[14].pos = D3DXVECTOR3(pos.x - halfWidth, pos.y + halfWidth, pos.z - halfWidth); // ����
	pVtx[15].pos = D3DXVECTOR3(pos.x - halfWidth, pos.y + halfWidth, pos.z - halfWidth); // ����
	pVtx[16].pos = D3DXVECTOR3(pos.x - halfWidth, pos.y - halfWidth, pos.z + halfWidth); // �E��
	pVtx[17].pos = D3DXVECTOR3(pos.x - halfWidth, pos.y - halfWidth, pos.z - halfWidth); // ����

	// �E��
	pVtx[18].pos = D3DXVECTOR3(pos.x + halfWidth, pos.y + halfWidth, pos.z - halfWidth); // �E��
	pVtx[19].pos = D3DXVECTOR3(pos.x + halfWidth, pos.y - halfWidth, pos.z - halfWidth); // �E��
	pVtx[20].pos = D3DXVECTOR3(pos.x + halfWidth, pos.y + halfWidth, pos.z + halfWidth); // ����
	pVtx[21].pos = D3DXVECTOR3(pos.x + halfWidth, pos.y + halfWidth, pos.z + halfWidth); // ����
	pVtx[22].pos = D3DXVECTOR3(pos.x + halfWidth, pos.y - halfWidth, pos.z - halfWidth); // �E��
	pVtx[23].pos = D3DXVECTOR3(pos.x + halfWidth, pos.y - halfWidth, pos.z + halfWidth); // ����

	// ����
	pVtx[24].pos = D3DXVECTOR3(pos.x - halfWidth, pos.y + halfWidth, pos.z - halfWidth); // �E��
	pVtx[25].pos = D3DXVECTOR3(pos.x - halfWidth, pos.y - halfWidth, pos.z - halfWidth); // �E��
	pVtx[26].pos = D3DXVECTOR3(pos.x + halfWidth, pos.y + halfWidth, pos.z - halfWidth); // ����
	pVtx[27].pos = D3DXVECTOR3(pos.x + halfWidth, pos.y + halfWidth, pos.z - halfWidth); // ����
	pVtx[28].pos = D3DXVECTOR3(pos.x - halfWidth, pos.y - halfWidth, pos.z - halfWidth); // �E��
	pVtx[29].pos = D3DXVECTOR3(pos.x + halfWidth, pos.y - halfWidth, pos.z - halfWidth); // ����

	// ����
	pVtx[30].pos = D3DXVECTOR3(pos.x + halfWidth, pos.y - halfWidth, pos.z + halfWidth); // �E��
	pVtx[31].pos = D3DXVECTOR3(pos.x + halfWidth, pos.y - halfWidth, pos.z - halfWidth); // �E��
	pVtx[32].pos = D3DXVECTOR3(pos.x - halfWidth, pos.y - halfWidth, pos.z + halfWidth); // ����
	pVtx[33].pos = D3DXVECTOR3(pos.x - halfWidth, pos.y - halfWidth, pos.z + halfWidth); // ����
	pVtx[34].pos = D3DXVECTOR3(pos.x + halfWidth, pos.y - halfWidth, pos.z - halfWidth); // �E��
	pVtx[35].pos = D3DXVECTOR3(pos.x - halfWidth, pos.y - halfWidth, pos.z - halfWidth); // ����

	//----- �@���ƒ��_�F�̐ݒ� -----
	for (int i = 0; i < numVertex; i++) {
		pVtx[i].normal = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		pVtx[i].color = D3DCOLOR_RGBA(255, 255, 255, 255);
	}

	//----- �e�N�X�`��UV�l�̐ݒ� -----
	// ���
	pVtx[0].tex = D3DXVECTOR2(texWidth * 2, texHeight * 0); // �E��
	pVtx[1].tex = D3DXVECTOR2(texWidth * 2, texHeight * 1); // �E��
	pVtx[2].tex = D3DXVECTOR2(texWidth * 1, texHeight * 0); // ����
	pVtx[3].tex = D3DXVECTOR2(texWidth * 1, texHeight * 0); // ����
	pVtx[4].tex = D3DXVECTOR2(texWidth * 2, texHeight * 1); // �E��
	pVtx[5].tex = D3DXVECTOR2(texWidth * 1, texHeight * 1); // ����

	// �w��
	pVtx[6].tex  = D3DXVECTOR2(texWidth * 2, texHeight * 1); // �E��
	pVtx[7].tex  = D3DXVECTOR2(texWidth * 2, texHeight * 2); // �E��
	pVtx[8].tex  = D3DXVECTOR2(texWidth * 1, texHeight * 1); // ����
	pVtx[9].tex  = D3DXVECTOR2(texWidth * 1, texHeight * 1); // ����
	pVtx[10].tex = D3DXVECTOR2(texWidth * 2, texHeight * 2); // �E��
	pVtx[11].tex = D3DXVECTOR2(texWidth * 1, texHeight * 2); // ����

	// ����
	pVtx[12].tex = D3DXVECTOR2(texWidth * 1, texHeight * 1); // �E��
	pVtx[13].tex = D3DXVECTOR2(texWidth * 1, texHeight * 2); // �E��
	pVtx[14].tex = D3DXVECTOR2(texWidth * 0, texHeight * 1); // ����
	pVtx[15].tex = D3DXVECTOR2(texWidth * 0, texHeight * 1); // ����
	pVtx[16].tex = D3DXVECTOR2(texWidth * 1, texHeight * 2); // �E��
	pVtx[17].tex = D3DXVECTOR2(texWidth * 0, texHeight * 2); // ����

	// �E��
	pVtx[18].tex = D3DXVECTOR2(texWidth * 3, texHeight * 1); // �E��
	pVtx[19].tex = D3DXVECTOR2(texWidth * 3, texHeight * 2); // �E��
	pVtx[20].tex = D3DXVECTOR2(texWidth * 2, texHeight * 1); // ����
	pVtx[21].tex = D3DXVECTOR2(texWidth * 2, texHeight * 1); // ����
	pVtx[22].tex = D3DXVECTOR2(texWidth * 3, texHeight * 2); // �E��
	pVtx[23].tex = D3DXVECTOR2(texWidth * 2, texHeight * 2); // ����

	// ����
	pVtx[24].tex = D3DXVECTOR2(texWidth * 4, texHeight * 1); // �E��
	pVtx[25].tex = D3DXVECTOR2(texWidth * 4, texHeight * 2); // �E��
	pVtx[26].tex = D3DXVECTOR2(texWidth * 3, texHeight * 1); // ����
	pVtx[27].tex = D3DXVECTOR2(texWidth * 3, texHeight * 1); // ����
	pVtx[28].tex = D3DXVECTOR2(texWidth * 4, texHeight * 2); // �E��
	pVtx[29].tex = D3DXVECTOR2(texWidth * 3, texHeight * 2); // ����

	// ����
	pVtx[30].tex = D3DXVECTOR2(texWidth * 2, texHeight * 2); // �E��
	pVtx[31].tex = D3DXVECTOR2(texWidth * 2, texHeight * 3); // �E��
	pVtx[32].tex = D3DXVECTOR2(texWidth * 1, texHeight * 2); // ����
	pVtx[33].tex = D3DXVECTOR2(texWidth * 1, texHeight * 2); // ����
	pVtx[34].tex = D3DXVECTOR2(texWidth * 2, texHeight * 3); // �E��
	pVtx[35].tex = D3DXVECTOR2(texWidth * 1, texHeight * 3); // ����
#endif

	// VRAM�̉��z�A�h���X���
	m_pVtxBuff->Unlock();
}