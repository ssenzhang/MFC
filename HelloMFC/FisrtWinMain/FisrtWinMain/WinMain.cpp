// WinMain.cpp

/** First Microsoft Foundation Class Program
*********��������*******
> ����C++����Ŀ ������-ϵͳ-��ϵͳ ����Ϊ���� (/SUBSYSTEM:WINDOWS)    
-- LINK2019 �޷��������ⲿ����,�÷����ں���"int _cdecl invoke_main(void)"(?invoke_main@@YAHXZ)������
-- ����̨ (/SUBSYSTEM:CONSOLE)����ں���Ϊint main(void), ������ʱ�޷�������ں������Ա���

> ע�����¼����ֵ��
> ��Ŀ-����-���� Ŀ���ļ���չ��Ϊ.exe����������ΪӦ�ó���exe��ʹ�ñ�׼Windows��������ӳ����޽������ţ��ַ�����������ΪUNICODE
> C/C++-����-��WChar_t��Ϊ��������  wchar_t��UNICODE��Ӧ
> ������-ϵͳ-��ϵͳ ����Ϊ���� (/SUBSYSTEM:WINDOWS)
************************/
#include "windows.h"  //�ײ�ʵ�ִ��ڵ�ͷ�ļ�

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//������ں���
//WINAPI ��������˳���ĸ��������ҵ�����ջ�����ں�������ǰ��ն�ջ
int WINAPI WinMain(
	HINSTANCE hInstance,       // Ӧ�ó���ʵ�����
	HINSTANCE hPrevInstance,   // ��һ��Ӧ�ó���ʵ���������Win32������һ��ΪNULL
	LPSTR lpszCmdLine,         // char* argv	[]
	int nCmdShow)              // ��ʾ��� ��󻯣���С����default...
{
	// 1.��ƴ���  
	WNDCLASS wc;
	wc.style = 0;                                           // Class style ��ʾ��� 0--default
	wc.cbClsExtra = 0;                                      // Class extra bytes ��Ķ�����ڴ�	
	wc.cbWndExtra = 0;                                      // Window extra bytes ���ڶ�����ڴ�
	wc.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);	// Background color ���ñ���
	// wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.hCursor = LoadCursor(NULL, IDC_HAND);                // Cursor handle ���ù�꣬�����һ������ΪNULL����ʹ��ϵͳ�ṩ�Ĺ��
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO/*IDI_ERROR*/);    // Icon handle ���Ͻ�ͼ��,�������һ������ΪNULLʹ��ϵͳĬ��ͼ��
    wc.hInstance = hInstance;                               // Instance handle Ӧ�ó���ʵ�����������WinMain�е��βμ���														
	wc.lpfnWndProc = (WNDPROC)WndProc;                      // Window procedure address �ص����������ڹ��̣���6��ʹ��													
	wc.lpszClassName = TEXT("MyWndClass");                  // WNDCLASS name ָ������������
	wc.lpszMenuName = NULL;                                 // Menu name �˵�����

    // 2.ע�ᴰ����
	// �����ඨ���˴��ڵ���Ҫ���ԣ��細�ڹ��̵�ַ��Ĭ�ϱ���ɫ�Լ�ͼ��ȣ���Щ����ͨ��һ��WNDCALSS(wc)�ṹ����ֶ�ֵ���壬��󴫸�RegisterClass
	// ��Ӧ�ó�������һ������ʱ������ָ��һ�������࣬�ڸ����ܱ�ʹ��֮ǰ�������ȶ������ע�᣻RegisterClass�ڳ���ʼ��������
	// WNDCLASS���ʹ�������C++�еĴ����಻һ����WNDCLASSΪRegisterClassע����࣬C++�еĴ�����ָMFC��CWnd����������
	RegisterClass(&wc);

	// 3.��������	
	// һ��WNDCLASS��ע�ᣬWinMain������CreateWindow����Ӧ�ó���Ĵ���
	// �˺���11������, �����ط�ʽ
	HWND hwnd = CreateWindow(
		TEXT("MyWndClass"),            // WNDCLASS name ��������
		TEXT("My First MFC Dialog"),   // Window title ���ڱ�����
		WS_OVERLAPPEDWINDOW,           // Window style ���
		CW_USEDEFAULT,                 // Horizontal position ��ʾ���� xֵ
		CW_USEDEFAULT,                 // Vertical position ��ʾ���� yֵ
		CW_USEDEFAULT,                 // Initial width ��
		CW_USEDEFAULT,                 // Initial Height ��
		HWND_DESKTOP/*NULL*/,          // Handle of parent window ������
		NULL,                          // Menu handle �˵�
		hInstance,                     // Application's instance handle  ʵ�����hInstance
		NULL                           // Window-creation data
	);

	// 4.��ʾˢ��
	// �������ɴ���ʱ��δʹ��WS_VISIBLE, CreateWindow���ɵĴ�������Ļ������ǲ��ɼ��ģ����ʹ��WS_VISIBLE��Ӧ����CreateWindow����WS_OVERLAPPEDWINDOW���Ӧ��
	// ����������������ʹ���ڿɼ���WM_PAINT��Ϣ����������̱�����
	ShowWindow(hwnd, /*nCmdShow*/SW_SHOWNORMAL);
	UpdateWindow(hwnd);

	// 5.ͨ����Ϣѭ��ȡ��Ϣ
	// Ϊ�˼�����������Ϣ��WinMainִ��һ���򵥵ķ�������GetMessage��TranslateMessage��
	// Ϊ�˼�����������Ϣ��WinMainִ��һ���򵥵ķ�������GetMessage��TranslateMessage��DispatchMessage����API������whileѭ�����
	// GetMessage�����Ϣ���У����ĳ����Ϣ����Ч�ģ������Ӷ�����ɾ�������Ƶ�msg������GetMessage��ͣ������Ϣ������ֱ����Ϣ��Ч
	// TranslateMessage��һ��ָʾ�ַ����ļ�����Ϣת��Ϊ������ʹ�õ�WM_CHAR��Ϣ
	// DispatchMessage����Ϣ���͸����ڹ���
	// ��Ϣѭ��һֱִ�е�GetMessage����ֵΪ0ʱ��������������ֻ����WM_QUIT��Ϣ����Ϣ�����б�������ʱ�ŷ�������ʱWinMain������������ֹ����

	// typedef struct tagMSG {
	//	 HWND hwnd;          //�����ھ��
	//	 UINT message;       //������Ϣ����
	//	 WPARAM wParam;      //������Ϣ ������Ϣ
	//	 LPARAM lParam;      //������Ϣ �����Ϣ
	//	 DWORD time;         //��Ϣ����ʱ�� ����ϵͳ���� ��Ϣ����������Ϣ�����е�ʱ�䣿
	//	 POINT pt;	         //������Ϣ �����Ϣ �������Ϣ x y
	// }MSG;
	MSG msg;
	/**
	_Out_ LPMSG lpMsg,            ��Ϣ
	_In_opt_ HWND hWnd,           ���񴰿� NULLΪ�������д�����Ϣ
	_In_ UINT wMsgFilterMin,      ��С�������˵���Ϣ��һ��Ϊ0��������������Ϣ
	_In_ UINT wMsgFilterMax);
	*/
	while (GetMessage(&msg, NULL, 0, 0))      // ��Ϣ����ȡ��Ϣ
	{
		TranslateMessage(&msg);               // ������Ϣ��������ϼ���Ϣ(CTRL+C)
		DispatchMessage(&msg);                // �ַ���Ϣ�����ڹ���
	}

	// 6.������Ϣ(���ڹ���)

	// return 0;
	return (int)msg.wParam;
}

