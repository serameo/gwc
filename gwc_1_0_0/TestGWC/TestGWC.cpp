#include "..\gwc\gwc.h"
#include "..\gwc\gwcapp.h"
#include "..\gwc\gwcwnd.h"
#include "..\gwc\gwcdlg.h"
#include "TestGWCrc.h"

using namespace gwc::win32;

class MyWnd : public GWCFrameWindow
{
public:
  virtual LPCTSTR GetClassName()
  {
    return TEXT("MyWnd_ClassName");
  }
protected:
  
  virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
  {
    switch (message)
    {
    case WM_DESTROY: PostQuitMessage(0); return 0;
    }
    return GWCFrameWindow::WindowProc(message, wParam, lParam);
  }
  
};

class MyDlg : public GWCDialog
{
public:
  MyDlg() : GWCDialog(NULL, IDD_DIALOG1)
  {
  }

protected:
  
  virtual void OnOK()
  {
    PostQuitMessage(0);
    ::SetWindowLongPtr(m_hWnd, DWL_MSGRESULT, (LONG)IDOK);
    GWCDialog::OnOK();
  }
  virtual void OnCancel()
  {
    // do not close if pressing ESC
    //GWCDialog::OnCancel();
  }
  
};

class MyMDIChild : public GWCMDIChildWindow
{
public:
  MyMDIChild()
  {
  }
  MyMDIChild(GWCMDIFrameWindow *pFrameWnd)
    : GWCMDIChildWindow(pFrameWnd)
  {
  }
  virtual LPCTSTR GetClassName(){ return TEXT("MyMDIChild_ClassName"); }

protected:
  virtual void OnDestroy()
  {
  }
};

class MyMDIChild2 : public GWCMDIChildWindow
{
public:
  MyMDIChild2()
  {
  }
  MyMDIChild2(GWCMDIFrameWindow *pFrameWnd)
    : GWCMDIChildWindow(pFrameWnd)
  {
  }
  virtual LPCTSTR GetClassName(){ return TEXT("MyMDIChild2_ClassName"); }

protected:
  virtual void OnDestroy()
  {
  }
};

class MyMDIFrame : public GWCMDIFrameWindow
{
  HMENU m_hFrameMenu;
  HMENU m_hChildMenu;
  HMENU m_hChildMenu2;
public:
  virtual LPCTSTR GetClassName(){ return TEXT("MyMDIFrame_ClassName"); }

protected:
  virtual void OnDestroy()
  {
    ::DestroyMenu(m_hChildMenu);
    ::DestroyMenu(m_hChildMenu2);
    PostQuitMessage(0); 
  }
  virtual BOOL OnCreate(LPCREATESTRUCT lpcs)
  {
    if ( !GWCMDIFrameWindow::OnCreate(lpcs) )
      return FALSE;

    m_hFrameMenu = ::LoadMenu(NULL, MAKEINTRESOURCE(IDR_TESTGWC_MAIN));
    m_hChildMenu = ::LoadMenu(NULL, MAKEINTRESOURCE(IDR_TESTGWC_CHILD));
    m_hChildMenu2 = ::LoadMenu(NULL, MAKEINTRESOURCE(IDR_TESTGWC_CHILD2));

    SetMDIMenu(m_hFrameMenu);
    ::SetMenu(m_hWnd, m_hFrameMenu);
    ::DrawMenuBar(m_hWnd);
    return TRUE;
  }
  virtual void OnCommand(int nID, GWCWindow *pCtrl, UINT nCode)
  {
    switch (nID)
    {
    case IDM_FILE_NEW:
      {
        MyMDIChild *pChild = new MyMDIChild(this);
        pChild->Create(TEXT("Hello World"), m_hChildMenu, 1);
      }
      break;
    case IDM_FILE_NEW_RECT:
      {
        MyMDIChild2 *pChild = new MyMDIChild2(this);
        pChild->Create(TEXT("Hello Rectangle"), m_hChildMenu2, 2);
      }
      break;

    default:
      GWCMDIFrameWindow::OnCommand(nID, pCtrl, nCode);
      break;
    }
  }
};

#define TEST_DIALOG

class MyApp : public GWCApplication
{
public:
  MyApp(HINSTANCE hInst, LPSTR lpszCmdLine, int nCmdShow)
    : GWCApplication(hInst, lpszCmdLine, nCmdShow)
  {
  }

protected:
#if defined( TEST_DIALOG0 )
  virtual BOOL InitInstance()
  {
    MyDlg *pWnd = new MyDlg();
    //pWnd->RegisterWindow(m_hInst);
    //pWnd->CreateEx(WS_EX_CLIENTEDGE, TEXT("GWC Test Functions"), WS_OVERLAPPEDWINDOW);
    pWnd->Show(NULL, TRUE);
    pWnd->ShowWindow(m_nCmdShow);
    pWnd->UpdateWindow();
    m_pMainWnd = pWnd;
    return TRUE;
  }
#elif defined( TEST_FRAME )
  virtual BOOL InitInstance()
  {
    MyWnd *pWnd = new MyWnd();
    pWnd->RegisterWindow(m_hInst);
    pWnd->CreateEx(WS_EX_CLIENTEDGE, TEXT("GWC Test Functions"), WS_OVERLAPPEDWINDOW);
    pWnd->ShowWindow(m_nCmdShow);
    pWnd->UpdateWindow();
    m_pMainWnd = pWnd;
    return TRUE;
  }
#else
  virtual BOOL InitInstance()
  {
    MyMDIChild child;
    child.RegisterWindow(m_hInst,
      (HBRUSH)(COLOR_BTNFACE + 1),
      ::LoadCursor(NULL, IDC_IBEAM),
      ::LoadIcon(NULL, IDI_EXCLAMATION));

    MyMDIChild2 child2;
    child2.RegisterWindow(m_hInst,
      (HBRUSH)(COLOR_HIGHLIGHT + 1),
      ::LoadCursor(NULL, IDC_CROSS),
      ::LoadIcon(NULL, IDI_QUESTION));

    MyMDIFrame *pFrame = new MyMDIFrame();
    pFrame->RegisterWindow(m_hInst, (HBRUSH)(COLOR_WINDOW + 1),
      ::LoadCursor(NULL, IDC_ARROW),
      ::LoadIcon(NULL, IDI_APPLICATION),
      MAKEINTRESOURCE(IDR_TESTGWC_MAIN));

    pFrame->CreateEx(WS_EX_CLIENTEDGE, TEXT("GWC MDI Windows"), WS_OVERLAPPEDWINDOW);
    pFrame->ShowWindow(m_nCmdShow);
    pFrame->UpdateWindow();
    m_pMainWnd = pFrame;
    return TRUE;
  }

#endif
};

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR lpszCmdLine, int nCmdShow)
{
  MyApp app(hInst, lpszCmdLine, nCmdShow);
  return app.Run();
}

