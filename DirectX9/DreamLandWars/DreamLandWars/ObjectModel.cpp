//*****************************************************************************
//
//		���f���i���X�g�\���j
//													Autohr : Yusuke Seki
//*****************************************************************************
#include "ObjectModel.h"
#include "renderer.h"



//-----------------------------------------------------------------------------
// �R���X�g���N�^
//-----------------------------------------------------------------------------
ObjectModel::ObjectModel() : Object(Object::TYPE::TYPE_MODEL)
{
	// �����o�ϐ�������
	m_pMesh = nullptr;
	m_pMeshMat = nullptr;
	m_numMat = 0;
	ZeroMemory(&m_WorldMatrix, sizeof(m_WorldMatrix));
	m_halfSize = D3DXVECTOR3(0, 0, 0);
	m_rotate = D3DXVECTOR3(0, 0, 0);
	m_scale = D3DXVECTOR3(0, 0, 0);
	m_radius = 0.f;
	m_color.color = 0xffffffff;
	m_front = D3DXVECTOR3(0, 0, 1);
	m_pVtxBuff = nullptr;
	m_pTexture = nullptr;
	m_bUpdateVertexBuf = false;
	m_bUpdateWorldMatrix = false;
	m_bDraw = true;

}


//-----------------------------------------------------------------------------
// �R���X�g���N�^
//-----------------------------------------------------------------------------
ObjectModel::ObjectModel(Object::TYPE type) : Object(type)
{
	// �����o�ϐ�������
	m_pMesh              = nullptr;
	m_pMeshMat           = nullptr;
	m_numMat             = 0;
	ZeroMemory(&m_WorldMatrix, sizeof(m_WorldMatrix));
	m_halfSize           = D3DXVECTOR3(0, 0, 0);
	m_rotate             = D3DXVECTOR3(0, 0, 0);
	m_scale              = D3DXVECTOR3(0, 0, 0);
	m_radius             = 0.f;
	m_color.color        = 0xffffffff;
	m_front               = D3DXVECTOR3(0, 0, 1);
	m_pVtxBuff           = nullptr;
	m_pTexture           = nullptr;
	m_bUpdateVertexBuf   = false;
	m_bUpdateWorldMatrix = false;
	m_bDraw              = true;

}


//-----------------------------------------------------------------------------
// �f�X�g���N�^
//-----------------------------------------------------------------------------
ObjectModel::~ObjectModel()
{
	Uninit();

}


//-----------------------------------------------------------------------------
// ���̂̐���
//-----------------------------------------------------------------------------
ObjectModel* ObjectModel::Create(D3DXVECTOR3& position, const char* FileName)
{
	ObjectModel* pObjectModel = new ObjectModel(Object::TYPE::TYPE_MODEL);
	pObjectModel->Init(position, FileName);

	return pObjectModel;
}


//-----------------------------------------------------------------------------
// ����������
//-----------------------------------------------------------------------------
void ObjectModel::Init(D3DXVECTOR3& position, const char* FileName)
{
	// �f�[�^�̐ݒ�
	Object::SetPosition(position);					// ���W
	m_rotate             = D3DXVECTOR3(0, 0, 0);	// ��]��
	m_scale              = D3DXVECTOR3(1, 1, 1);	// �g�k��
	m_front               = D3DXVECTOR3(0, 0, 1);	// �����Ă����
	m_pTexture           = nullptr;					// �e�N�X�`��
	m_bUpdateWorldMatrix = true;					// true �Ń��[���h�}�g���N�X�̍X�V������
	m_bDraw              = true;					// true �ŕ`�揈�����s��

	// ���� �ȉ����ݓK���ɐݒ肹����𓾂Ȃ���� ����
	m_color.color        = 0xffffffff;				// �F
	m_pVtxBuff           = nullptr;					// ���_�o�b�t�@
	m_bUpdateVertexBuf   = false;					// true �Œ��_�o�b�t�@�̍X�V������


	// ���f���̓ǂݍ���
	LoadMeshModel_DX(FileName);

	// �傫���̎擾
	LoadModelSizeFromX(FileName);

}


