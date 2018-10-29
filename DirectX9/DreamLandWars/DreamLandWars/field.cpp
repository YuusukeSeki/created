//*****************************************************************************
//
//		�t�B�[���h
//													Autohr : Yusuke Seki
//*****************************************************************************
#include "field.h"
#include "renderer.h"

//----- �}�N����`
//static const int   NUM_FIELD_HORIZON	= 4;												// �n�ʂ̐��i���j
//static const int   NUM_FIELD_VERTICAL	= 4;												// �n�ʂ̐��i�c�j
//static const int   NUM_FIELD			= NUM_FIELD_HORIZON * NUM_FIELD_VERTICAL;			// �n�ʂ̐��i�S�́j
//static const float FIELD_WIDTH			= ( float )FIELD_WIDTH_ALL / NUM_FIELD_HORIZON;		// �P���̕�
//static const float FIELD_HEIGHT			= ( float )FIELD_HEIGHT_ALL / NUM_FIELD_VERTICAL;	// �P���̍���
//static const int   NUM_VERTEX			= (2 + 2 * NUM_FIELD_HORIZON) * NUM_FIELD_VERTICAL + (2 * (NUM_FIELD_VERTICAL - 1));	// ���_�̐�
//static const int   NUM_POLYGON			= NUM_VERTEX - 2;									// �|���S���̐�

const float Field::FIELD_WIDTH_ALL  = 1000.0f;	// �S�̃t�B�[���h��
const float Field::FIELD_HEIGHT_ALL = 1000.0f;	// �S�̃t�B�[���h����


// �O���[�o���ϐ�
float g_FieldHeight[5][5] = {	// �t�B�[���h��Y���W
	//{ 0.0f,   0.0f,   0.0f,    0.0f, 0.0f },
	//{ 0.0f, 100.0f, 150.0f,  100.0f, 0.0f },
	//{ 0.0f, 200.0f, 300.0f,  200.0f, 0.0f },
	//{ 0.0f, 100.0f, 150.0f,  100.0f, 0.0f },
	//{ 0.0f,   0.0f,   0.0f,    0.0f, 0.0f },
	{ 0.0f,   0.0f,   0.0f,    0.0f, 0.0f },
	{ 0.0f,   0.0f,   0.0f,    0.0f, 0.0f },
	{ 0.0f,   0.0f,   0.0f,    0.0f, 0.0f },
	{ 0.0f,   0.0f,   0.0f,    0.0f, 0.0f },
	{ 0.0f,   0.0f,   0.0f,    0.0f, 0.0f },
};



//-----------------------------------------------------------------------------
//	�R���X�g���N�^
//-----------------------------------------------------------------------------
//Field::Field(int priority, TYPE type):Scene(priority, type)
Field::Field(Object::TYPE type) : Object(type)
{
	// �����o�ϐ�������
	D3DXMatrixIdentity( &m_mtxWorld );	// �s���P�ʍs��ɂ���i�S�l���P�ɂ���j
	m_rot = D3DXVECTOR3( 0, 0, 0);		// ��]��
	m_scl = D3DXVECTOR3( 0, 0, 0);		// �g�k��
	m_pVtxBuf  = nullptr;				// ���_�o�b�t�@
	m_pIdxBuf  = nullptr;				// �C���f�b�N�X�o�b�t�@
	m_pTexture = nullptr;				// �e�N�X�`��
	m_mat.Diffuse  = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// �g�U����
	m_mat.Ambient.r = m_mat.Diffuse.r * 0.4f;	        // ������
	m_mat.Ambient.g = m_mat.Diffuse.g * 0.4f;	        // �V
	m_mat.Ambient.b = m_mat.Diffuse.b * 0.4f;	        // �V
	m_mat.Ambient.a = m_mat.Diffuse.a * 0.4f;	        // �V
	m_mat.Specular = D3DXCOLOR(0.3f, 0.3f, 0.3f, 0.3f);	// ���ʔ���
	m_mat.Emissive = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);	// ���Ȕ���
	m_mat.Power = 1.0f;									// ���ʔ��˂̑N���x
	m_size = D3DXVECTOR3(0, 0, 0);
	m_numFieldHorizon = 0;
	m_numFieldVertical = 0;
}


