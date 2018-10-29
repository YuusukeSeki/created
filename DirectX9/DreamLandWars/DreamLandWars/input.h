//*****************************************************************************
//
//		���͏��� 
//												Author : Yusuke Seki
//*****************************************************************************
#ifndef _INPUT_H_
#define _INPUT_H_

#include "main.h"


#define _USE_KEYBOARD	// �L�[�{�[�h���g���ꍇ�̓R�����g�A�E�g���O���Ă��������B
#define _USE_MOUSE		// �}�E�X���g���ꍇ�̓R�����g�A�E�g���O���Ă��������B
#define _USE_JOYSTICK	// �W���C�X�e�B�b�N���g���ꍇ�̓R�����g�A�E�g���O���Ă��������B



class Input
{
public:
	Input(){ m_pInput = NULL; }
	~Input(){}
	static Input* Create(HINSTANCE hInstance, HWND hWnd);	// ����
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);			// ������
	void Uninit(void);										// �I��
	void Update(void);										// �X�V

private:
	static const int LIMIT_COUNT_WTRIGGER = 30;	// �_�u���N���b�N�Ɣ��肷��܂ł̃t���[����
	static const int LIMIT_COUNT_REPEAT   = 60;	// ���s�[�g��ԂɈڍs����܂ł̃t���[����
	static LPDIRECTINPUT8 m_pInput; // DirectInput�I�u�W�F�N�g�ւ̃|�C���^


#ifdef _USE_KEYBOARD
// �L�[�{�[�h
public:
	// �֐�
	bool GetKeyboardPress(int nKey);    // �����Ă����
	bool GetKeyboardTrigger(int nKey);  // �����ꂽ�u�Ԃ̂�
	bool GetKeyboardWTrigger(int nKey); // �Q��A���ŉ����ꂽ�u�Ԃ̂�
	bool GetKeyboardRepeat(int nKey);   // �h���N�G�I�ȃA��
	bool GetKeyboardRelease(int nKey);  // �����ꂽ�u�Ԃ̂�


private:
	// �萔
	static const int NUM_KEY_MAX = 256;	// �L�[�̍ő吔

	// �֐�
	HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd);
	void UninitKeyboard(void);
	void UpdateKeyboard(void);

	// �ϐ�
	LPDIRECTINPUTDEVICE8 m_pDevKeyboard;		// ���̓f�o�C�X(�L�[�{�[�h)�ւ̃|�C���^
	BYTE m_aKeyState[NUM_KEY_MAX];				// �L�[�{�[�h�̓��͏�񃏁[�N
	BYTE m_aKeyStateTrigger[NUM_KEY_MAX];		// �L�[�{�[�h�̃g���K�[��񃏁[�N
	BYTE m_aKeyStateWTrigger[NUM_KEY_MAX];		// �L�[�{�[�h�̃_�u���g���K�[��񃏁[�N
	BYTE m_aKeyStateRelease[NUM_KEY_MAX];		// �L�[�{�[�h�̃����[�X��񃏁[�N
	BYTE m_aKeyStateRepeat[NUM_KEY_MAX];		// �L�[�{�[�h�̃��s�[�g��񃏁[�N
	int	 m_aKeyStateWTriggerCnt[NUM_KEY_MAX];	// �L�[�{�[�h�̃_�u���g���K�[�J�E���^
	int	 m_aKeyStateRepeatCnt[NUM_KEY_MAX];		// �L�[�{�[�h�̃��s�[�g�J�E���^


#endif


#ifdef _USE_MOUSE
// �}�E�X
public:
	// �萔
	static const int MOUSEBUTTON_LEFT    = 0;
	static const int MOUSEBUTTON_RIGHT   = 1;
	static const int MOUSEBUTTON_CENTER  = 2;
	static const int MOUSEBUTTON_RETURN  = 3;
	static const int MOUSEBUTTON_ADVANCE = 4;

	// �֐�
	bool GetMousePress(int nKey);		// �����Ă����
	bool GetMouseTrigger(int nKey);		// �����ꂽ�u�Ԃ̂�
	bool GetMouseWTrigger(int nKey);	// �Q��A���ŉ����ꂽ�u�Ԃ̂�
	bool GetMouseRepeat(int nKey);		// �h���N�G�I�ȃA��
	bool GetMouseRelease(int nKey);		// �����ꂽ�u�Ԃ̂�


