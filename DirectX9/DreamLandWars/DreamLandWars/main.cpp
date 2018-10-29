//*****************************************************************************
//	GM31 ���ƂP�R�}��
//	Author : Yusuke Seki
//*****************************************************************************

//---------- �C���N���[�h�t�@�C��
#include "main.h"
#include "GameManager.h"
#include "Title.h"
#include "MainGame.h"

//---------- �}�N����`
#define CLASS_NAME	("class name")	// �E�B���h�E�N���X�̖��O
#define WINDOW_NAME	("Dream Land Wars")	// �E�B���h�E�̖��O
#define WindowStyle		(WS_OVERLAPPEDWINDOW ^ WS_MINIMIZEBOX ^ WS_MAXIMIZEBOX ^ WS_THICKFRAME)	// �E�B���h�E�X�^�C��

//---------- �v���g�^�C�v�錾
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);	// �E�B���h�E�v���V�[�W��

//---------- �O���[�o���錾
#ifdef _DEBUG
int	g_nCountFPS	= 0;	// FPS�J�E���^�[
#endif
HWND g_hwnd;


//=============================================================================
// ���C���֐�
//=============================================================================
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	HWND hWnd;
	WNDCLASSEX wcex;
	RECT ClientRect, DesktopRect;
	int WindowWidth, WindowHeight, DesktopWidth, DesktopHeight, WindowX, WindowY;
	HRESULT hr;
	MSG msg;
	DWORD dwCountFrame, dwCurrentTime, dwFPSLastTime, dwExecLastTime;


	//----- �E�B���h�E�̍쐬 -----
	// �E�B���h�E�N���X�̐ݒ�
	wcex = { sizeof(WNDCLASSEX), CS_CLASSDC, WndProc, 0, 0, hInstance, NULL, LoadCursor(NULL,IDC_ARROW),
			 (HBRUSH)(COLOR_WINDOW+1), NULL, CLASS_NAME, NULL };
	RegisterClassEx(&wcex);

	// �N���C�A���g�̈�̐ݒ�
	ClientRect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	AdjustWindowRect( &ClientRect, WindowStyle, FALSE );
	WindowWidth  = ClientRect.right  - ClientRect.left;
	WindowHeight = ClientRect.bottom - ClientRect.top;

	// �f�X�N�g�b�v�̈�̎擾
	GetWindowRect( GetDesktopWindow(), &DesktopRect );
	DesktopWidth  = DesktopRect.right  - DesktopRect.left;
	DesktopHeight = DesktopRect.bottom - DesktopRect.top;

	// ���ۂ̃N���C�A���g�̈�̎Z�o
	WindowX = WindowWidth  > DesktopWidth  ? 0 : ( DesktopWidth  - WindowWidth  ) / 2;
	WindowY = WindowHeight > DesktopHeight ? 0 : ( DesktopHeight - WindowHeight ) / 2;

	// �E�B���h�E�̎��̉�
	hWnd = CreateWindowEx( 0, CLASS_NAME, WINDOW_NAME, WindowStyle, WindowX, WindowY,
						   WindowWidth, WindowHeight, NULL, NULL, hInstance, NULL );
	g_hwnd = hWnd;

	// �E�B���h�E�̕\��
	ShowWindow( hWnd, nCmdShow );
	UpdateWindow( hWnd );

	
	//----- �Q�[���̏����� -----
	// �Q�[���}�l�[�W���[�̏�����
	//hr = GameManager::Init(hInstance, hWnd, TRUE, new Title);
	hr = GameManager::Init(hInstance, hWnd, TRUE, new MainGame);

	// ���ʂ́H
	if (hr) { // ���s���܂���
		// �G���[���b�Z�[�W�̕\��
		_MSG("�I�����܂�");

		// �I���܂�
		return -1;
	}

	// ����\�ݒ�
	timeBeginPeriod(1);

	// FPS�ݒ�
	dwCountFrame		= 0;				// �t���[���J�E���^�[
	dwCurrentTime		= 0;				// ���ݎ���
	dwFPSLastTime		= timeGetTime();	// �Ō��FPS���X�V��������
	dwExecLastTime	= dwFPSLastTime;	// �Ō�ɃQ�[����������������

	//----- ���C�����[�v -----
	for(;;){
		// ���b�Z�[�W�̎擾
		if( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) != 0 ){	// WndProc�̐ݒ�
			if(msg.message == WM_QUIT){	// �I�����߂̎擾�ŁA���[�v�E�o
				break;
			}else{	// ���߁E�����̎擾
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		// �Q�[�����[�v
		else{
			// ���ݎ����̎擾
			dwCurrentTime = timeGetTime();
	
#ifdef _DEBUG
			// FPS�̍X�V
			if( dwCurrentTime - dwFPSLastTime >= 500 ){
				g_nCountFPS		= ( dwCountFrame * 1000 ) / ( dwCurrentTime-dwFPSLastTime );
				dwFPSLastTime	= dwCurrentTime;
				dwCountFrame	= 0;
			}
#endif
			// �Q�[������
			if((dwCurrentTime - dwExecLastTime) >= (1000/60)){
				dwExecLastTime = dwCurrentTime;

				// �X�V����
				GameManager::Update();

				// �`�揈��
				GameManager::Draw();

				dwCountFrame++;
			}// end... �Q�[������
		}// end... �Q�[�����[�v
	}// end... ���C�����[�v

	// ����\�̉��
	timeEndPeriod(1);


	//----- �Q�[���I�� -----
	GameManager::Uninit();

	return (int)msg.wParam;
}

//=============================================================================
//	�N���C�A���g�̈�̐ݒ�
//=============================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	UINT nID;	// ID�擾

	switch(uMsg)
	{
	// �E�B���h�E�N���G�C�g
	case WM_CREATE:
		break;

	// �L�[����
	case WM_KEYDOWN:
		switch(wParam){
		case VK_ESCAPE:	// ���s�t�@�C���I���m�F
			nID = MessageBox( hWnd, "�I�����܂����H" , "�I���m�F" , MB_YESNO | MB_ICONINFORMATION );
			if(nID == IDYES){ DestroyWindow(hWnd); }
			break;
		}
		break;
	
	// �I���m�F
	case WM_CLOSE:
		nID = MessageBox( hWnd, "�I�����܂����H" , "�I���m�F" , MB_YESNO | MB_ICONINFORMATION );
		if(nID != IDYES){ return 0; }
		break;

	// �I������
	case WM_DESTROY:
		PostQuitMessage(0);	// ���C�����[�v�E�o
		break;

	default:
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);	// ����̏������
}

#ifdef _DEBUG
//=============================================================================
//	FPS�擾
//=============================================================================
int GetFPS(void)
{
	return g_nCountFPS;
}
#endif


HWND GetHWnd()
{
	return g_hwnd;
}