//-----------------------------------------------------------------------------
//	�f�X�g���N�^
//-----------------------------------------------------------------------------
Field::~Field()
{
	Uninit();

}


//-----------------------------------------------------------------------------
//	����
//-----------------------------------------------------------------------------
Field* Field::Create(D3DXVECTOR3 pos , D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXVECTOR3 scl, int numFieldHorizon, int numFieldVertical)
{
	//Field* pField = new Field(1, TYPE_3D_FIELD);
	Field* pField = new Field(Object::TYPE::TYPE_3D_FIELD);
	pField->Init( pos, size, rot, scl, numFieldHorizon, numFieldVertical);

	return pField;
}


//-----------------------------------------------------------------------------
//	������
//-----------------------------------------------------------------------------
HRESULT Field::Init( D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXVECTOR3 scl, int numFieldHorizon, int numFieldVertical)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();

	// �����o�ϐ��ݒ�
	//Scene::SetPos(pos);
	Object::SetPosition(pos);
	m_size = size;                         // �傫��
	m_rot = rot;						   // ��]��
	m_scl = scl;						   // �g�k��
	m_numFieldHorizon  = numFieldHorizon;  // ���̃t�B�[���h��
	m_numFieldVertical = numFieldVertical; // �c�̃t�B�[���h��

	m_halfSize = m_size * 0.5f;

	// ���[���h�}�g���N�X�̐���
	D3DXMATRIX mtxTrans;
	D3DXMATRIX mtxRot;
	D3DXMATRIX mtxScall;
	
	// �e�s��v�Z
	D3DXMatrixIdentity( &m_mtxWorld );	// �s���P�ʍs��ɂ���i�S�l���P�ɂ���j
	D3DXMatrixScaling( &mtxScall, m_scl.x, m_scl.y, m_scl.z );					// �g�k
	D3DXMatrixTranslation( &mtxTrans , pos.x , pos.y , pos.z );					// �ړ�
	D3DXMatrixRotationYawPitchRoll( &mtxRot , m_rot.y , m_rot.x , m_rot.z );	// ��]�iy,x,z�̏��j

	// �s��̍���
	D3DXMatrixMultiply( &m_mtxWorld , &m_mtxWorld , &mtxScall );
	D3DXMatrixMultiply( &m_mtxWorld , &m_mtxWorld , &mtxRot );
	D3DXMatrixMultiply( &m_mtxWorld , &m_mtxWorld , &mtxTrans );

	// ���_�o�b�t�@�̐���
	MakeVertexBuf();

	// �C���f�b�N�X�o�b�t�@�̐���
	MakeIdxBuf();

	return S_OK;
}


//-----------------------------------------------------------------------------
//	�I��
//-----------------------------------------------------------------------------
void Field::Uninit(void)
{
	// ���_�o�b�t�@�̔j��
	if( m_pVtxBuf != nullptr){
		m_pVtxBuf->Release();
		m_pVtxBuf = nullptr;
	}

	// �C���f�b�N�X�o�b�t�@�̊J��
	if( m_pIdxBuf != nullptr){
		m_pIdxBuf->Release();
		m_pIdxBuf = nullptr;
	}

}


//-----------------------------------------------------------------------------
//	�X�V
//-----------------------------------------------------------------------------
void Field::Update(void)
{
}


