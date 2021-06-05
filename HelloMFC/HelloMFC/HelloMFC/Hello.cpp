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

// 消息映射(一个将消息和成员函数互相关联的表)
// 当框架窗口接收到消息(WM_PAINT)，MFC将搜索该窗口的消息映射，调用响应函数(OnPaint)
// 消息映射是MFC避免冗长的虚表的一种方式，如果每个类对它可能接收到的每个可能消息都有一个虚拟函数那么就需要虚表(?)。
// 从CCmdTarget派生的任何类都可以包含消息映射；
// MFC为执行消息映射在内部所做的工作隐藏在某些十分复杂的宏中，但使用消息映射相当简单:
// 1，DELCARE_MESSAGE_MAP宏添加到类声明中，声明消息映射
// 2，通过放置标识消息的宏来执行消息映射，相应的类将在BEGIN_MASSAGE_MAP和END_MASSAGE_MAP的调用之间处理消息。
// 3，添加成员函数来处理消息

// BEGIN_MESSAGE_MAP开始消息映射，标识消息映射所属的类和该类的基类。
// 消息映射就像其他类成员那样可以通过继承来传承。需要有基类，这样框架就可以在必要是查找基类的消息映射。
// END_MESSAGE_MAP结束消息映射，它们之间是消息映射条目。比如定义在Afxmsg_.h中的ON_WM_PAINT()宏
// 可以在Afxmsg_.h或者MSDN中查找需要的消息及对应的响应函数，确定响应函数的参数和返回值

// 处理MFC没有提供消息映射宏的消息，可以使用使用ON_MESSAGE()，两个参数为消息ID、对应类成员函数地址
// MFC提供的其他特殊用途的消息映射宏：
// ON_COMMAND -- 将菜单选择和其他的UI事件映射到类成员函数
// ON_UPDATE_COMMAND_UI -- 将菜单项和其他UI对象连接到保持他们与应用程序内部状态同步的"更新处理程序"

BEGIN_MESSAGE_MAP(CMainWindow, CFrameWnd) 
	ON_WM_PAINT()                      // WM_PAINT的消息映射宏
	ON_WM_LBUTTONDOWN()
	ON_MESSAGE(WM_SETTEXT, OnSetText)  //将WM_SETTEXT消息映射到OnSetText
END_MESSAGE_MAP()

CMainWindow::CMainWindow()
{
	//Create(NULL, _T("The Hello Application"));  // Create接收的8个参数中6个由默认值指定
	/** virtual BOOL Create(
			LPCTSTR lpszClassName,                // 指定窗口基于WNDCLASS类的名称
			LPCTSTR lpszWindowName,               // 窗口标题栏文本 
			DWORD dwStyle = WS_OVERLAPPEDWINDOW,  // 指定窗口样式(标准样式)，默认为WS_OVERLAPPEDWINDOW
			const RECT& rect = rectDefault,       // 指定窗口初始位置和尺寸, 指定窗口左上、右下屏幕坐标
			CWnd* pParentWnd = NULL,			  // != NULL for popups 指定窗口的父亲或所有者，NULL为桌面窗口
			LPCTSTR lpszMenuName = NULL,          // 指定于与窗口有关的菜单，NULL表明此窗口无菜单
			DWORD dwExStyle = 0,                  // 窗口扩展样式
			CCreateContext* pContext = NULL);     // 包含一个指向CCreateContext结构的指针，在文档/视图应用程序主结构初始化框架窗口时用到
	*/
	// 修改窗口样式禁止最小化，
	Create(
		NULL,
		_T("The Hello Application"),
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MAXIMIZEBOX | WS_THICKFRAME,
		CRect(500, 300, 1000, 1000)
	);
}

// 程序通过响应WM_PAINT消息进行绘制，此消息通知程序应该更新窗口了
// WM_PAINT消息发生有多种原因：移动了另一个窗口(?)；窗口原先被遮盖的部分显露出来；窗口的大小改变了。
// 由应用程序负责响应WM_PAINT消息绘制其窗口的客户区，由Windows绘制非客户区使得所有应用程序具有一支的外观、
void CMainWindow::OnPaint()
{
	// CPaintDC由MFC更一般的CDC派生，只在WM_PAINT消息处理程序中使用，是CDC的一个特殊例子。
	// CDC类封装了Windows设备环境，以及包含了绘制到屏幕、打印机和其他设备的十几个成员函数。
	// 在Windows中，所有的图形输出都通过设备环境对象执行，设备环境对象抽象了输出的物理目的地。
	// 应用程序在响应WM_PAINT消息进行绘制之前，必须调用Windows的::BeginPaint来获取设备环境以准备将此设备环境用于绘制;
	// 当应用程序完成绘制时，必须调用::EndPaint来释放设备环境和通知Windows绘制已经完成；
	// 如果应用程序不调用::BeginPaint和::EndPaint，那么该消息不会从消息队列中删除
	// CPaintDC将从其构造函数中调用::BeginPaint，从析构函数中调用::EndPaint来确保不会出现这样的情况。
	// 在MFC中一般都是用某种类型的CDC对象在屏幕上进行绘制，但必须尽在OnPaint中使用CPaint对象。
	// 此外，在栈上创建CPaintDC对象时良好的编程习惯，这样当OnPaint结束时自动调用他们的析构函数。
	// 注意，如果需要可以new来实例化一个CPaintDC对象，但是在OPaint结束之前比须删除这个对象，否则::EndPaint将不会被调用，而且应用程序也将不能正确地重新绘制。
	CPaintDC dc(this);

	// 客户区绘制
	CRect rect;
	GetClientRect(&rect);    // 使用客户区标初始化rect

	/** CDC::DrawText
		int DrawText(
			LPCTSTR lpszString,     // 指向待显示字符串的指针
			int nCount,				// 字符串中的字符数(或者-1，如果字符串事宜NULL字符终止的)
			LPRECT lpRect,			// 指定格式矩形的一个RECT结构或者CRect对象的地址
			UINT nFormat);			// 指定输出选项的标记，如DT_CENTER--水平居中
	*/
	dc.DrawText(_T("Hello, MFC"), -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	// DrawText参数中明显缺少指定输出的基本属性(如字体、文本颜色),
	// 这些输出特征都是设备环境的属性，可以使用CDC成员函数(如SlectObject, SetTextColor)来控制;
	// DrawText使用设备环境的当前背景颜色在它所输出的文本周围填充一个默认为白色的矩形，
	// 如果系统默认窗口背景颜色也是白色将看不到该矩形，如果想看到该矩形可以将窗口背景颜色改为灰色。

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

// 传递给消息处理程序的参数来自于伴随消息的wParam和lParam参数，但是鉴于wParam和lParam是普遍需要的，
// 因而传递给MFC消息处理程序的参数即使特定的也是类型安全的(?)
void CMainWindow::OnLButtonDown(
	UINT nFlags,     // 包含指定鼠标和Ctrl及Shift键的状态位标记
	CPoint point)    // 标识鼠标单击的位置
{
	TCHAR buf[32] = { 0 };
	wsprintf(buf, _T("Point(%d, %d)"), point.x, point.y);
	MessageBox(buf, _T("LBUTTON DOWN"));
}

// 通过ON_MASSGE映射消息
LRESULT CMainWindow::OnSetText(WPARAM wParam, LPARAM lParam)
{
	return wParam;
}