//*****************************************************************************
//
//		���f��
//													Autohr : Yusuke Seki
//*****************************************************************************
#include "sceneModel.h"
#include "renderer.h"



//-----------------------------------------------------------------------------
// �R���X�g���N�^
//-----------------------------------------------------------------------------
SceneModel::SceneModel(int priority, TYPE type) : Scene(priority, type)
{
	// �����o�ϐ�������
	D3DXMatrixIdentity( &m_mtxWorld );
	D3DXQuaternionIsIdentity(&m_quaternion);
	m_rot = m_scl = D3DXVECTOR3( 0, 0, 0 );
	m_pMesh		= nullptr;
	m_pBufMat	= nullptr;
	m_numMat	= 0;
	m_pMeshMat	= nullptr;
	m_pTexture	= nullptr;

	m_vecZ = D3DXVECTOR3(0.f, 0.f, 1.f);

}


//-----------------------------------------------------------------------------
// �f�X�g���N�^
//-----------------------------------------------------------------------------
SceneModel::~SceneModel()
{
	// �e�N�X�`���̊J��
	for( int i = 0; i < (int)m_numMat; ++i ){
		if( m_pTexture[i] != nullptr )
		{
			m_pTexture[i]->Release();
			m_pTexture[i] = nullptr;
		}
	}

	// ���b�V���̊J��
	if( m_pMeshMat != nullptr ){
		delete [] m_pMeshMat;
		m_pMeshMat = nullptr;
	}

	// �}�e���A���̊J��
	if( m_pBufMat != nullptr ){
		m_pBufMat->Release();
		m_pBufMat = nullptr;
	}

	// ���b�V���C���^�[�t�F�[�X���̊J��
	if( m_pMesh != nullptr ){
		m_pMesh->Release();
		m_pMesh = nullptr;
	}
}


//-----------------------------------------------------------------------------
// ���̂̐���
//-----------------------------------------------------------------------------
SceneModel* SceneModel::Create( D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, const char* modelPass )
{
	SceneModel* pSceneModel = new SceneModel(0, TYPE_MODEL);
	pSceneModel->Init( pos, rot, scl, modelPass );

	return pSceneModel;
}


//-----------------------------------------------------------------------------
// ����������
//-----------------------------------------------------------------------------
HRESULT SceneModel::Init( D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, const char* modelPass )
{
	Scene::SetPos(pos);
	D3DXQuaternionIdentity(&m_quaternion);
	m_rot = rot;
	m_scl = scl;

	
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();

	// X�t�@�C���̓ǂݍ���
	if(FAILED(D3DXLoadMeshFromXA(modelPass, D3DXMESH_MANAGED, pDevice, nullptr, &m_pBufMat, nullptr, &m_numMat, &m_pMesh)))
	{
		MessageBox( nullptr , modelPass , "Xfile OpenError!" , MB_OK );
		return E_FAIL;
	}

	// X�t�@�C���ɖ@�����Ȃ��ꍇ�́A�@������������
	if ( !( m_pMesh->GetFVF() & D3DFVF_NORMAL ) )
	{
		ID3DXMesh* pTempMesh = nullptr;
		
		m_pMesh->CloneMeshFVF( m_pMesh->GetOptions(), m_pMesh->GetFVF() | D3DFVF_NORMAL, pDevice, &pTempMesh );
	
		D3DXComputeNormals(pTempMesh, nullptr);
		m_pMesh->Release();
		m_pMesh = pTempMesh;
	}
	
	//// ���a�̎Z�o
	//LPDIRECT3DVERTEXBUFFER9 pVtxBuf;
	//float max = 0.f;
	//float min = 0.f;
	//VERTEX_3D* pVtx;
	//int numVtx = m_pMesh->GetNumVertices();
	//m_pMesh->GetVertexBuffer(&pVtxBuf);

	////pVtxBuf->Lock(0, 0, (void**)pVtx, 0);

	////for (int i = 0; i < numVtx; i++) {
	////	D3DXVECTOR3 pos = pVtx[i].pos;
	////	if (min > pVtx->pos.x) min = pVtx[i].pos.x;
	////	if (max < pVtx->pos.x) max = pVtx[i].pos.x;
	////}

	////pVtxBuf->Unlock();

	////m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)pVtx);

	////for (int i = 0; i < numVtx; i++) {
	////	D3DXVECTOR3 pos = pVtx[i].pos;
	////	if (min > pVtx->pos.x) min = pVtx[i].pos.x;
	////	if (max < pVtx->pos.x) max = pVtx[i].pos.x;
	////}

	////m_pMesh->UnlockVertexBuffer();

	//m_radius = (max - min) / 2;


	// �}�e���A�����̎擾
	D3DXMATERIAL* pMat = ( D3DXMATERIAL* )m_pBufMat->GetBufferPointer();
	m_pMeshMat = new D3DMATERIAL9[ m_numMat ];
	m_pTexture = new LPDIRECT3DTEXTURE9[ m_numMat ];


	for( int i=0; i<(int)m_numMat; i++ )
	{
		m_pMeshMat[i] = pMat[i].MatD3D;
		m_pTexture[i] = nullptr;

		if (pMat[i].pTextureFilename == nullptr) continue;

		if( FAILED( D3DXCreateTextureFromFile( pDevice, pMat[i].pTextureFilename, &m_pTexture[i] )))
		{
			MessageBox( nullptr, pMat[i].pTextureFilename, "�e�N�X�`���̓ǂݍ��݂Ɏ��s���܂���" , MB_OK );
		}
	}

	return S_OK;
}