//-----------------------------------------------------------------------------
//	�`��
//-----------------------------------------------------------------------------
void Field::Draw(void)
{
	// �ϐ��錾
	int numVtx = (2 + 2 * m_numFieldHorizon) * m_numFieldVertical + (2 * (m_numFieldVertical - 1)); // ���_��
	int numPolygon = numVtx - 2; // �|���S����

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();

	// �f�o�C�X�Ƀ��[���h�ϊ��s���ݒ�
	pDevice->SetTransform( D3DTS_WORLD , &m_mtxWorld );

	// �X�g���[���̐ݒ�
	pDevice->SetStreamSource( 0, m_pVtxBuf, 0, sizeof(VERTEX_3D));

	// �f�o�C�X�փC���f�b�N�X�o�b�t�@��ݒ�
	pDevice->SetIndices( m_pIdxBuf );

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF( FVF_VERTEX_3D );

	// �e�N�X�`���\��t��
	pDevice->SetTexture(0, m_pTexture->GetTexture());

	// �}�e���A�����ݒ�
	pDevice->SetMaterial( &m_mat );

	// �`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, numVtx, 0, numPolygon);
}


//-----------------------------------------------------------------------------
// ���_�o�b�t�@����
//-----------------------------------------------------------------------------
void Field::MakeVertexBuf(void)
{
	// �ϐ��錾
	VERTEX_3D* pVtx;
	int indexNum = 0;
	float fieldWidth  = m_size.x / m_numFieldHorizon;  // �t�B�[���h�P���̕�
	float fieldHeight = m_size.z / m_numFieldVertical; // �t�B�[���h�P���̍���
	int numVtx = (m_numFieldHorizon + 1) * (m_numFieldVertical + 1); // ���_��
	int numPolygon = numVtx - 2; // �|���S����
	float leftEdgeVertex_X = -m_size.x * 0.5f;	// ���[���_��X���W
	float topEdgeVertex_Z = m_size.z * 0.5f;	// ��[���_��Z���W

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();

	// ���_�o�b�t�@�̈�̐���
	if (m_pVtxBuf == NULL) {
		if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * numVtx, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D,
			D3DPOOL_MANAGED, &m_pVtxBuf, NULL))) {
			MessageBox(NULL, "���_�o�b�t�@�������s", "Field::MakeVertexBuf", MB_OK);
		}
	}

	// VRAM�̉��z�A�h���X�擾
	m_pVtxBuf->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	for (int i = 0; i < m_numFieldHorizon + 1; i++)
	{
		for (int j = 0; j < m_numFieldVertical + 1; j++)
		{
			pVtx[indexNum].pos.x = leftEdgeVertex_X + fieldWidth  * j;
			pVtx[indexNum].pos.y = g_FieldHeight[i][j];
			pVtx[indexNum].pos.z = topEdgeVertex_Z  - fieldHeight * i;
			indexNum++;
		}
	}

	// �z��ԍ��̏�����
	indexNum = 0;

	// �e�N�X�`�����W�̐ݒ�
	for (int i = 0; i < m_numFieldVertical + 1; i++)
	{
		for (int j = 0; j < m_numFieldHorizon + 1; j++)
		{
			pVtx[indexNum].tex = D3DXVECTOR2((float)j, (float)i);
			indexNum++;
		}
	}

	// �@���ƒ��_�F�̐ݒ�
	for (int i = 0; i < numVtx; i++)
	{
		// �@���̐ݒ�
		pVtx[i].normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		// ���_�F�̐ݒ�
		pVtx[i].color = D3DCOLOR_RGBA(255, 255, 255, 255);
	}

	// �@���̐ݒ�
	for(int z = 1; z < m_numFieldVertical; z++) {
		for(int x = 1; x < m_numFieldHorizon; x++) {
			// X�����̌v�Z
			D3DXVECTOR3 vx = pVtx[z * (m_numFieldVertical + 1) + x + 1].pos - pVtx[z * (m_numFieldVertical + 1) + x - 1].pos;
			D3DXVECTOR3 nx;
			nx.x = -vx.y;
			nx.y = vx.x;
			nx.z = 0.0f;

			// Z�����̌v�Z
			D3DXVECTOR3 vz = pVtx[z * (m_numFieldVertical + 1) + x - z * (m_numFieldVertical + 1)].pos 
				           - pVtx[z * (m_numFieldVertical + 1) + x + z * (m_numFieldVertical + 1)].pos;
			D3DXVECTOR3 nz;
			nz.x = 0.0f;
			nz.y = vz.z;
			nz.z = -vz.y;

			// Y�����̎Z�o
			D3DXVECTOR3 n = nx + nz;
			D3DXVec3Normalize(&n, &n);
			pVtx[z * 5 + x].normal = n;
		}
	}

	//// �@���̐ݒ�
	//D3DXVECTOR3 n(0,0,0);
	//int cnt = 0;

	//for (int z = 1; z < 4; z++) {
	//	for (int x = 1; x < 4; x++) {
	//		// X�����̌v�Z
	//		D3DXVECTOR3 vx = pVtx[z * 5 + x + 1].pos - pVtx[z * 5 + x].pos;
	//		// Z�����̌v�Z
	//		D3DXVECTOR3 vz = pVtx[z * 5 + x - z * 5].pos - pVtx[z * 5 + x].pos;
	//		// Y�����̎Z�o
	//		D3DXVECTOR3 n1;
	//		D3DXVec3Cross(&n1, &vz, &vx);

	//		//// X�����̌v�Z
	//		//D3DXVECTOR3 vx = pVtx[z * 5 + x + 1].pos - pVtx[z * 5 + x].pos;
	//		//// Z�����̌v�Z
	//		//D3DXVECTOR3 vz = pVtx[z * 5 + x - z * 5].pos - pVtx[z * 5 + x].pos;
	//		//// Y�����̎Z�o
	//		//D3DXVECTOR3 n1;
	//		//D3DXVec3Cross(&n1, &vz, &vx);
	//		// �v�Z���ʂ𑫂�
	//		n += n1;
	//		cnt++;

	//		pVtx[z * 5 + x].normal = n;
	//	}
	//}

	// VRAM�̉��z�A�h���X���
	m_pVtxBuf->Unlock();
}