//-----------------------------------------------------------------------------
// �I������
//-----------------------------------------------------------------------------
void ObjectModel::Uninit(void)
{
	// �e�N�X�`���̊J��
	for (int i = 0; i < (int)m_numMat; ++i) {
		if (m_pTexture[i] != nullptr)
		{
			m_pTexture[i]->Release();
			m_pTexture[i] = nullptr;
		}
	}

	// ���b�V���̊J��
	if (m_pMeshMat != nullptr) {
		delete[] m_pMeshMat;
		m_pMeshMat = nullptr;
	}

	// ���b�V���C���^�[�t�F�[�X���̊J��
	if (m_pMesh != nullptr) {
		m_pMesh->Release();
		m_pMesh = nullptr;
	}
}


//-----------------------------------------------------------------------------
// �X�V����
//-----------------------------------------------------------------------------
void ObjectModel::Update(void)
{
}


//-----------------------------------------------------------------------------
// �`�揈��
//-----------------------------------------------------------------------------
void ObjectModel::Draw(void)
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
	pDevice->SetTransform(D3DTS_WORLD, &m_WorldMatrix);

	// ���݃f�o�C�X�ɐݒ肳��Ă���}�e���A�����̎擾
	D3DMATERIAL9 matDef;
	pDevice->GetMaterial(&matDef);

	// �}�e���A�����̃|�C���^�Ƃ��ăo�b�t�@�A�h���X���擾
	for (int i = 0; i<(int)m_numMat; i++)
	{
		// �f�o�C�X�Ƀ}�e���A����ݒ�
		pDevice->SetMaterial(&m_pMeshMat[i]);

		// �e�N�X�`���̓\��t��
		pDevice->SetTexture(0, m_pTexture[i]);

		// �`��
		m_pMesh->DrawSubset(i);
	}

	// �}�e���A������������Ԃ֖߂�
	pDevice->SetMaterial(&matDef);

}



//=============================================================================
//	��������
// ���W�̈ړ�
void ObjectModel::MovePosition(D3DXVECTOR3& movePosition)
{
	// ���W�̈ړ�
	Object::MovePosition(movePosition);

	// ���[���h�}�g���N�X�̍X�V�t���OON
	m_bUpdateWorldMatrix = true;
}

// �傫���̑���
void ObjectModel::MoveSize(D3DXVECTOR3& moveSize)
{
	// �傫���̑���
	m_halfSize += moveSize * 0.5f;
	m_radius    = sqrtf(m_halfSize.x * m_halfSize.x + m_halfSize.y * m_halfSize.y);	// ���a
	
	// ���_�o�b�t�@�̍X�V�t���OON
	m_bUpdateVertexBuf = true;

}

// ��]���̑���
void ObjectModel::MoveRotate(D3DXVECTOR3& moveRotate)
{
	// ��]���̑���
	m_rotate += moveRotate;
	
	// ���[���h�}�g���N�X�̍X�V�t���OON
	m_bUpdateWorldMatrix = true;
}

// �g�k���̑���
void ObjectModel::MoveScale(D3DXVECTOR3& moveScale)
{
	// �g�k���̑���
	m_scale += moveScale;

	// ���[���h�}�g���N�X�̍X�V�t���OON
	m_bUpdateWorldMatrix = true;
}

// �F�̑���
void ObjectModel::MoveColor(int r, int g, int b, int a)
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



//=============================================================================
// �ݒ菈��
// ���W�̐ݒ�
void ObjectModel::SetPosition(D3DXVECTOR3& position)
{
	// ���W�̈ړ�
	Object::SetPosition(position);

	// ���[���h�}�g���N�X�̍X�V�t���OON
	m_bUpdateWorldMatrix = true;
}