// CALLBACK ��������˳���ĸ��������ҵ�����ջ�����ں�������ǰ��ն�ջ
LRESULT CALLBACK WndProc(
	HWND hwnd,         // ��Ϣ�������ھ��
	UINT message,      // ��Ϣ WM_XXXX
	WPARAM wParam,     // ���̸�����Ϣ
	LPARAM lParam)     // ��긽����Ϣ
{
	TCHAR buf[256] = { 0 };

	switch (message)
	{
	case WM_PAINT:           // ��ͼ
		PAINTSTRUCT ps;
		HDC hdc;
		hdc = BeginPaint(hwnd, &ps);   	// ��ȡ�豸�������
		TextOut(hdc, 0, 0, TEXT("Draw a ellipse:"), (int)strlen(TEXT("Draw a ellipse:")));
		Ellipse(hdc, 0, 20, 200, 100);
		EndPaint(hwnd, &ps);            // �ͷ��豸�������
		return 0;
	case WM_CLOSE:
		DestroyWindow(hwnd);   // ����WM_DESTROY��Ϣ���������������
		return 0;
	case WM_DESTROY:
		// �����յ�һ��WM_DESTROY��Ϣʱ�����㴰�ڱ������PostQuitMessage������������Ϣѭ������ֹͣ������Ҳ��Զ�������
		PostQuitMessage(0);   // ����Ϣ���з���WM_QUIT��Ϣ��ʹ����ֹͣ���У�ִ�к�GetMessageΪFALSE
		return 0;
	case WM_LBUTTONDOWN:      // ����������
		/**
		Do not use the LOWORD or HIWORD macros to extract the x- and y- coordinates of the cursor position,
		because these macros return incorrect results on systems with multiple monitors.
		Systems with multiple monitors can have negative x- and y- coordinates,
		and LOWORD and HIWORD treat the coordinates as unsigned quantities.
		*/
		POINT pt;
		// Just a Test, and it's not suggested
		pt.x = LOWORD(lParam); // GET_X_LPARAM(lParam); "Windowsx.h"
		pt.y = HIWORD(lParam); // GET_Y_LPARAM(lParam);

		// wsprintf ==>sprintf(MBCS) or swprintf(UNICODE) 
		wsprintf(buf, TEXT("POINT.X = %ld, POINT.Y = %ld"), pt.x, pt.y);
		MessageBox(hwnd, buf, TEXT("WM_LBUTTONDOWN"), message);
		return 0;
	case WM_KEYDOWN:
		TCHAR szTmp[32];
		GetKeyNameText((long)lParam, szTmp, 32);
		wsprintf(buf, TEXT("The %s was pressed down!"), szTmp);
		MessageBox(hwnd, buf, TEXT("WM_KEYDOWM"), message);
		return 0;
	}

	return DefWindowProc(hwnd, message, wParam, lParam);  // Default return value
}

/** ��������Ƿ�
	�� clr--COLORREF sz--��0��β���ַ��� psz--ָ����0��β���ַ�����ָ�� m_xxx---��ĳ�Ա����
*/
//Windows��һ���¼�������������Ϣ�Ĳ���ϵͳ����Ϣ����ϵͳ�з����κ�����ĺ���