private:
	// �萔
	static const int NUM_MOUSE_MAX		 = 8;	// �}�E�X�{�^���̍ő吔

	// �֐�
	HRESULT InitMouse(HINSTANCE hInstance, HWND hWnd);
	void UninitMouse(void);
	void UpdateMouse(void);

	// �ϐ�
	LPDIRECTINPUTDEVICE8 m_pDevMouse;						// ���̓f�o�C�X(�}�E�X)�ւ̃|�C���^
	DIMOUSESTATE2 m_diMouseState;							// �}�E�X�̃v���X��񃏁[�N
	DIMOUSESTATE2 m_diMouseStateTrigger;					// �}�E�X�̃g���K�[��񃏁[�N
	DIMOUSESTATE2 m_diMouseStateWTrigger;					// �}�E�X�̃_�u���g���K�[��񃏁[�N
	DIMOUSESTATE2 m_diMouseStateRelease;					// �}�E�X�̃����[�X��񃏁[�N
	DIMOUSESTATE2 m_diMouseStateRepeat;						// �}�E�X�̃��s�[�g��񃏁[�N
	int           m_diMouseStateWTriggerCnt[NUM_MOUSE_MAX];	// �}�E�X�̃_�u���g���K�[�J�E���^
	int           m_diMouseStateRepeatCnt[NUM_MOUSE_MAX];	// �}�E�X�̃��s�[�g�J�E���^


#endif


#ifdef _USE_JOYSTICK
// �W���C�X�e�B�b�N
public:
	// �萔
	static const int JOYSTICKBUTTON001 = 0;
	static const int JOYSTICKBUTTON002 = 1;
	static const int JOYSTICKBUTTON003 = 2;
	static const int JOYSTICKBUTTON004 = 3;
	static const int JOYSTICKBUTTON005 = 4;
	static const int JOYSTICKBUTTON006 = 5;
	static const int JOYSTICKBUTTON007 = 6;
	static const int JOYSTICKBUTTON008 = 7;
	static const int JOYSTICKBUTTON009 = 8;
	static const int JOYSTICKBUTTON010 = 9;
	static const int JOYSTICKBUTTON011 = 10;
	static const int JOYSTICKBUTTON012 = 11;

	// �֐�
	D3DXVECTOR2 GetJoystickLeftAxis(void);	// ���X�e�B�b�N�̌X���l
	D3DXVECTOR2 GetJoystickRightAxis(void);	// �E�X�e�B�b�N�̌X���l
	bool GetJoystickPress(int nKey);		// �����Ă����
	bool GetJoystickTrigger(int nKey);		// �����ꂽ�u�Ԃ̂�
	bool GetJoystickWTrigger(int nKey);		// 2��A���ŉ����ꂽ�u�Ԃ̂�
	bool GetJoystickRepeat(int nKey);		// �h���N�G�I�ȃA��
	bool GetJoystickRelease(int nKey);		// �����ꂽ�u�Ԃ̂�


private:
	// �萔
	static const int NUM_JOYSTICK_MAX     = 128;	// �W���C�X�e�B�b�N�{�^���̍ő吔
	static const int JOYSTICK_BUFFER_SIZE = 100;	// �W���C�X�e�B�b�N���͂̃o�b�t�@�[�T�C�Y

	// �֐�
	HRESULT InitJoystick(HINSTANCE hInstance, HWND hWnd);
	static void UninitJoystick(void);
	void UpdateJoystick(void);
	static BOOL CALLBACK EnumJoysticksCallback(const DIDEVICEINSTANCE* pDevInstance, LPVOID lpContext);
	static BOOL CALLBACK EnumAxesCallback(LPCDIDEVICEOBJECTINSTANCE lpddoi, LPVOID lpvRef);

	// �ϐ�
	static LPDIRECTINPUTDEVICE8 m_pDevJoystick;			        // ���̓f�o�C�X(�W���C�X�e�B�b�N)�ւ̃|�C���^
	static DIDEVCAPS m_diJoystickCaps;			                // �W���C�X�e�B�b�N�̔\��
	DIJOYSTATE2	m_diJoystickState;			                    // �W���C�X�e�B�b�N�̃v���X��񃏁[�N
	DIJOYSTATE2	m_diJoystickStateTrigger;	                    // �W���C�X�e�B�b�N�̃g���K�[��񃏁[�N
	DIJOYSTATE2	m_diJoystickStateWTrigger;	                    // �W���C�X�e�B�b�N�̃_�u���g���K�[��񃏁[�N
	DIJOYSTATE2	m_diJoystickStateRelease;	                    // �W���C�X�e�B�b�N�̃����[�X��񃏁[�N
	DIJOYSTATE2	m_diJoystickStateRepeat;	                    // �W���C�X�e�B�b�N�̃��s�[�g��񃏁[�N
	int			m_diJoystickStateWTriggerCnt[NUM_JOYSTICK_MAX]; // �W���C�X�e�B�b�N�̃_�u���g���K�[�J�E���^
	int			m_diJoystickStateRepeatCnt[NUM_JOYSTICK_MAX];   // �W���C�X�e�B�b�N�̃��s�[�g�J�E���^
	bool		m_bConnectJoystick;		                        // true�̏ꍇ�A�W���C�X�e�B�b�N�ڑ��L��



#endif

};

#endif
