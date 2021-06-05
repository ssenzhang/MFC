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

// ��Ϣӳ��(һ������Ϣ�ͳ�Ա������������ı�)
// ����ܴ��ڽ��յ���Ϣ(WM_PAINT)��MFC�������ô��ڵ���Ϣӳ�䣬������Ӧ����(OnPaint)
// ��Ϣӳ����MFC�����߳�������һ�ַ�ʽ�����ÿ����������ܽ��յ���ÿ��������Ϣ����һ�����⺯����ô����Ҫ���(?)��
// ��CCmdTarget�������κ��඼���԰�����Ϣӳ�䣻
// MFCΪִ����Ϣӳ�����ڲ������Ĺ���������ĳЩʮ�ָ��ӵĺ��У���ʹ����Ϣӳ���൱��:
// 1��DELCARE_MESSAGE_MAP����ӵ��������У�������Ϣӳ��
// 2��ͨ�����ñ�ʶ��Ϣ�ĺ���ִ����Ϣӳ�䣬��Ӧ���ཫ��BEGIN_MASSAGE_MAP��END_MASSAGE_MAP�ĵ���֮�䴦����Ϣ��
// 3����ӳ�Ա������������Ϣ

// BEGIN_MESSAGE_MAP��ʼ��Ϣӳ�䣬��ʶ��Ϣӳ����������͸���Ļ��ࡣ
// ��Ϣӳ������������Ա��������ͨ���̳������С���Ҫ�л��࣬������ܾͿ����ڱ�Ҫ�ǲ��һ������Ϣӳ�䡣
// END_MESSAGE_MAP������Ϣӳ�䣬����֮������Ϣӳ����Ŀ�����綨����Afxmsg_.h�е�ON_WM_PAINT()��
// ������Afxmsg_.h����MSDN�в�����Ҫ����Ϣ����Ӧ����Ӧ������ȷ����Ӧ�����Ĳ����ͷ���ֵ

// ����MFCû���ṩ��Ϣӳ������Ϣ������ʹ��ʹ��ON_MESSAGE()����������Ϊ��ϢID����Ӧ���Ա������ַ
// MFC�ṩ������������;����Ϣӳ��꣺
// ON_COMMAND -- ���˵�ѡ���������UI�¼�ӳ�䵽���Ա����
// ON_UPDATE_COMMAND_UI -- ���˵��������UI�������ӵ�����������Ӧ�ó����ڲ�״̬ͬ����"���´������"

BEGIN_MESSAGE_MAP(CMainWindow, CFrameWnd) 
	ON_WM_PAINT()                      // WM_PAINT����Ϣӳ���
	ON_WM_LBUTTONDOWN()
	ON_MESSAGE(WM_SETTEXT, OnSetText)  //��WM_SETTEXT��Ϣӳ�䵽OnSetText
END_MESSAGE_MAP()

CMainWindow::CMainWindow()
{
	//Create(NULL, _T("The Hello Application"));  // Create���յ�8��������6����Ĭ��ֵָ��
	/** virtual BOOL Create(
			LPCTSTR lpszClassName,                // ָ�����ڻ���WNDCLASS�������
			LPCTSTR lpszWindowName,               // ���ڱ������ı� 
			DWORD dwStyle = WS_OVERLAPPEDWINDOW,  // ָ��������ʽ(��׼��ʽ)��Ĭ��ΪWS_OVERLAPPEDWINDOW
			const RECT& rect = rectDefault,       // ָ�����ڳ�ʼλ�úͳߴ�, ָ���������ϡ�������Ļ����
			CWnd* pParentWnd = NULL,			  // != NULL for popups ָ�����ڵĸ��׻������ߣ�NULLΪ���洰��
			LPCTSTR lpszMenuName = NULL,          // ָ�����봰���йصĲ˵���NULL�����˴����޲˵�
			DWORD dwExStyle = 0,                  // ������չ��ʽ
			CCreateContext* pContext = NULL);     // ����һ��ָ��CCreateContext�ṹ��ָ�룬���ĵ�/��ͼӦ�ó������ṹ��ʼ����ܴ���ʱ�õ�
	*/
	// �޸Ĵ�����ʽ��ֹ��С����
	Create(
		NULL,
		_T("The Hello Application"),
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MAXIMIZEBOX | WS_THICKFRAME,
		CRect(500, 300, 1000, 1000)
	);
}

