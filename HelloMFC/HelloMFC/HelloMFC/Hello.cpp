// Hello.cpp
#include "Hello.h"

CMyApp myApp;
//////////////////////////////////////////////////////////////////////////
// CMyApp member functions

// ��Ӧ�ó�����������InitInstance���ñȽ���(Ӧ�ó���ʼ����֮�󴰿ڴ���֮ǰ)������InitInstance�������ڷ���Ӧ�ó��򲻻��д���
// �����κ�MFC���򶼱����CWinApp������һ���ಢ����CWinApp::InitInstance(һ���麯��������һ����䣬return TRUE;)��
// InitInstanceĿ����ΪӦ�ó����ṩһ�������ʼ���Ļ��ᣬ�䷵��ֵ�����˿�ܽṹ������Ҫִ�е�����(FALSE--�ر�Ӧ�ó���TRUE--��������)
BOOL CMyApp::InitInstance()
{
	m_pMainWnd = new CMainWindow;          // main window (usually same AfxGetApp()->m_pMainWnd) (public member variable)
	
	// ���Ǵ�������WS_VISIBLE���ԣ����򴰿ڲ��ɼ�����Ҫ����������������ʾ
	// ע��Ҫ�ڳ����е���һ�������Windows API��������Ҫ�ں�������ǰ���ȫ�������::(����ȷ������ͬ��Ҳ�ǵ��õ�Windows API����MFC��Ա����)����::UpdateWindow(hwnd);
	// ����Windows�������Э�飬Hello�Ѵ洢��Ӧ�ó�������m_nCmdShow�����е�ֵ���ݸ�ShowWindow�����б����ߴ��ݸ�WinMain��nCmdShow������
	// m_nCmdShow��ֵͨ����SW_SHOWNORMAL��ָ�����ڴ��������ķ���С�������״̬��
	// ����������ԭ�򣬷���InitIstanceӦ�����Ǹ�ShowWindow����m_nCmdWindow����Ӳ�����SW_ֵ��

	m_pMainWnd->ShowWindow(m_nCmdShow);    // Initial state of the application's window; normally, this is an argument to ShowWindow().
	m_pMainWnd->UpdateWindow();

	return TRUE;
}

// �������Ա����ǵ��麯������WinHelp, ProcessWndProcException��
// ���ʹ����InitIstance�����ڴ����Դ��������ExitInstance�ͷţ���ֹ�����������䷵��ֵ����WinMain���ص��˳����롣

//////////////////////////////////////////////////////////////////////////
// CMainWindow Message map and member functions

BEGIN_MESSAGE_MAP(CMainWindow, CFrameWnd)
	ON_WM_PAINT()
END_MESSAGE_MAP()

CMainWindow::CMainWindow()
{
	Create(NULL, _T("The Hello Application"));
}

void CMainWindow::OnPaint()
{
	CPaintDC dc(this);

	// �ͻ�������
	CRect rect;
	GetClientRect(&rect);

	dc.DrawText(_T("Hello, MFC"), -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
}