//-----------------------------------------------------------------------------
// �C���f�b�N�X�o�b�t�@����
//-----------------------------------------------------------------------------
void Field::MakeIdxBuf(void)
{
	// �ϐ��錾
	WORD* pIdx;
	float fieldWidth       = m_size.x / m_numFieldHorizon;  // �t�B�[���h�P���̕�
	float fieldHeight      = m_size.z / m_numFieldVertical; // �t�B�[���h�P���̍���
	int numVtx             = (2 + 2 * m_numFieldHorizon) * m_numFieldVertical + (2 * (m_numFieldVertical - 1)); // ���_��
	int numPolygon         = numVtx - 2;                    // �|���S����
	int firstLineNumber    = m_numFieldHorizon * 2 + 3;	    // 2�s�ڂ̈�ڂ̒��_�ԍ�
	int addFirstLineNumber = m_numFieldHorizon * 2 + 4;	    // 3�s�ڈȍ~�ŏ�L�ϐ��ɑ�����鐔
	int lastLineNumber     = m_numFieldHorizon * 2 + 2;	    // �s���̂̍Ō�̒��_�ԍ�
	int addLastLineNumber  = m_numFieldHorizon * 2 + 4;	    // 2�s�ڈȍ~�ŏ�L�ϐ��ɑ�����鐔
	float leftEdgeVertex_X = -m_size.x * 0.5f;	            // ���[���_��X���W
	float topEdgeVertex_Z  = m_size.z * 0.5f;	            // ��[���_��Z���W
	int firstLineIndex     = m_numFieldHorizon + 1;	        // �܂�Ԃ����̒��_�ԍ� 

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();

	// �C���f�b�N�X�o�b�t�@�̈�̐���
	if(m_pIdxBuf == NULL){
		if (FAILED(pDevice->CreateIndexBuffer(sizeof(WORD) * numVtx, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16,
			D3DPOOL_MANAGED, &m_pIdxBuf, NULL))) {
			MessageBox(NULL, "�C���f�b�N�X�o�b�t�@�̐����Ɏ��s���܂����B", "Field::Init", MB_OK);
		}
	}

	// �C���f�b�N�X�o�b�t�@�����n���J�n
	m_pIdxBuf->Lock(0, 0, (void**)&pIdx, 0);

	// �C���f�b�N�X�����̐ݒ�
	{
		// 1�s�ڂ̍��[2���_
		pIdx[0] = firstLineIndex;
		pIdx[1] = 0;

		// �c
		for (int i = 0; i<m_numFieldVertical; i++)
		{
			// 1�s�ڂ���Ȃ���Γ_��ł�
			if (i != 0)
			{
				// 2�s�ڂ̏ꍇ
				if (i == 1)
				{
					pIdx[firstLineNumber] = firstLineIndex * 2;
					pIdx[firstLineNumber + 1] = firstLineIndex * 2;
					pIdx[firstLineNumber + 2] = firstLineIndex;
				}
				// 3�s�ڈȍ~
				else
				{
					pIdx[firstLineNumber + addFirstLineNumber * (i - 1)] = firstLineIndex * (i + 1);
					pIdx[firstLineNumber + addFirstLineNumber * (i - 1) + 1] = firstLineIndex * (i + 1);
					pIdx[firstLineNumber + addFirstLineNumber * (i - 1) + 2] = firstLineIndex * i;
				}
			}// End -- 1�s�ڂ���Ȃ��ꍇ

			 // ��
			for (int j = 0; j<m_numFieldHorizon; j++)
			{
				// 1�s�ڂ̏ꍇ
				if (i == 0)
				{
					pIdx[j * 2 + 2] = firstLineIndex + j + 1;
					pIdx[j * 2 + 3] = j + 1;
				}
				// 2�s�ڂ̏ꍇ
				else if (i == 1)
				{
					pIdx[firstLineNumber + j * 2 + 3] = firstLineIndex * 2 + 1 + j;
					pIdx[firstLineNumber + j * 2 + 4] = firstLineIndex + 1 + j;
				}
				// 3�s�ڈȍ~
				else
				{
					pIdx[firstLineNumber + addFirstLineNumber * (i - 1) + j * 2 + 3] = firstLineIndex * (i + 1) + 1 + j;
					pIdx[firstLineNumber + addFirstLineNumber * (i - 1) + j * 2 + 4] = firstLineIndex * i + 1 + j;
				}
			}// End -- ��

			 // �Ō�̍s����Ȃ���Γ_��ł�
			if (i != m_numFieldVertical - 1)
			{
				// 1�s�ڂ̏ꍇ
				if (i == 0)
				{
					pIdx[lastLineNumber] = pIdx[lastLineNumber - 1];
				}
				// 2�s�ڈȍ~
				else
				{
					pIdx[lastLineNumber + addLastLineNumber * i] = pIdx[lastLineNumber + addLastLineNumber * i - 1];
				}
			}// End -- �Ō�̍s����Ȃ��ꍇ
		}// End -- �c
	}// End -- ���_���W�̐ݒ�

	 // �C���f�b�N�X�o�b�t�@�����n���I��
	m_pIdxBuf->Unlock();
}


