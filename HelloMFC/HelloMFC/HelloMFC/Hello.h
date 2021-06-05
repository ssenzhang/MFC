// Hello.h
//////////////////////////////////////////////////////////////////////////
/** 工程配置
	创建C++空项目，将子系统改为窗口，常规--MFC使用设置为在共享DLL中使用MFC或在静态库中使用MFC
	前者打包时MFC的DLL内容不会包含在EXE文件中，EXE文件较小；
	后者将DLL中的相关代码写进EXE文件中，文件较大，但可以在没有相关DLL的机器上运行

	MFC应用程序的核心就是基于CWinApp类的应用程序对象，CWinApp提供了消息循环来检索消息并将消息调度给应用程的窗口；
	包含一系列可被覆盖的、用来自定义应用程序行为的主要虚函数，如InitInstance；
	一旦包含afxwin.h就可以将CWinApp以及其他MFC类引入应用程序中；
	一个MFC应用程序可以有且仅有一个应用程序对象，此对象必须声明在全局范围内有效，以便它在程序开始时即在内存中被实例化。

	MFC程序并没有main或者WinMain函数，在MFC源代码文件WinMain.cpp中定义了AfxWinMain函数，在MFC中的作用相当于WinMain.
	AfxWinMain广泛使用应用程序对象，这也是应用程序对象为什么必须作为全局声明的原因，全局变量和对象在任何其他代码执行前被创建，
	在AfxMain执行之前，应用程序对象必须在内存中存在。

	MFC程序运行一开始，AfxWinMain就调用AfxInit函数来初始化主框架，并将hInstance、
	nCmdShow以及其他AfxWinMain函数参数复制给应用程序对象的数据成员，然后调用InitApplication和InitInstance。
	在MFC16位版本中，只有传递给AfxWinMain的hPrevInstance位空时才调用InitApplication，表明当前运行时应用程序的唯一实例；
	在Win32位环境下，hPrevInstance总是空的，因此主框架不必再去检查。32位应用程序能像使用InitInstance一样使用InitApplication初始化自身，
	但是InitApplication是为了保证MFC先前版本的兼容性而提供的，因此不应该在32位的Windows应用程序中使用。
	
	如果AfxWinInit, InitApplication, InitInstance返回0，则AfxWinMain将终止执行，应用程序关闭。
	当上述函数返回非0时AfxWinMan将执行以下关键步骤：
	pThread->Run();
	调用应用程序对象的Run函数，该函数执行消息循环并开始向应用程序窗口发送消息。消息循环重复执行直到WM_QUIT消息从消息队列中被检索到；
	这时Run跳出循环，并调用ExitInstance，返回到AfxWinMain，在执行最后的一些清除工作后，AfxWinMain执行return语句结束应用程序。

*/

#if _MSC_VER > 1000 
#pragma once 
#endif  

#ifndef _HELLO_H_
#define _HLLLO_H_

#undef _Win32_WINT
#define _WIN32_WINNT 0x0A00    // Windows版本号常数，不定义默认为_WIN32_WINNT_MAXVER，目前最高win10(0x0A00)

#include <afxwin.h>

// 应用程序对象，派生于CWinThread，初始化后将执行pThread->Run(见WinMain.h中AfxWinMain入口函数)
class CMyApp : public CWinApp
{
public: 
	virtual BOOL InitInstance();
};

// 框架窗口对象
class CMainWindow : public CFrameWnd
{
public:
	CMainWindow();
protected:
	// afx_msg表明这是一个消息处理程序，可以省略afx_msg，编译时它将会简化成空白；
	// afx_msg表示一个行为很像虚拟函数但却不需要虚表项的函数
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg LRESULT OnSetText(WPARAM wParam, LPARAM lParam);

	// 在类声明中通常时最后的语句，因为它使用C++关键字来指定其成员的可见度，可以在其后面插入声明其他类成员的语句，
	// 但应当使用关键字public, protected, ptrivate开头，以确保为这些成员设置可见度
	DECLARE_MESSAGE_MAP();  // protected: ...
};

#endif