// �傫���̐ݒ�
void ObjectModel::SetSize(D3DXVECTOR3& size)
{
	// �傫���̐ݒ�
	m_halfSize = size * 0.5f;
	m_radius   = sqrtf(m_halfSize.x * m_halfSize.x + m_halfSize.y * m_halfSize.y);	// ���a

	// ���_�o�b�t�@�̍X�V�t���OON
	m_bUpdateVertexBuf = true;

}

// ��]���̐ݒ�
void ObjectModel::SetRotate(D3DXVECTOR3& rotate)
{
	// ��]���̑���
	m_rotate = rotate;

	// ���[���h�}�g���N�X�̍X�V�t���OON
	m_bUpdateWorldMatrix = true;
}

// �g�k���̐ݒ�
void ObjectModel::SetScale(D3DXVECTOR3& scale)
{
	// �g�k���̐ݒ�
	m_scale = scale;

	// ���[���h�}�g���N�X�̍X�V�t���OON
	m_bUpdateWorldMatrix = true;
}

// �F�̐ݒ�
void ObjectModel::SetColor(unsigned int rgba)
{
	// �F�ݒ�
	m_color.color = rgba;

	// ���_�o�b�t�@�̍X�V�t���OON
	m_bUpdateVertexBuf = true;

}

// �Ώۂ̕����������悤�ɐݒ肷��
void ObjectModel::SetRotateToObj(D3DXVECTOR3& ObjectPostion)
{
	D3DXVECTOR3 targetPosition = ObjectPostion;

	// ��������Ώۂւ̃x�N�g�������
	targetPosition -= Object::GetPosition();

	// �����2D�Q�[���Ȃ̂�Y���W�͂O�œ���
	targetPosition.y = 0.f;

	// �͂��v��Ȃ��̂ŒP�ʃx�N�g����
	D3DXVec3Normalize(&targetPosition, &targetPosition);

	// ������ݒ�
	m_front = targetPosition;

	// Y���̌X�����Z�o���Đݒ�
	float angle = atan2f(targetPosition.x, targetPosition.z);
	SetRotate(D3DXVECTOR3(0, angle, 0));

}



//=============================================================================
//	private�֐�
// ���_�o�b�t�@�̐����@��������
void ObjectModel::MakeVertexBuf()
{

}

// ���_�o�b�t�@�̍X�V�@��������
void ObjectModel::UpdateVertexBuf()
{
	// ���_���擾
	int numVtx = (int)m_pMesh->GetNumVertices();

	// VRAM�̉��z�A�h���X�擾
	VERTEX_3D* pVtx;
	m_pMesh->LockVertexBuffer(0, (void**)&pVtx);

	// ���_���W�̐ݒ�


	// �@���̐ݒ�


	// ���_�F�̐ݒ�
	for (int i = 0; i < numVtx; i++) {
		pVtx[i].color = D3DCOLOR_RGBA(m_color.rgba[3], m_color.rgba[2], m_color.rgba[1], m_color.rgba[0]);
	}

	// �e�N�X�`��UV�l�̐ݒ�


	// VRAM�̉��z�A�h���X���
	m_pMesh->UnlockVertexBuffer();

	// ���_�o�b�t�@�̍X�V�t���OOFF
	m_bUpdateVertexBuf = false;

}

// ���[���h�}�g���N�X�̍X�V
void ObjectModel::UpdateWorldMatrix()
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

