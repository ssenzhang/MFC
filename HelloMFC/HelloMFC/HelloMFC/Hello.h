// Hello.h
//////////////////////////////////////////////////////////////////////////
/** ��������
	����C++����Ŀ������ϵͳ��Ϊ���ڣ�����--MFCʹ������Ϊ�ڹ���DLL��ʹ��MFC���ھ�̬����ʹ��MFC
	ǰ�ߴ��ʱMFC��DLL���ݲ��������EXE�ļ��У�EXE�ļ���С��
	���߽�DLL�е���ش���д��EXE�ļ��У��ļ��ϴ󣬵�������û�����DLL�Ļ���������

	MFCӦ�ó���ĺ��ľ��ǻ���CWinApp���Ӧ�ó������CWinApp�ṩ����Ϣѭ����������Ϣ������Ϣ���ȸ�Ӧ�ó̵Ĵ��ڣ�
	����һϵ�пɱ����ǵġ������Զ���Ӧ�ó�����Ϊ����Ҫ�麯������InitInstance��
	һ������afxwin.h�Ϳ��Խ�CWinApp�Լ�����MFC������Ӧ�ó����У�
	һ��MFCӦ�ó���������ҽ���һ��Ӧ�ó�����󣬴˶������������ȫ�ַ�Χ����Ч���Ա����ڳ���ʼʱ�����ڴ��б�ʵ������

	MFC����û��main����WinMain��������MFCԴ�����ļ�WinMain.cpp�ж�����AfxWinMain��������MFC�е������൱��WinMain.
	AfxWinMain�㷺ʹ��Ӧ�ó��������Ҳ��Ӧ�ó������Ϊʲô������Ϊȫ��������ԭ��ȫ�ֱ����Ͷ������κ���������ִ��ǰ��������
	��AfxMainִ��֮ǰ��Ӧ�ó������������ڴ��д��ڡ�

	MFC��������һ��ʼ��AfxWinMain�͵���AfxInit��������ʼ������ܣ�����hInstance��
	nCmdShow�Լ�����AfxWinMain�����������Ƹ�Ӧ�ó����������ݳ�Ա��Ȼ�����InitApplication��InitInstance��
	��MFC16λ�汾�У�ֻ�д��ݸ�AfxWinMain��hPrevInstanceλ��ʱ�ŵ���InitApplication��������ǰ����ʱӦ�ó����Ψһʵ����
	��Win32λ�����£�hPrevInstance���ǿյģ��������ܲ�����ȥ��顣32λӦ�ó�������ʹ��InitInstanceһ��ʹ��InitApplication��ʼ������
	����InitApplication��Ϊ�˱�֤MFC��ǰ�汾�ļ����Զ��ṩ�ģ���˲�Ӧ����32λ��WindowsӦ�ó�����ʹ�á�
	
	���AfxWinInit, InitApplication, InitInstance����0����AfxWinMain����ִֹ�У�Ӧ�ó���رա�
	�������������ط�0ʱAfxWinMan��ִ�����¹ؼ����裺
	pThread->Run();
	����Ӧ�ó�������Run�������ú���ִ����Ϣѭ������ʼ��Ӧ�ó��򴰿ڷ�����Ϣ����Ϣѭ���ظ�ִ��ֱ��WM_QUIT��Ϣ����Ϣ�����б���������
	��ʱRun����ѭ����������ExitInstance�����ص�AfxWinMain����ִ������һЩ���������AfxWinMainִ��return������Ӧ�ó���

*/

#if _MSC_VER > 1000 
#pragma once 
#endif  

#ifndef _HELLO_H_
#define _HLLLO_H_

#undef _Win32_WINT
#define _WIN32_WINNT 0x0A00    // Windows�汾�ų�����������Ĭ��Ϊ_WIN32_WINNT_MAXVER��Ŀǰ���win10(0x0A00)

#include <afxwin.h>

// Ӧ�ó������������CWinThread����ʼ����ִ��pThread->Run(��WinMain.h��AfxWinMain��ں���)
class CMyApp : public CWinApp
{
public: 
	virtual BOOL InitInstance();
};

// ��ܴ��ڶ���
class CMainWindow : public CFrameWnd
{
public:
	CMainWindow();
protected:
	// afx_msg��������һ����Ϣ������򣬿���ʡ��afx_msg������ʱ������򻯳ɿհף�
	// afx_msg��ʾһ����Ϊ�������⺯����ȴ����Ҫ�����ĺ���
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg LRESULT OnSetText(WPARAM wParam, LPARAM lParam);

	// ����������ͨ��ʱ������䣬��Ϊ��ʹ��C++�ؼ�����ָ�����Ա�Ŀɼ��ȣ��������������������������Ա����䣬
	// ��Ӧ��ʹ�ùؼ���public, protected, ptrivate��ͷ����ȷ��Ϊ��Щ��Ա���ÿɼ���
	DECLARE_MESSAGE_MAP();  // protected: ...
};

#endif