//-----------------------------------------------------------------------------
// �I������
//-----------------------------------------------------------------------------
void SceneModel::Uninit(void)
{
	// �e�N�X�`���̊J��
	for( int i = 0; i < (int)m_numMat; ++i ){
		if( m_pTexture[i] != nullptr )
		{
			m_pTexture[i]->Release();
			m_pTexture[i] = nullptr;
		}
	}

	// ���b�V���̊J��
	if( m_pMeshMat != nullptr ){
		delete [] m_pMeshMat;
		m_pMeshMat = nullptr;
	}

	// �}�e���A���̊J��
	if( m_pBufMat != nullptr ){
		m_pBufMat->Release();
		m_pBufMat = nullptr;
	}

	// ���b�V���C���^�[�t�F�[�X���̊J��
	if( m_pMesh != nullptr ){
		m_pMesh->Release();
		m_pMesh = nullptr;
	}
}


//-----------------------------------------------------------------------------
// �X�V����
//-----------------------------------------------------------------------------
void SceneModel::Update(void)
{
}


//-----------------------------------------------------------------------------
// �`�揈��
//-----------------------------------------------------------------------------
void SceneModel::Draw(void)
{
	// ���[���h�}�g���N�X�̐���
	D3DXMATRIX mtxTrans, mtxRot, mtxScl;
	D3DXVECTOR3 pos = GetPos();

	// �s��̌v�Z
	D3DXMatrixScaling(&mtxScl, m_scl.x, m_scl.y, m_scl.z);
	//D3DXMatrixRotationQuaternion(&mtxRot, &m_quaternion);
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);

	// �s��̍���
	D3DXMatrixIdentity(&m_mtxWorld);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxScl);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();

	// �f�o�C�X�Ƀ��[���h�ϊ��s���ݒ�
	Renderer::GetDevice()->SetTransform( D3DTS_WORLD , &m_mtxWorld );

	// ���݃f�o�C�X�ɐݒ肳��Ă���}�e���A�����̎擾
	D3DMATERIAL9 matDef;
	pDevice->GetMaterial( &matDef );

	// �}�e���A�����̃|�C���^�Ƃ��ăo�b�t�@�A�h���X���擾
	for( int i=0; i<(int)m_numMat; i++ )
	{
		// �f�o�C�X�Ƀ}�e���A����ݒ�
		pDevice->SetMaterial( &m_pMeshMat[i] );

		// �e�N�X�`���̓\��t��
		pDevice->SetTexture( 0 , m_pTexture[i] );

		// �`��
		m_pMesh->DrawSubset( i );
	}

	// �}�e���A������������Ԃ֖߂�
	pDevice->SetMaterial( &matDef );

}


//-----------------------------------------------------------------------------
// 
//-----------------------------------------------------------------------------
void SceneModel::MoveQuaternion(float move)
{
	D3DXQUATERNION quaternion;

	D3DXQuaternionRotationAxis(&quaternion, &D3DXVECTOR3(0.f, 1.f, 0.f), move);
	D3DXQuaternionMultiply(&m_quaternion, &quaternion, &m_quaternion);

}


//-----------------------------------------------------------------------------
// 
//-----------------------------------------------------------------------------
void SceneModel::MoveQuaternion(D3DXVECTOR3 vec, float move)
{
	D3DXQUATERNION quaternion;

	D3DXQuaternionRotationAxis(&quaternion, &vec, move);
	D3DXQuaternionMultiply(&m_quaternion, &quaternion, &m_quaternion);

}


//-----------------------------------------------------------------------------
// �F�̐ݒ�
//-----------------------------------------------------------------------------
void SceneModel::SetColor(int a, int r, int g, int b)
{
	VERTEX_3D* pVtx;
	int numVtx = (int)m_pMesh->GetNumVertices();

	m_pMesh->LockVertexBuffer(0, (void**)&pVtx);

	for (int i = 0; i < numVtx; i++) {
		pVtx[i].color = D3DCOLOR_RGBA(r, g, b, a);
	}

	m_pMesh->UnlockVertexBuffer();

}


//-----------------------------------------------------------------------------
// 
//-----------------------------------------------------------------------------
void SceneModel::SetRotateToObj(D3DXVECTOR3 objPos)
{
	float angle;

	objPos -= GetPos();
	objPos.y = 0.f;
	D3DXVec3Normalize(&objPos, &objPos);
	m_vecZ = objPos;
	angle = atan2f(objPos.x, objPos.z);
	SetRotate(D3DXVECTOR3(0, angle, 0));

}