// ���f���f�[�^�̓ǂݍ��݁@��������
void ObjectModel::LoadModel(const char* FileName)
{
	//D3DXVECTOR3* positionArray;
	//D3DXVECTOR2* texcoordArray;
	//D3DXVECTOR3* normalArray;
	//unsigned int positionNum = 0;
	//unsigned int texcoordlNum = 0;
	//unsigned int normalNum = 0;
	//unsigned int vertexNum = 0;
	//unsigned int indexNum = 0;
	//unsigned int in = 0;
	//unsigned int subsetNum = 0;
	//char str[256];
	//char* s;
	//char c;
	//FILE* file;
	//file = fopen(modelPass, "rt");

	//// �t�@�C����������ΏI��
	//if (file == nullptr) {
	//	_MSGERROR("Failed Load Model!!", modelPass);
	//	return;
	//}

	//// ���f���̎��̐���
	//m_pModel = new MODEL;


	//// �v�f���J�E���g
	//while (true) {
	//	fscanf(file, "%s", str);

	//	// �s���Ȃ���Ηv�f���̃J�E���g���I������
	//	if (feof(file) != 0) break;

	//	// ���_���W�f�[�^�H
	//	if (strcmp(str, "v") == 0) positionNum++;
	//	// �@���f�[�^�H
	//	else if (strcmp(str, "vn") == 0) normalNum++;
	//	// SV�l�f�[�^�H
	//	else if (strcmp(str, "vt") == 0) texcoordlNum++;
	//	// �`��T�u�Z�b�g�f�[�^�H
	//	else if (strcmp(str, "usemtl") == 0) subsetNum++;
	//	// ���_�w��f�[�^�H
	//	else if (strcmp(str, "f") == 0) {
	//		in = 0;

	//		do {
	//			fscanf(file, "%s", str);

	//			// ���_������
	//			vertexNum++;
	//			in++;

	//			// �ꕶ���擾
	//			c = fgetc(file);

	//		} while (c != '\n' && c != '\r'); // ���s�Ń��[�v�I��

	//										  // �l�p�͎O�p�ɕ���
	//		if (in == 4) in = 6;

	//		// �C���f�b�N�X������
	//		indexNum += in;

	//	}
	//}

	//// �������m��
	//positionArray = new VECTOR3D[positionNum];
	//normalArray = new VECTOR3D[normalNum];
	//texcoordArray = new VECTOR2D[texcoordlNum];
	//m_pModel->VertexArray = new VERTEX_3D[vertexNum];
	//m_pModel->IndexArray = new unsigned int[indexNum];
	//m_pModel->IndexNum = indexNum;
	//m_pModel->Subset = new SUBSET[subsetNum];
	//m_pModel->SubsetNum = subsetNum;

	//// �v�f�Ǎ�
	//VECTOR3D* position = positionArray;
	//VECTOR3D* normal = normalArray;
	//VECTOR2D* texcoord = texcoordArray;
	//unsigned int vc = 0;
	//unsigned int ic = 0;
	//unsigned int sc = 0;
	//fseek(file, 0, SEEK_SET);
	//while (true) {
	//	// ��s�擾
	//	fscanf(file, "%s", str);

	//	// �I��
	//	if (feof(file) != 0) break;

	//	// 
	//	if (strcmp(str, "mtllib") == 0) {
	//		// �}�e���A���t�@�C��
	//		fscanf(file, "%s", str);

	//		char path[256];
	//		strcpy(path, "data/model/");
	//		strcat(path, str);

	//		LoadMaterial(path);
	//	}
	//	// 
	//	else if (strcmp(str, "o") == 0) {
	//		// �I�u�W�F�N�g��
	//		fscanf(file, "%s", str);
	//	}
	//	// ���W�f�[�^�̓��������_�z����`��
	//	else if (strcmp(str, "v") == 0) {
	//		// ���_���W
	//		fscanf(file, "%f", &position->x);
	//		fscanf(file, "%f", &position->y);
	//		fscanf(file, "%f", &position->z);
	//		position->x *= SCALE_MODEL;
	//		position->y *= SCALE_MODEL;
	//		position->z *= SCALE_MODEL;
	//		position++;

	//	}
	//	// �@���f�[�^
	//	else if (strcmp(str, "vn") == 0) {
	//		// �@��
	//		fscanf(file, "%f", &normal->x);
	//		fscanf(file, "%f", &normal->y);
	//		fscanf(file, "%f", &normal->z);
	//		normal++;

	//	}
	//	// �e�N�X�`���f�[�^
	//	else if (strcmp(str, "vt") == 0) {
	//		// SV�l
	//		fscanf(file, "%f", &texcoord->x);
	//		fscanf(file, "%f", &texcoord->y);
	//		texcoord++;

	//	}
	//	// 
	//	else if (strcmp(str, "usemtl") == 0) {
	//		// �}�e���A��
	//		fscanf(file, "%s", str);

	//		if (sc != 0) m_pModel->Subset[sc - 1].IndexNum = ic - m_pModel->Subset[sc - 1].StartIndex;
	//		m_pModel->Subset[sc].StartIndex = ic;

	//		for (unsigned int i = 0; i < m_MaterialNum; i++) {
	//			if (strcmp(str, m_pMaterialArray[i].Name) == 0) {
	//				m_pModel->Subset[sc].Material.Material = m_pMaterialArray[i].Material;
	//				strcpy(m_pModel->Subset[sc].Material.Name, m_pMaterialArray[i].Name);

	//				break;
	//			}
	//		}

	//		sc++;

	//	}
	//	// ���_�ԍ����������C���f�b�N�X�z��̌`��
	//	else if (strcmp(str, "f") == 0) {
	//		// ��
	//		in = 0;

	//		do {
	//			fscanf(file, "%s", str);

	//			s = strtok(str, "/");
	//			m_pModel->VertexArray[vc].Position = positionArray[atoi(s) - 1];

	//			if (s[strlen(s) + 1] != '/')
	//			{
	//				s = strtok(NULL, "/");
	//				m_pModel->VertexArray[vc].TexturePos = texcoordArray[atoi(s) - 1];
	//			}

	//			s = strtok(NULL, "/");
	//			m_pModel->VertexArray[vc].Normal = normalArray[atoi(s) - 1];

	//			m_pModel->IndexArray[ic] = vc;
	//			ic++;
	//			vc++;

	//			in++;
	//			c = fgetc(file);

	//		} while (c != '\n' && c != '\r');

	//		// �l�p�͎O�p�ɕ���
	//		if (in == 4) {
	//			m_pModel->IndexArray[ic] = vc - 4;
	//			ic++;
	//			m_pModel->IndexArray[ic] = vc - 2;
	//			ic++;

	//		}
	//	}
	//}

	//if (sc != 0) m_pModel->Subset[sc - 1].IndexNum = ic - m_pModel->Subset[sc - 1].StartIndex;

	//if (m_pMaterialArray) {
	//	delete[] m_pMaterialArray;
	//	m_pMaterialArray = NULL;
	//}

	//m_MaterialNum = 0;

}