// ����ͨ����ӦWM_PAINT��Ϣ���л��ƣ�����Ϣ֪ͨ����Ӧ�ø��´�����
// WM_PAINT��Ϣ�����ж���ԭ���ƶ�����һ������(?)������ԭ�ȱ��ڸǵĲ�����¶���������ڵĴ�С�ı��ˡ�
// ��Ӧ�ó�������ӦWM_PAINT��Ϣ�����䴰�ڵĿͻ�������Windows���Ʒǿͻ���ʹ������Ӧ�ó������һ֧����ۡ�
void CMainWindow::OnPaint()
{
	// CPaintDC��MFC��һ���CDC������ֻ��WM_PAINT��Ϣ���������ʹ�ã���CDC��һ���������ӡ�
	// CDC���װ��Windows�豸�������Լ������˻��Ƶ���Ļ����ӡ���������豸��ʮ������Ա������
	// ��Windows�У����е�ͼ�������ͨ���豸��������ִ�У��豸����������������������Ŀ�ĵء�
	// Ӧ�ó�������ӦWM_PAINT��Ϣ���л���֮ǰ���������Windows��::BeginPaint����ȡ�豸������׼�������豸�������ڻ���;
	// ��Ӧ�ó�����ɻ���ʱ���������::EndPaint���ͷ��豸������֪ͨWindows�����Ѿ���ɣ�
	// ���Ӧ�ó��򲻵���::BeginPaint��::EndPaint����ô����Ϣ�������Ϣ������ɾ��
	// CPaintDC�����乹�캯���е���::BeginPaint�������������е���::EndPaint��ȷ��������������������
	// ��MFC��һ�㶼����ĳ�����͵�CDC��������Ļ�Ͻ��л��ƣ������뾡��OnPaint��ʹ��CPaint����
	// ���⣬��ջ�ϴ���CPaintDC����ʱ���õı��ϰ�ߣ�������OnPaint����ʱ�Զ��������ǵ�����������
	// ע�⣬�����Ҫ����new��ʵ����һ��CPaintDC���󣬵�����OPaint����֮ǰ����ɾ��������󣬷���::EndPaint�����ᱻ���ã�����Ӧ�ó���Ҳ��������ȷ�����»��ơ�
	CPaintDC dc(this);

	// �ͻ�������
	CRect rect;
	GetClientRect(&rect);    // ʹ�ÿͻ������ʼ��rect

	/** CDC::DrawText
		int DrawText(
			LPCTSTR lpszString,     // ָ�����ʾ�ַ�����ָ��
			int nCount,				// �ַ����е��ַ���(����-1������ַ�������NULL�ַ���ֹ��)
			LPRECT lpRect,			// ָ����ʽ���ε�һ��RECT�ṹ����CRect����ĵ�ַ
			UINT nFormat);			// ָ�����ѡ��ı�ǣ���DT_CENTER--ˮƽ����
	*/
	dc.DrawText(_T("Hello, MFC"), -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	// DrawText����������ȱ��ָ������Ļ�������(�����塢�ı���ɫ),
	// ��Щ������������豸���������ԣ�����ʹ��CDC��Ա����(��SlectObject, SetTextColor)������;
	// DrawTextʹ���豸�����ĵ�ǰ������ɫ������������ı���Χ���һ��Ĭ��Ϊ��ɫ�ľ��Σ�
	// ���ϵͳĬ�ϴ��ڱ�����ɫҲ�ǰ�ɫ���������þ��Σ�����뿴���þ��ο��Խ����ڱ�����ɫ��Ϊ��ɫ��

	CFont font;
	font.CreatePointFont(180, _T("Arial"));
	/**
	font.CreateFont(
		50,				// nHeight
		0,				// nWidth
		0,				// nEscapement
		0,				// nOrientation
		FW_NORMAL,		// nWeight
		FALSE,			// bItalic
		FALSE,			// bUnderline
		0,				// cStrikeOut
		ANSI_CHARSET,				// nCharSet
		OUT_DEFAULT_PRECIS,			// nOutPrecision
		CLIP_DEFAULT_PRECIS,		// nClipPrecision
		DEFAULT_QUALITY,			// nQuality
		DEFAULT_PITCH | FF_SWISS,
		_T("Arial")					// nPitchAndFamily Arial
	);
	*/
	dc.SelectObject(&font);
	dc.SetTextColor(RGB(255, 0, 0));
	dc.SetBkColor(RGB(140, 140, 140));
	int nCeterX = rect.CenterPoint().x, nCeterY = rect.CenterPoint().y;
	dc.DrawText("Hello, MFC", CRect(nCeterX-100, nCeterY - 80, nCeterX + 100, nCeterY + 80), DT_SINGLELINE | DT_CENTER /*| DT_VCENTER*/);
}

// ���ݸ���Ϣ�������Ĳ��������ڰ�����Ϣ��wParam��lParam���������Ǽ���wParam��lParam���ձ���Ҫ�ģ�
// ������ݸ�MFC��Ϣ�������Ĳ�����ʹ�ض���Ҳ�����Ͱ�ȫ��(?)
void CMainWindow::OnLButtonDown(
	UINT nFlags,     // ����ָ������Ctrl��Shift����״̬λ���
	CPoint point)    // ��ʶ��굥����λ��
{
	TCHAR buf[32] = { 0 };
	wsprintf(buf, _T("Point(%d, %d)"), point.x, point.y);
	MessageBox(buf, _T("LBUTTON DOWN"));
}

// ͨ��ON_MASSGEӳ����Ϣ
LRESULT CMainWindow::OnSetText(WPARAM wParam, LPARAM lParam)
{
	return wParam;
}


/************************************************************************
��Ϣӳ��Ĺ�����ʽ
Դ��: Afxwin.h�е�DECLARE_MESSAGE_MAP, BEGIN_MESSAGE_MAP, END_MESSAGE_MAP�Լ�Wincore.cpp�е�CWnd::WindowProc

(���ڰ汾��MFC?)
> MFC��DECLARE_MESSAGE_MAP���������������3����Ա:
	1> ��Ϊ_messageEntries��˽�е�AFX_MSGMAP_ENTRY�ṹ���飬���а�������Ϣ����Ϣ�������������������Ϣ��
	2> ��ΪmessageMap�ľ�̬AFX_MSGMAP�ṹ�����а���һ��ָ�����е�_messageEntries�����ָ���һ��ָ�������messageMap�ṹ��ָ�룻
	3> ��ΪGetMessageMap�����⺯�����ú�������messageMap�ĵ�ַ��
	����һ����̬�Ķ����Ǿ�̬���ӵ�MFC��MFCӦ�ó�������ִ����Щ��΢��ͬ��������ԭ������ͬ�ġ�
BEGIN_MESSAGE_MAP����GetMessageMap������ʵ�֣���������ʼ��messageMap�ṹ�Ĵ��룻
BEGIN_MESSAGE_MAP��END_MESSAGE_MAP֮����ֵĺ����뵽_messageEntries�����У���END_MESSAGE_MAPʹ��һ��NULL��Ŀ���������Ľ�β��

// In the class declaration
DECLARE_MESSAGE_MAP()

// In the class implementation
DEGIN_MESSAGE_MAP(CMainWindow, CFrameWnd)
	ON_WM_PAINT()
END_MESSAGE_MAP
��������Ԥ���������������Ĵ��룺��
// In the class declaration
private:
	static const AFX_MSGMAP_ENTRY _messageEntries[];\
protected:
	static const AFX_MSGMAP messageMap;
	virtual const AFX_MSGMAP * GetMessageMap() const;
// In the class implementation
const AFX_MSGMAP* CMinWindow::GetMessageMap() cosnt
{ return &CMainWindow::messageMap;}

cosnt AFX_MSGMAP CMainWindow::messageMap = {
	&CFrameWnd::messageMap,
	&CMainWindow::_messageEntries[0]
};

const AFX_MSGMAP_ENTRY CMainWindow::_messasgeEntries[] = {
	{ WM_PAINT, 0, 0, AfxSig_vv,
		(AFX_PMSG)(AFX_PMAGW)(void (CWnd::*)(void)OnPaint },
	{ 0, 0, 0, 0, AfxSig_end, (AFX_PMSG)0 }
};

ֻҪ��������ṹ��λ�ú��ʣ���ܾͿ��Ե���GetMessageMap����ȡһ��ָ��CMainWindow��messageMap�ṹ��ָ�롣
Ȼ������������_messageEntries�������鿴CMainWindow�Ƿ��д���Ϣ����������⣬
�����Ҫ������ά��һָ��CFrameWnd��messageMap�ṹ��ָ�벢�����������Ϣӳ�䡣

������ǶԵ�����һ��CMainWindow����Ϣ�ִ�ʱ���������¼�����ϸ������
Ҫ���ɴ���Ϣ����ܵ�����CMainWindow��CWnd�̳�����������WindowProc������
WindowProc����OnWndMsg����OnWndMsg�ֵ���GetMesageMap����ȡһ��ָ��CMainWindow::messageMap��ָ��
��������CMainWindow::_messageEntries����ȡһ������ϢID�뵱ǰ���ȴ��������ϢId��ƥ�����Ŀ��
����ҵ��˸���Ŀ����Ӧ��CMainWindow����(���ַ�����ϢIDһͬ�洢��_messageEntries������)�ͱ����á�
����OnWndMsg�ο�CMainWindow::messageMap���һ��ָ��CFrameWnd::messageMap��ָ�벢δ�����ظ��ù��̡�
�������û�и���Ϣ�Ĵ���������ܽ�������һ�����𣬲ο�����Ļ��࣬�൱ϵͳ�����ż̳��������ߣ�
ֱ�����ҵ���һ����Ϣ���������߽�����Ϣ���ݸ�Windows����Ĭ�ϴ���Ϊֹ��
ͼ1-5��CMainWindow����Ϣӳ����Ŀ��ʼ����ʾ��ͼ������CMainWindow����Ϣӳ�䣬���������������һ��ƥ���ض���ϢID�Ĵ��������������·����

MFC����Ϣӳ����Ƶ������൱�ڣ�������Ϣ���ӵ���Ϣ������������ʹ�����⺯����һ�ַǳ���Ч�ķ�ʽ��
���⺯���ڿռ��ϲ�����Ч����Ϊ������Ҫ������Ҽ�ʹ����еĺ���û�б����ǣ����Ҳ�������ڴ档
�෴����Ϣӳ����ʹ�õ��ڴ��������������������Ŀ�����ɱ�����
���ڳ���ԱҪִ��һ���������в�ͬ��Ϣ���͵Ĵ������Ĵ������Ƿǳ��ټ��ģ������Ϣӳ��ֻ�Ǵ�Լ��ÿ��CWndʹ��HWND��װʱ���ּ����ֽڵ��ڴ档
/************************************************************************/

/** Windows���ַ�����_T��
	Microsoft Windows 98��Microsoft Windows NTʹ�����ֲ�ͬ���ַ����������ַ����ַ�����
	Windos 98������ǰ�İ汾ʹ��8λ��ANSI�ַ�����������ACII�ַ�����
	Windows NT��Windows 2000ʹ��16λ��Unicode�ַ���������ANSI��һ��������
	Unicode�����������Է�U.S.��ĸ����ַ���
	ʹ��ASNI�ַ�����ĳ��������Windows NT��Windows 2000�����У���Unicode��������������΢��㣬��Ϊ����Ҫ��ANSI��UNICODE��ת����
	Unicode������Windows 98�����У����ǽ�ÿ�����ݸ�Windows���ַ�����Unicodeת��λANSI��

	"Hello" -- ����������ANSI�ַ�����ַ���
	L"Hello" -- ��������ʹ��Unicode�ַ�
	�������ʹ����MFC��_T�꣬_T("Hello")
	���������Ԥ����������_UNICODE����������ʹ��Unicode�ַ�������ʹ��ANSI�ַ�����
	��������ַ�����ʹ��_T�꣬��ô����ͨ������_UNICODE����һ������Ľ�������Windows NT�İ汾��
	��ʿ����������Ž�����һ����ΪUINICODE(���»���)����ط��ţ�����ѡ���ڶ�Windows API�����е�Unicode�汾��

1> ���ַ�����ΪTHAR�����������_UNICODE��TCHAR����ֵΪwchar_t�����򽫱�Ϊchar
2> ��Ҫʹ��char*����wchar_t*������TCHAR�ַ���ָ�룬��Ӧʹ��TCHAR�����߸��ѵ�LPTST(ָ��TCAHR�ַ�����ָ��)����LPCSTR(ָ��const TCHAR�ַ�����ָ��)
3> ��Ҫ��Ϊһ���ַ�ֻ��8λ����������ֽڱ�ʾ�Ļ���������ת��Ϊ���ַ���ʾ�Ļ�������С�����Խ���sizeof(TCHAR)���ֻ���������.
4> ����TCHAR�ַ�������������ANSI���ַ�����������ʹ��_tcscat������strcat��
*/