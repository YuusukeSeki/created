////*****************************************************************************
////
//// �T�E���h���� [sound.h]
//// Author : Yusuke Seki
////
////*****************************************************************************
//#ifndef _SOUND_H_
//#define _SOUND_H_
//
////----- �C���N���[�h�t�@�C��
//#include "main.h"
//
////----- �\���̂̒�`
//// �T�E���h�t�@�C��
//typedef enum
//{
//	SOUND_LABEL_BGM_TITLE01 = 0,	// BGM -- �^�C�g��
//	SOUND_LABEL_SE_CLEAR01,			// SE -- �C�x���g����
//	SOUND_LABEL_MAX,
//} SOUND_LABEL;
//// �T�E���h�p�����[�^
//typedef struct
//{
//	char *pFilename;	// �t�@�C����
//	int nCntLoop;		// ���[�v�J�E���g
//} SOUNDPARAM;
//
////----- �N���X�̒�`
//class Sound
//{
//public:
//	static HRESULT InitSound(HWND hWnd);
//	static void UninitSound(void);
//	static HRESULT PlaySound(SOUND_LABEL label);
//	static void StopSound(SOUND_LABEL label);
//	static void StopSound(void);
//	static void PlayClearSound( int arrayNum );
//	static void PlayDeathSound( int arrayNum );
//	static void SetVolume( SOUND_LABEL label , float volume );
//private:
//	static HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
//	static HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);
//	static IXAudio2					*m_pXAudio2;						// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
//	static IXAudio2MasteringVoice	*m_pMasteringVoice;					// �}�X�^�[�{�C�X
//	static IXAudio2SourceVoice		*m_apSourceVoice[SOUND_LABEL_MAX];	// �\�[�X�{�C�X
//	static BYTE						*m_apDataAudio[SOUND_LABEL_MAX];	// �I�[�f�B�I�f�[�^
//	static DWORD					m_aSizeAudio[SOUND_LABEL_MAX];		// �I�[�f�B�I�f�[�^�T�C�Y
//	static SOUNDPARAM				m_aParam[SOUND_LABEL_MAX];			// �e���f�ނ̃p�����[�^
//};
//
//#endif