// X�t�@�C�����烂�f���f�[�^�̃T�C�Y��ǂݍ���
void ObjectModel::LoadModelSizeFromX(const char* FileName)
{
	// �ϐ��̒�`
	unsigned int positionNum = 0;
	D3DXVECTOR3 positionMax(0, 0, 0);
	D3DXVECTOR3 positionMin(0, 0, 0);
	char str[256];
	FILE* file;
	int cntHeader = 0;
	char* s;

	// �t�@�C�����J��
	file = fopen(FileName, "rt");

	// �t�@�C����������ΏI��
	if (file == nullptr) {
		_MSGERROR("Failed Load Model Size From X File!!", FileName);
		return;
	}

	// �ő�l�ƍŏ��l�̎擾
	while (true) {
		fscanf(file, "%s", str);

		// �s���Ȃ���Ηv�f���̃J�E���g���I������
		if (feof(file) != 0) break;

		// ���_�f�[�^�̒T�m
		if (strcmp(str, "Header{") == 0) {
			cntHeader++;
		}

		// ���_�f�[�^�̒T�m
		if (strcmp(str, "Mesh") == 0 && cntHeader == 1) {
			// �ǂݔ�΂�
			fscanf(file, "%s", str);

			// �v�f���̎擾
			fscanf(file, "%d", &positionNum);

			// �ǂݔ�΂�
			fscanf(file, "%s", str);

			// ���_�f�[�^�̓Ǎ�
			for (unsigned int i = 0; i < positionNum; i++) {
				fscanf(file, "%s", str);

				D3DXVECTOR3 buf;
				s = strtok(str, ";");
				buf.x = (float)atof(s);
				s = strtok(NULL, ";");
				buf.y = (float)atof(s);
				s = strtok(NULL, ";");
				buf.z = (float)atof(s);

				// �ő�l�̍X�V
				if (positionMax.x < buf.x) positionMax.x = buf.x;
				if (positionMax.y < buf.y) positionMax.y = buf.y;
				if (positionMax.z < buf.z) positionMax.z = buf.z;

				// �ŏ��l�̍X�V
				if (positionMin.x > buf.x) positionMin.x = buf.x;
				if (positionMin.y > buf.y) positionMin.y = buf.y;
				if (positionMin.z > buf.z) positionMin.z = buf.z;

			}

			break;

		}
	}

	// �t�@�C�������
	fclose(file);

	// �傫�����擾
	m_halfSize = (positionMax - positionMin) * 0.5f;																// �����̑傫��
	//m_radius   = sqrtf(m_halfSize.x * m_halfSize.x + m_halfSize.z * m_halfSize.z);									// ���a
	m_radius   = sqrtf(m_halfSize.x * m_halfSize.x + m_halfSize.y * m_halfSize.y + m_halfSize.z * m_halfSize.z);	// ���a
	//m_radius = m_halfSize.x;

}

