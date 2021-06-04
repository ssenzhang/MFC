// Hello.cpp
#include "Hello.h"

CMyApp myApp;
//////////////////////////////////////////////////////////////////////////
// CMyApp member functions

// 在应用程序生存期内InitInstance调用比较早(应用程序开始运行之后窗口创建之前)，除非InitInstance创建窗口否则应用程序不会有窗口
// 所以任何MFC程序都必须从CWinApp派生出一个类并覆盖CWinApp::InitInstance(一个虚函数，仅有一条语句，return TRUE;)；
// InitInstance目的是为应用程序提供一个自身初始化的机会，其返回值决定了框架结构接下来要执行的内容(FALSE--关闭应用程序，TRUE--继续进行)
BOOL CMyApp::InitInstance()
{
	m_pMainWnd = new CMainWindow;          // main window (usually same AfxGetApp()->m_pMainWnd) (public member variable)
	
	// 除非窗口设置WS_VISIBLE属性，否则窗口不可见，需要以下两个函数来显示
	// 注意要在程序中调用一个常规的Windows API函数，需要在函数名称前添加全局运算符::(可以确保即便同名也是调用的Windows API而非MFC成员函数)，如::UpdateWindow(hwnd);
	// 根据Windows程序设计协议，Hello把存储在应用程序对象的m_nCmdShow变量中的值传递给ShowWindow，其中保存者传递给WinMain的nCmdShow参数；
	// m_nCmdShow的值通常是SW_SHOWNORMAL，指出窗口处于正常的非最小、非最大状态；
	// 除非有特殊原因，否则InitIstance应该总是给ShowWindow传递m_nCmdWindow而非硬编码的SW_值。

	m_pMainWnd->ShowWindow(m_nCmdShow);    // Initial state of the application's window; normally, this is an argument to ShowWindow().
	m_pMainWnd->UpdateWindow();

	return TRUE;
}

// 其他可以被覆盖的虚函数，如WinHelp, ProcessWndProcException等
// 如果使用了InitIstance分配内存或资源，可以在ExitInstance释放，终止程序并清屏；其返回值是由WinMain返回的退出代码。

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

	// 客户区绘制
	CRect rect;
	GetClientRect(&rect);

	dc.DrawText(_T("Hello, MFC"), -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
}