//-----------------------------------------------------------------------------
// �t�B�[���h�Ƃ̓����蔻��
// �Ԃ�l�Ftrue  �������Ă���t�B�[���h�̍���
//         false -1.f
//-----------------------------------------------------------------------------
float Field::GetHeight(D3DXVECTOR3 pos)
{
	// �ϐ��錾
	D3DXVECTOR3 v01, v12, v20, v0p, v1p, v2p, n;
	float c0, c1, c2;
	int indexNum = 0;
	VERTEX_3D pVertex[256];
	float leftVertex_X = -m_size.x * 0.5f;	// ���[���_��X���W
	float topVertex_Z  = m_size.z * 0.5f;	// ��[���_��Z���W
	float fieldWidth = m_size.x / m_numFieldHorizon;  // �t�B�[���h�P���̕�
	float fieldHeight = m_size.z / m_numFieldVertical; // �t�B�[���h�P���̍���

	// �t�B�[���h�̒��_���W���擾
	for (int i = 0; i <= m_numFieldVertical; i++)
	{
		for (int j = 0; j <= m_numFieldHorizon; j++)
		{
			pVertex[indexNum].pos.x = leftVertex_X + fieldWidth * j;
			pVertex[indexNum].pos.y = g_FieldHeight[i][j];
			pVertex[indexNum].pos.z = topVertex_Z - fieldHeight * i;
			indexNum++;
		}
	}

	// �����蔻��
	for (int z = 0; z < m_numFieldVertical + 1; z++) {
		for (int x = 0; x < m_numFieldHorizon + 1; x++) {
			// �����̎O�p�`
			v01 = pVertex[z * (m_numFieldHorizon + 1) + x].pos - pVertex[(z + 1) * (m_numFieldHorizon + 1) + x].pos;
			v12 = pVertex[z * (m_numFieldHorizon + 1) + (x + 1)].pos - pVertex[z * (m_numFieldHorizon + 1) + x].pos;
			v20 = pVertex[(z + 1) * (m_numFieldHorizon + 1) + x].pos - pVertex[z * (m_numFieldHorizon + 1) + (x + 1)].pos;
			v0p = pos - pVertex[(z + 1) * (m_numFieldHorizon + 1) + x].pos;
			v1p = pos - pVertex[z * (m_numFieldHorizon + 1) + x].pos;
			v2p = pos - pVertex[z * (m_numFieldHorizon + 1) + (x + 1)].pos;
			c0 = v01.x * v0p.z - v01.z * v0p.x;
			c1 = v12.x * v1p.z - v12.z * v1p.x;
			c2 = v20.x * v2p.z - v20.z * v2p.x;

			// �������Ă����獂�������߂�
			if (c0 <= 0.f && c1 <= 0.f && c2 <= 0.f) {
				D3DXVec3Cross(&n, &v01, &v12);
				pos.y = pVertex[(z + 1) * (m_numFieldHorizon + 1) + x].pos.y
					  - (n.x * (pos.x - pVertex[(z + 1) * (m_numFieldHorizon + 1) + x].pos.x)
					  +  n.z * (pos.z - pVertex[(z + 1) * (m_numFieldHorizon + 1) + x].pos.z)) / n.y;
				return pos.y;
			}// ���������߂�

			 // �E���̎O�p�`
			v01 = pVertex[z * (m_numFieldHorizon + 1) + (x + 1)].pos - pVertex[(z + 1) * (m_numFieldHorizon + 1) + x].pos;
			v12 = pVertex[(z + 1) * (m_numFieldHorizon + 1) + (x + 1)].pos - pVertex[z * (m_numFieldHorizon + 1) + (x + 1)].pos;
			v20 = pVertex[(z + 1) * (m_numFieldHorizon + 1) + x].pos - pVertex[(z + 1) * (m_numFieldHorizon + 1) + (x + 1)].pos;
			v0p = pos - pVertex[(z + 1) * (m_numFieldHorizon + 1) + x].pos;
			v1p = pos - pVertex[z * (m_numFieldHorizon + 1) + (x + 1)].pos;
			v2p = pos - pVertex[(z + 1) * (m_numFieldHorizon + 1) + (x + 1)].pos;
			c0 = v01.x * v0p.z - v01.z * v0p.x;
			c1 = v12.x * v1p.z - v12.z * v1p.x;
			c2 = v20.x * v2p.z - v20.z * v2p.x;

			// �������Ă����獂�������߂�
			if (c0 <= 0.f && c1 <= 0.f && c2 <= 0.f) {
				D3DXVec3Cross(&n, &v01, &v12);
				pos.y = pVertex[(z + 1) * (m_numFieldHorizon + 1) + x].pos.y
					  - (n.x * (pos.x - pVertex[(z + 1) * (m_numFieldHorizon + 1) + x].pos.x)
					  +  n.z * (pos.z - pVertex[(z + 1) * (m_numFieldHorizon + 1) + x].pos.z)) / n.y;
				return pos.y;
			}// ���������߂�
		}// x
	}// z

	// �������ĂȂ��ꍇ�A���̐���Ԃ�
	return -1.f;
}