// �}�e���A�����̓ǂݍ��݁@��������
void ObjectModel::LoadMaterial()
{

}

// ���f���f�[�^�̓ǂݍ��݁idirectX�֗̕��֐��g�p�j
void ObjectModel::LoadMeshModel_DX(const char* modelPass)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();

	// X�t�@�C���̓ǂݍ���
	LPD3DXBUFFER pBufMat = nullptr;	// �}�e���A�����
	if (FAILED(D3DXLoadMeshFromXA(modelPass, D3DXMESH_MANAGED, pDevice, nullptr, &pBufMat, nullptr, &m_numMat, &m_pMesh))){
		_MSGERROR("Failed XFile Open!!", "modelPass");
	}

	// X�t�@�C���ɖ@�����Ȃ��ꍇ�́A�@������������
	if (!(m_pMesh->GetFVF() & D3DFVF_NORMAL)){
		ID3DXMesh* pTempMesh = nullptr;
		m_pMesh->CloneMeshFVF(m_pMesh->GetOptions(), m_pMesh->GetFVF() | D3DFVF_NORMAL, pDevice, &pTempMesh);
		D3DXComputeNormals(pTempMesh, nullptr);
		m_pMesh->Release();
		m_pMesh = pTempMesh;
	}

	// �}�e���A�����̎擾
	D3DXMATERIAL* pMat = (D3DXMATERIAL*)pBufMat->GetBufferPointer();
	m_pMeshMat = new D3DMATERIAL9[m_numMat];
	m_pTexture = new LPDIRECT3DTEXTURE9[m_numMat];

	// �}�e���A�����ƃe�N�X�`�����̕ۑ�
	for (int i = 0; i<(int)m_numMat; i++){
		m_pMeshMat[i] = pMat[i].MatD3D;
		m_pTexture[i] = nullptr;

		if (pMat[i].pTextureFilename == nullptr) continue;

		if (FAILED(D3DXCreateTextureFromFile(pDevice, pMat[i].pTextureFilename, &m_pTexture[i]))){
			_MSGERROR("Failed Load Texture!!", "pMat[i].pTextureFilename");
		}
	}

	// �������̉��
	if (pBufMat != nullptr) pBufMat->Release();

}

